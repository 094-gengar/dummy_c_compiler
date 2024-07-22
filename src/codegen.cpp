#include "codegen.hpp"

#include <llvm/IR/Metadata.h>
#include <llvm/Support/Error.h>


#include <unordered_map>

std::unordered_map<std::string, int64_t> mp{};
std::unordered_map<std::string, llvm::AllocaInst*> decl_mp{};

/*
 * コンストラクタ
 */
CodeGen::CodeGen() {
	Builder = new llvm::IRBuilder<>(TheContext);
	Mod = NULL;
}

/*
 * デストラクタ
 */
CodeGen::~CodeGen() {
	SAFE_DELETE(Builder);
	SAFE_DELETE(Mod);
}

/*
 * コード生成実行
 * @param TranslationUnitAST Module名(入力ファイル名)
 * @return 成功：true、失敗：false
 */
bool CodeGen::doCodeGen(TranslationUnitAST& t_unit, std::string name, std::string link_file, bool with_jit = false) {
	if (not generateTranslationUnit(t_unit, name)) {
		return false;
	}
	// LinkFileの指定があったらModuleをリンク
	if (not link_file.empty() and not linkModule(Mod, link_file)) {
		return false;
	}
	// JITのフラグが立っていたらJIT
	if (with_jit) {
		// TODO
	}
	return true;
}

/*
 * Module取得
 */
llvm::Module& CodeGen::getModule() {
	if (Mod) {
		return *Mod;
	} else {
		return *(new llvm::Module("null", TheContext));
	}
}

/*
 * Module生成メソッド
 * @param TranslationUnitAST Module名(入力ファイル名)
 * @return 成功：true、失敗：false
 */
bool CodeGen::generateTranslationUnit(TranslationUnitAST& t_unit, std::string name) {
	Mod = new llvm::Module(name, TheContext);
	// function declaration
	for (int i = 0; ; i++) {
		PrototypeAST* proto = t_unit.getPrototype(i);
		if (not proto) {
			break;
		} else if (not generatePrototype(proto, Mod)) {
			SAFE_DELETE(Mod);
			return false;
		}
	}
	// function definition
	for (int i = 0; ; i++) {
		FunctionAST* func = t_unit.getFunction(i);
		if (not func) {
			break;
		} else if (not generateFunctionDefinition(func, Mod)) {
			SAFE_DELETE(Mod);
			return false;
		}
	}
	return true;
}

/*
 * 関数定義生成メソッド
 * @param FunctionAST Module
 * @return 生成したFunctionのポインタ
 */
llvm::Function* CodeGen::generateFunctionDefinition(FunctionAST* func_ast, llvm::Module* mod) {
	llvm::Function* func = generatePrototype(func_ast->getPrototype(), mod);
	if (not func) {
		return NULL;
	}
	CurFunc = func;
	llvm::BasicBlock* bblock = llvm::BasicBlock::Create(TheContext, "entry", func);
	Builder->SetInsertPoint(bblock);
	generateFunctionStatement(func_ast->getBody());
	return func;
}

/*
 * 関数宣言生成メソッド
 * @param PrototypeAST Module
 * @return 生成したFunctionのポインタ
 */
llvm::Function* CodeGen::generatePrototype(PrototypeAST* proto, llvm::Module* mod) {
	// already declared?
	llvm::Function* func = mod->getFunction(proto->getName());
	if (func) {
		if (func->arg_size() == proto->getParamNum() and func->empty()) {
			return func;
		} else {
			fprintf(stderr, "error::function %s is redefined", proto->getName().c_str());
			return NULL;
		}
	}
	// create arg_types
	std::vector<llvm::Type*> int_types(proto->getParamNum(), llvm::Type::getInt64Ty(TheContext)); // TODO
	// create func type
	llvm::FunctionType* func_type = llvm::FunctionType::get(llvm::Type::getInt64Ty(TheContext), int_types, false);
	// create function
	func = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage, proto->getName(), mod);
	// set names
	llvm::Function::arg_iterator arg_iter = func->arg_begin();
	for (int i = 0; i < proto->getParamNum(); i++) {
		arg_iter->setName(proto->getParamName(i).append("_arg"));
		arg_iter++;
	}
	return func;
}

