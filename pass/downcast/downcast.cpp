#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Constants.h"
#include <unordered_map>

using namespace llvm;

struct DowncastPass : public FunctionPass {
	static char ID;
	std::unordered_map<std::string, int64_t> upper_mp;
	bool low_q(const std::string& s) {
		return upper_mp.count(s) and upper_mp.at(s) <= INT32_MAX;
	}
	// std::unordered_map<std::string, std::pair<std::string, std::string>> varpair_mp;

	DowncastPass() : FunctionPass(ID) {}

	bool runOnFunction(Function& F) override {
		upper_mp.clear();

		for (auto& BB : F) for (auto& I : BB) {
			if (auto* INST = dyn_cast<Instruction>(&I)) {
				if (MDNode* N = INST->getMetadata("upper_data")) {
					if (auto* S = dyn_cast<MDString>(N->getOperand(0))) {
						std::string variableName = INST->getName().str();
						if (variableName == "") {
							INST->setMetadata("upper_data", nullptr);
							continue; // metadataそのもの
						}
						std::string metadataStr = S->getString().str();
						// S = nullptr;
						int64_t upperValue = 0;
						upperValue = std::stoll(metadataStr);
						upper_mp[variableName] = upperValue;
					}
				}
				INST->setMetadata("upper_data", nullptr);
			}
		}

		// Alloca
		std::vector<AllocaInst*> AllocasToReplace{};
		for (auto& BB : F) for (auto& I : BB) {
			if (auto* Alloca = dyn_cast<AllocaInst>(&I)) {
				auto name = Alloca->getName().str();
				// llvm::errs() << name << '\n';
				if (low_q(name)) {
					AllocasToReplace.emplace_back(Alloca); // i32
				}
			}
		}
		for (auto* Alloca : AllocasToReplace) {
			IRBuilder<> Builder(Alloca);
			AllocaInst* NewAlloca;
			if (Alloca->getAllocatedType() == Type::getInt64Ty(F.getContext()) or Alloca->getAllocatedType() == Type::getInt32Ty(F.getContext())) {
				NewAlloca = Builder.CreateAlloca(Type::getInt32Ty(F.getContext()), Alloca->getArraySize(), Alloca->getName() + ".i32");
			} else {
				NewAlloca = Builder.CreateAlloca(ArrayType::get(Type::getInt32Ty(F.getContext()), Alloca->getAllocatedType()->getArrayNumElements()), Alloca->getArraySize(), Alloca->getName() + ".i32");
			}
			NewAlloca->takeName(Alloca);
			Alloca->replaceAllUsesWith(NewAlloca);
			Alloca->eraseFromParent();
		}

		// Store / Load / BinaryOperator
		std::vector<Instruction*> InstructionsToReplace{};
		for (auto& BB : F) for (auto& I : BB) {
			if (auto* Store = dyn_cast<StoreInst>(&I)) {
				Value* PointerOperand = Store->getPointerOperand();
				if (auto* Alloca = dyn_cast<AllocaInst>(PointerOperand->stripPointerCasts())) {
					// errs() << "Alloca->getName(): " <<  Alloca->getName() << '\n';
					auto name1 = Alloca->getName().str();
					if (upper_mp.count(name1)) {
						const auto& upper_val = upper_mp.at(name1);
						if (upper_val <= INT32_MAX) {
							InstructionsToReplace.emplace_back(Store); // こっちは主にinput()のときのtruncation
						}
					}
					// errs() << "Store->getValueOperand()->getName(): " << Store->getValueOperand()->getName() << '\n';
					auto name2 = Store->getValueOperand()->getName().str();
					if (upper_mp.count(name2)) {
						const auto& upper_val = upper_mp.at(name2);
						if (upper_val <= INT32_MAX) {
							InstructionsToReplace.emplace_back(Store); // こっちは store i32 i64 の場合
						}
					}
				}
			} else if (auto* Load = dyn_cast<LoadInst>(&I)) {
				Value* PointerOperand = Load->getPointerOperand();
				auto l_name = Load->getName();
				// errs() << l_name << '\n';
				if (auto* Alloca = dyn_cast<AllocaInst>(PointerOperand->stripPointerCasts())) {
					auto r_name = Alloca->getName().str();
					// errs() << "fuga: " <<  Alloca->getName() << '\n';
					if (upper_mp.count(r_name) or upper_mp.count(l_name)) {
						auto l_upper_val = upper_mp.count(l_name) ? upper_mp.at(l_name) : (int64_t)INT32_MAX;
						auto r_upper_val = upper_mp.count(r_name) ? upper_mp.at(r_name) : (int64_t)INT32_MAX;
						// errs() << l_upper_val << " " << r_upper_val << "\n";
						if (r_upper_val <= INT32_MAX or l_upper_val <= INT32_MAX) {
							// どちらもi32に直す
							InstructionsToReplace.emplace_back(Load);
						}
					}
				} else if (auto* GEP = dyn_cast<GetElementPtrInst>(PointerOperand->stripPointerCasts())) {
					auto r_name = GEP->getName().str();
					// errs() << "fuga: " <<  GEP->getName().str() << '\n';
					if (upper_mp.count(r_name) or upper_mp.count(l_name)) {
						auto l_upper_val = upper_mp.count(l_name) ? upper_mp.at(l_name) : (int64_t)INT32_MAX;
						auto r_upper_val = upper_mp.count(r_name) ? upper_mp.at(r_name) : (int64_t)INT32_MAX;
						// errs() << l_upper_val << " " << r_upper_val << "\n";
						if (r_upper_val <= INT32_MAX or l_upper_val <= INT32_MAX) {
							// どちらもi32に直す
							InstructionsToReplace.emplace_back(Load);
						}
					}
				} 
			} else if (auto* BinOp = dyn_cast<BinaryOperator>(&I)) {
				bool flag = false;
				auto tmp_name = BinOp->getName().str();
				// errs() << tmp_name << " " << BinOp->operands().end() - BinOp->operands().begin() << "\n";
				for (auto& op : BinOp->operands()) { // operands.size() should be 2
					auto name = op->getName().str();
					if (low_q(name)) {
						// i64でなかったら
						flag = true;
					}
				}
				for (auto& op : BinOp->operands()) {
					auto name = op->getName().str();
					// errs() << name << "\n";
				}
				// tmpがi32になるべきなときは絶対にebする
				if (flag or low_q(tmp_name) or true) InstructionsToReplace.emplace_back(BinOp);
			} else if (auto* Call = dyn_cast<CallInst>(&I)) {
				// errs() << Call->getCalledFunction()->getName() << "\n";
				if (Call->getCalledFunction()->getName() == "printnum") {
					InstructionsToReplace.emplace_back(Call);
				}
			} else if (auto* GEP = dyn_cast<GetElementPtrInst>(&I)) {
				if (low_q(GEP->getPointerOperand()->getName().str())) InstructionsToReplace.emplace_back(GEP);
			}
		}

		// 直す
		for (auto* Ins : InstructionsToReplace) {
			IRBuilder<> Builder(Ins);
			if (auto* Store = dyn_cast<StoreInst>(Ins)) {
				// errs() << "store: " << Store->getValueOperand()->getName() << '\n';
				auto* Alloca = dyn_cast<AllocaInst>(Store->getPointerOperand()->stripPointerCasts());
				auto name1 = Alloca->getName().str();
				auto name2 = Store->getValueOperand()->getName().str();
				if (low_q(name1) and low_q(name2)) {
					// どちらもi32なのでなにもしない
				} else if (low_q(name1)) {
					Value* StoredValue = Store->getValueOperand();
					Value* PointerOperand = Store->getPointerOperand();
					Value* TruncatedValue = Builder.CreateTrunc(StoredValue, Type::getInt32Ty(F.getContext()));
					Builder.CreateStore(TruncatedValue, PointerOperand);
					Store->eraseFromParent();
				} else if (low_q(name2)) {
					IRBuilder<> Builder(Alloca);
					AllocaInst* NewAlloca = Builder.CreateAlloca(Type::getInt32Ty(F.getContext()), Alloca->getArraySize(), Alloca->getName() + ".i32");
					NewAlloca->takeName(Alloca);
					Alloca->replaceAllUsesWith(NewAlloca);
					Alloca->eraseFromParent();
				} else {
					// どちらもi64なのでなにもしない
				}
			} else if (auto* Load = dyn_cast<LoadInst>(Ins)) {
				// errs() << Load->getName() << "\n";
				auto load_name = Load->getName().str();
				Value* PointerOperand = Load->getPointerOperand();
				auto p_name = PointerOperand->getName().str();
				// errs() << "fuga\n";
				if (low_q(load_name) or low_q(p_name)) {
					// errs() << "fuga\n";
					// errs() << p_name << "\n";
					Value* NewLoad = Builder.CreateLoad(Type::getInt32Ty(F.getContext()), PointerOperand, p_name + ".i32");
					NewLoad->takeName(Load);
					Load->replaceAllUsesWith(NewLoad);
					Load->eraseFromParent();
					// if (auto* Alloca = dyn_cast<AllocaInst>(PointerOperand)) {
					// 	IRBuilder<> Builder(Alloca);
					// 	AllocaInst* NewAlloca = Builder.CreateAlloca(Type::getInt32Ty(F.getContext()), Alloca->getArraySize(), Alloca->getName() + ".i32");
					// 	NewAlloca->takeName(Alloca);
					// 	Alloca->replaceAllUsesWith(NewAlloca);
					// 	Alloca->eraseFromParent();
					// } else if (auto* GEP = dyn_cast<Instruction>(PointerOperand)) {
					// 	// if (auto *Ty = dyn_cast<ArrayType>(GEP->getSourceElementType())) {
					// 	// 	assert(Ty->getArrayElementType()->isIntegerTy(64));
					// 	// 	llvm::Value* idxList[2] = {
					// 	// 		Builder.getInt32(0),
					// 	// 		GEP->getOperand(2)
					// 	// 	};
					// 	// 	auto NewGEP = Builder.CreateGEP(llvm::ArrayType::get(llvm::Type::getInt32Ty(F.getContext()), Ty->getArrayNumElements()), GEP->getPointerOperand(), idxList);
					// 	// 	NewGEP->takeName(GEP);
					// 	// 	GEP->replaceAllUsesWith(NewGEP);
					// 	// 	GEP->eraseFromParent();
					// 	// }
					// }

				}
			} else if (auto* BinOp = dyn_cast<BinaryOperator>(Ins)) {
				auto tmp_name = BinOp->getName();
				// errs() << tmp_name << "\n";
				// for (auto& op : BinOp->operands()) errs() << "hoge: " << op->getName().str() << "\n";
				Value* op1 = BinOp->getOperand(0);
				Value* op2 = BinOp->getOperand(1);
				if (upper_mp.count(tmp_name) and upper_mp.at(tmp_name) <= INT32_MAX) { // i32
					if (isa<ConstantInt>(op1)) {
						op1 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(F.getContext()), dyn_cast<ConstantInt>(op1)->getValue().sextOrTrunc(32));
						// errs() << "hoge\n";
					}
					if (isa<ConstantInt>(op2)) {
						op2 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(F.getContext()), dyn_cast<ConstantInt>(op2)->getValue().sextOrTrunc(32));
						// errs() << "hoge\n";
					}
					// errs() << "fuga: " << op1->getName() << "\n";
					if (const auto& name = op1->getName().str(); low_q(name) and op1->getType()->isIntegerTy(64)) {
						op1 = Builder.CreateTrunc(op1, Type::getInt32Ty(F.getContext()));
					}
					// errs() << "fuga: " << op2->getName().str() << "\n";
					if (const auto& name = op2->getName().str(); low_q(name) and op2->getType()->isIntegerTy(64)) {
						op2 = Builder.CreateTrunc(op2, Type::getInt32Ty(F.getContext()));
					}
					Value* NewBinOp = Builder.CreateBinOp(BinOp->getOpcode(), op1, op2, tmp_name + ".i32");
					NewBinOp->takeName(BinOp);
					BinOp->replaceAllUsesWith(NewBinOp);
					BinOp->eraseFromParent();
				} else { // i64
					if (isa<ConstantInt>(op1)) {
						op1 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(F.getContext()), dyn_cast<ConstantInt>(op1)->getValue().sextOrTrunc(64));
						// errs() << "hoge\n";
					}
					if (isa<ConstantInt>(op2)) {
						op2 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(F.getContext()), dyn_cast<ConstantInt>(op2)->getValue().sextOrTrunc(64));
						// errs() << "hoge\n";
					}
					// errs() << "piyo: " << op1->getName().str() << "\n";
					if (const auto& name = op1->getName().str(); op1->getType()->isIntegerTy(32)) {
						op1 = Builder.CreateSExt(op1, Type::getInt64Ty(F.getContext()));
					}
					// errs() << "piyo: " << op2->getName().str() << "\n";
					if (const auto& name = op2->getName().str(); op2->getType()->isIntegerTy(32)) {
						op2 = Builder.CreateSExt(op2, Type::getInt64Ty(F.getContext()));
					}
					Value* NewBinOp = Builder.CreateBinOp(BinOp->getOpcode(), op1, op2, tmp_name + ".i64");
					NewBinOp->takeName(BinOp);
					BinOp->replaceAllUsesWith(NewBinOp);
					BinOp->eraseFromParent();
				}
			} else if (auto* Call = dyn_cast<CallInst>(Ins)) {
				assert(Call->getCalledFunction()->getName() == "printnum");
				if (Call->getArgOperand(0)->getType()->isIntegerTy(32)) {
					Value* ArgValue = Call->getArgOperand(0);
					Value* SExtValue = Builder.CreateSExt(ArgValue, Type::getInt64Ty(F.getContext()));
					auto NewCall = Builder.CreateCall(Call->getCalledFunction(), llvm::ArrayRef<Value*>{SExtValue}, Call->getName());
					NewCall->takeName(Call);
					Call->replaceAllUsesWith(NewCall);
					Call->eraseFromParent();
				}
			} else if (auto* GEP = dyn_cast<GetElementPtrInst>(Ins)) {
				// errs() << "hoge\n";
				if (auto *Ty = dyn_cast<ArrayType>(GEP->getSourceElementType())) {
					assert(Ty->getArrayElementType()->isIntegerTy(64));
					llvm::Value* idxList[2] = {
						Builder.getInt32(0),
						GEP->getOperand(2)
					};
					auto NewGEP = Builder.CreateGEP(llvm::ArrayType::get(llvm::Type::getInt32Ty(F.getContext()), Ty->getArrayNumElements()), GEP->getPointerOperand(), idxList, GEP->getName() + ".i32");
					NewGEP->takeName(GEP);
					GEP->replaceAllUsesWith(NewGEP);
					GEP->eraseFromParent();

					// llvm::Value *idxList[2] = {
					// 	Builder->getInt32(0),
					// 	Builder->getInt32(llvm::dyn_cast<NumberAST>(rhs)->getNumberValue()),
					// };
					// llvm::Value *elemPtr = Builder->CreateGEP(llvm::ArrayType::get(llvm::Type::getInt64Ty(TheContext), a_siz[name]), decl_a_mp[name], idxList);
					
					// // ポインタ型がi64*なら、i32*に変更
					// errs() << GEP->getPointerOperand()->getType()->getPointerElementType()->isArrayTy() << "\n";
					// if (GEP->getPointerOperand()->getType()->isPointerTy() &&
					// 	GEP->getPointerOperand()->getType()->getPointerElementType()->isArrayTy()) {
					// 	errs() << "fuga\n";
					// 	IRBuilder<> Builder(GEP);
					// 	// ポインタ型のキャストを行う
					// 	Value *NewPointer = Builder.CreateBitCast(GEP->getPointerOperand(), Type::getInt32PtrTy(F.getContext()));
					// 	GEP->setOperand(0, NewPointer);
					// }

					// // インデックスの型を変更（i64 -> i32）
					// for (unsigned i = 1; i < GEP->getNumOperands(); ++i) {
					// 	Value *Index = GEP->getOperand(i);
					// 	if (Index->getType()->isIntegerTy(64)) {
					// 		// i64型のインデックスをi32型に変換
					// 		IRBuilder<> Builder(GEP);
					// 		Value *NewIndex = Builder.CreateTrunc(Index, Type::getInt32Ty(F.getContext()));
					// 		GEP->setOperand(i, NewIndex);
					// 	}
					// }
				}
			}
		}

		// for (const auto& [key, value] : upper_mp) {
		// 	errs() << key << "\r\t\t: " << value << "\n";
		// }

		return true;
	}
};

char DowncastPass::ID = 0;
static RegisterPass<DowncastPass> X("downcastpass", "");