/*
 * 関数生成メソッド
 * 変数宣言、ステートメントの順に作成
 * @param FunctionStmtAST
 * @return 最後に生成したValueのポインタ
 */
llvm::Value* CodeGen::generateFunctionStatement(FunctionStmtAST* func_stmt) {
	// insert variable decls
	VariableDeclAST* v_decl;
	llvm::Value* v = NULL;
	for (int i = 0; ; i++) {
		if (not func_stmt->getVariableDecl(i)) {
			break;
		}
		// create alloca
		v_decl = llvm::dyn_cast<VariableDeclAST>(func_stmt->getVariableDecl(i));
		v = generateVariableDeclaration(v_decl);
	}
	// insert expr statement
	BaseAST* stmt;
	for (int i = 0; ; i++) {
		stmt = func_stmt->getStatement(i);
		if (not stmt) {
			break;
		} else if (not llvm::isa<NullExprAST>(stmt)) {
			v = generateStatement(stmt);
		}
	}
	return v;
}

/*
 * 変数宣言(alloca)生成メソッド
 * @param VariableDeclAST
 * @return 生成したValueのポインタ
 */
llvm::Value* CodeGen::generateVariableDeclaration(VariableDeclAST* v_decl) {
	// create alloca
	llvm::AllocaInst* alloca = Builder->CreateAlloca(llvm::Type::getInt64Ty(TheContext), 0, v_decl->getName());
	decl_mp[v_decl->getName()] = alloca;
	//        llvm::errs() << "gVD: " << v_decl->getName() << '\n';

	// if args alloca
	if (v_decl->getType() == VariableDeclAST::param) {
		// Find the argument in the function's argument list
		std::string argName = v_decl->getName().append("_arg");
		//        llvm::errs() << v_decl->getName() << '\n';
		//        llvm::errs() << argName << '\n';
		llvm::Argument* arg = NULL;
		for (llvm::Argument& a : CurFunc->args()) {
			//        llvm::errs() << a.getName() << "\n";
			if (a.getName() == argName) {
				arg = &a;
				break;
			}
		}
		//        llvm::errs() << arg->getName() << '\n';
		if (arg) {
			// store args
			Builder->CreateStore(arg, alloca);
		} else {
			llvm::errs() << "Argument not found: " << argName << "\n";
		}
		// llvm::ValueSymbolTable& vs_table = CurFunc->getValueSymbolTable();
		// Builder->CreateStore(vs_table.lookup(v_decl->getName().append("_arg")), alloca);
	}
	return alloca;
}

/*
 * ステートメント生成メソッド
 * 実際にはASTの種類を確認して各種生成メソッドを呼び出し
 * @param JumpStmtAST
 * @return 生成したValueのポインタ
 */
llvm::Value* CodeGen::generateStatement(BaseAST* stmt) {
	if (llvm::isa<BinaryExprAST>(stmt)) {
		return generateBinaryExpression(llvm::dyn_cast<BinaryExprAST>(stmt));
	} else if (llvm::isa<CallExprAST>(stmt)) {
		return generateCallExpression(llvm::dyn_cast<CallExprAST>(stmt));
	} else if (llvm::isa<JumpStmtAST>(stmt)) {
		return generateJumpStatement(llvm::dyn_cast<JumpStmtAST>(stmt));
	} else {
		return NULL;
	}
}

/*
 * 二項演算生成メソッド
 * @param JumpStmtAST
 * @return 生成したValueのポインタ
 */
llvm::Value* CodeGen::generateBinaryExpression(BinaryExprAST* bin_expr) {
	BaseAST* lhs = bin_expr->getLHS();
	BaseAST* rhs = bin_expr->getRHS();
	llvm::Value* lhs_v;
	llvm::Value* rhs_v;
	// assignment
	if (bin_expr->getOp() == "=") {
		// lhs is variable
		VariableAST* lhs_var = llvm::dyn_cast<VariableAST>(lhs);
		std::string varName = lhs_var->getName();
		llvm::Value* local_var = NULL;
		// llvm::Argument* arg = NULL;
		for (llvm::BasicBlock& bb : *CurFunc) {
			for (llvm::Instruction& i : bb) {
				if (i.getName() == varName) {
					local_var = &i;
					break;
				}
			}
			if (local_var) {
				break;
			}
		}
		if (local_var) {
			lhs_v = local_var;
		} else {
			llvm::errs() << "Variable not found: " << varName << "\n";
		}
	} else if (bin_expr->getOp() == "$") {
		/* pass */
	} else { // other operand
		// lhs = ?
		// Binary?
		if (llvm::isa<BinaryExprAST>(lhs)) {
			lhs_v = generateBinaryExpression(llvm::dyn_cast<BinaryExprAST>(lhs));
		} else if (llvm::isa<VariableAST>(lhs)) { // Variable?
			lhs_v = generateVariable(llvm::dyn_cast<VariableAST>(lhs));
		} else if (llvm::isa<NumberAST>(lhs)) { // Number?
			NumberAST* num = llvm::dyn_cast<NumberAST>(lhs);
			lhs_v = generateNumber(num->getNumberValue());
		}
	}
	// create rhs value
	if (llvm::isa<BinaryExprAST>(rhs)) {
		rhs_v = generateBinaryExpression(llvm::dyn_cast<BinaryExprAST>(rhs));
	} else if (llvm::isa<CallExprAST>(rhs)) { // CallExpr?
		rhs_v = generateCallExpression(llvm::dyn_cast<CallExprAST>(rhs));
	} else if (llvm::isa<VariableAST>(rhs)) { // Variable?
		rhs_v = generateVariable(llvm::dyn_cast<VariableAST>(rhs));
	} else if (llvm::isa<NumberAST>(rhs)) { // Number?
		NumberAST* num = llvm::dyn_cast<NumberAST>(rhs);
		rhs_v = generateNumber(num->getNumberValue());
	}

	if (bin_expr->getOp() == "=") {
		// store
		// llvm::errs() << rhs_v->getName() << '\n';
		if (mp.count(rhs_v->getName())) {
			mp[lhs_v->getName()] = mp[rhs_v->getName()];
			// llvm::errs() << "=, mp[lhs_v->getName()] : " << mp[lhs_v->getName()] << '\n';
		}
		auto tmp = Builder->CreateStore(rhs_v, lhs_v);
		llvm::MDNode* Node = llvm::MDNode::get(TheContext, llvm::MDString::get(TheContext, std::to_string(mp[lhs_v->getName()])));
		llvm::cast<llvm::Instruction>(tmp)->setMetadata("upper_data", Node);
		return tmp;
		// assert(lhs->getUpper() == Infty);
		// lhs->UpdateUpper(rhs->getUpper());
		//       llvm::errs() << lhs->getUpper() << '\n';
	} else if (bin_expr->getOp() == "+") { // add
		auto tmp = Builder->CreateAdd(lhs_v, rhs_v, "add_tmp");
		// llvm::errs() << lhs_v->getName() << '\n';
		// llvm::errs() << rhs_v->getName() << '\n';
		mp[tmp->getName()] = mp[lhs_v->getName()] + mp[rhs_v->getName()];
		// llvm::errs() << "+, mp[tmp->getName()] : " << mp[tmp->getName()] << '\n';
		llvm::MDNode* Node = llvm::MDNode::get(TheContext, llvm::MDString::get(TheContext, std::to_string(mp[tmp->getName()])));
		llvm::cast<llvm::Instruction>(tmp)->setMetadata("upper_data", Node);
		return tmp;
	} else if (bin_expr->getOp() == "-") { // sub
		auto tmp = Builder->CreateSub(lhs_v, rhs_v, "sub_tmp");
		mp[tmp->getName()] = mp[lhs_v->getName()] - mp[rhs_v->getName()];
		llvm::MDNode* Node = llvm::MDNode::get(TheContext, llvm::MDString::get(TheContext, std::to_string(mp[tmp->getName()])));
		llvm::cast<llvm::Instruction>(tmp)->setMetadata("upper_data", Node);
		// llvm::errs() << "mp[tmp->getName()] : " << mp[tmp->getName()] << '\n';
		return tmp;
	} else if (bin_expr->getOp() == "*") { // mul
		auto tmp = Builder->CreateMul(lhs_v, rhs_v, "mul_tmp");
		mp[tmp->getName()] = mp[lhs_v->getName()] * mp[rhs_v->getName()];
		llvm::MDNode* Node = llvm::MDNode::get(TheContext, llvm::MDString::get(TheContext, std::to_string(mp[tmp->getName()])));
		llvm::cast<llvm::Instruction>(tmp)->setMetadata("upper_data", Node);
		// llvm::errs() << "mp[tmp->getName()] : " << mp[tmp->getName()] << '\n';
		return tmp;
	} else if (bin_expr->getOp() == "/") { // div
		auto tmp = Builder->CreateSDiv(lhs_v, rhs_v, "div_tmp");
		mp[tmp->getName()] = mp[lhs_v->getName()] / mp[rhs_v->getName()];
		llvm::MDNode* Node = llvm::MDNode::get(TheContext, llvm::MDString::get(TheContext, std::to_string(mp[tmp->getName()])));
		llvm::cast<llvm::Instruction>(tmp)->setMetadata("upper_data", Node);
		// llvm::errs() << "mp[tmp->getName()] : " << mp[tmp->getName()] << '\n';
		return tmp;
	} else if (bin_expr->getOp() == "$") { // 注釈
		assert(llvm::isa<VariableAST>(lhs));
		assert(llvm::isa<NumberAST>(rhs));
		mp[llvm::dyn_cast<VariableAST>(lhs)->getName()] = llvm::dyn_cast<NumberAST>(rhs)->getNumberValue();
		llvm::MDNode* Node = llvm::MDNode::get(TheContext, llvm::MDString::get(TheContext, std::to_string(mp[llvm::dyn_cast<VariableAST>(lhs)->getName()])));
		llvm::cast<llvm::Instruction>(decl_mp[llvm::dyn_cast<VariableAST>(lhs)->getName()])->setMetadata("upper_data", Node);
		// lhs->UpdateUpper(rhs->getUpper());
		// llvm::errs() << "$, mp[lhs_v->getName()] : " << mp[llvm::dyn_cast<VariableAST>(lhs)->getName()] << '\n';
		return NULL;
	} else {
		return NULL;
	}
}

/*
 * 関数呼び出し(Call命令)生成メソッド
 * @param CallExprAST
 * @return 生成したValueのポインタ
 */
llvm::Value* CodeGen::generateCallExpression(CallExprAST* call_expr) {
	std::vector<llvm::Value*> arg_vec;
	BaseAST* arg;
	llvm::Value* arg_v;
	for (int i = 0; ; i++) {
		if (not (arg = call_expr->getArgs(i))) {
			break;
		}
		// isCall
		if (llvm::isa<CallExprAST>(arg)) {
			arg_v = generateCallExpression(llvm::dyn_cast<CallExprAST>(arg));
		} else if (llvm::isa<BinaryExprAST>(arg)) { // isBinaryExpr
			BinaryExprAST* bin_expr = llvm::dyn_cast<BinaryExprAST>(arg);
			// 二項演算命令を生成
			arg_v = generateBinaryExpression(llvm::dyn_cast<BinaryExprAST>(arg));
			// 代入のときはLoad命令を追加
			if (bin_expr->getOp() == "=") {
				VariableAST* var = llvm::dyn_cast<VariableAST>(bin_expr->getLHS());

				std::string varName = var->getName();
				llvm::Value* local_var = NULL;
				// llvm::Argument* arg = NULL;
				for (llvm::BasicBlock& bb : *CurFunc) {
					for (llvm::Instruction& i : bb) {
						if (i.getName() == varName) {
							local_var = &i;
							break;
						}
					}
					if (local_var) {
						break;
					}
				}
				arg_v = Builder->CreateLoad(local_var, "arg_val");
			}
		} else if (llvm::isa<VariableAST>(arg)) { // isVar
			arg_v = generateVariable(llvm::dyn_cast<VariableAST>(arg));
		} else if (llvm::isa<NumberAST>(arg)) { // isNumber
			NumberAST* num = llvm::dyn_cast<NumberAST>(arg);
			arg_v = generateNumber(num->getNumberValue());
		}
		arg_vec.push_back(arg_v);
	}
	return Builder->CreateCall(Mod->getFunction(call_expr->getCallee()), arg_vec, "call_tmp");
}

/*
 * ジャンプ(今回はreturn命令のみ)生成メソッド
 * @param JumpStmtAST
 * @return 生成したValueのポインタ
 */
llvm::Value* CodeGen::generateJumpStatement(JumpStmtAST* jump_stmt) {
	BaseAST* expr = jump_stmt->getExpr();
	llvm::Value* ret_v;
	if (llvm::isa<BinaryExprAST>(expr)) {
		ret_v = generateBinaryExpression(llvm::dyn_cast<BinaryExprAST>(expr));
	} else if (llvm::isa<VariableAST>(expr)) {
		VariableAST* var = llvm::dyn_cast<VariableAST>(expr);
		ret_v = generateVariable(var);
	} else if (llvm::isa<NumberAST>(expr)) {
		NumberAST* num = llvm::dyn_cast<NumberAST>(expr);
		ret_v = generateNumber(num->getNumberValue());
	}
	Builder->CreateRet(ret_v);
	return ret_v; // 確かめる
}

/*
 * 変数参照(load命令)生成メソッド
 * @param VariableAST
 * @return 生成したValueのポインタ
 */
llvm::Value* CodeGen::generateVariable(VariableAST* var) {
	std::string varName = var->getName();
	llvm::Value* local_var = NULL;
	// llvm::Argument* arg = NULL;
	for (llvm::BasicBlock& bb : *CurFunc) {
		for (llvm::Instruction& i : bb) {
			if (i.getName() == varName) {
				local_var = &i;
				break;
			}
		}
		if (local_var) {
			break;
		}
	}
	if (local_var) {
		auto tmp = Builder->CreateLoad(local_var, "var_tmp");
		// llvm::errs() << local_var->getName() << '\n';
		// llvm::errs() << tmp->getName() << '\n';
		if (mp.count(local_var->getName())) {
			// llvm::errs() << "hoge" << '\n';
			// llvm::errs() << mp[local_var->getName()] << '\n';
			mp[tmp->getName()] = mp[local_var->getName()];
			llvm::MDNode* Node = llvm::MDNode::get(TheContext, llvm::MDString::get(TheContext, std::to_string(mp[tmp->getName()])));
			llvm::cast<llvm::Instruction>(tmp)->setMetadata("upper_data", Node);
		}
		return tmp;
	} else {
		assert(0);
	}
}

llvm::Value* CodeGen::generateNumber(int64_t value) {
	return llvm::ConstantInt::get(llvm::Type::getInt64Ty(TheContext), value);
}
bool CodeGen::linkModule(llvm::Module* dest, std::string file_name) {
	// TODO
	return false;
}