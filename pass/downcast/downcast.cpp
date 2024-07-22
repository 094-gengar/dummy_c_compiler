#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Constants.h"
#include <unordered_map>

using namespace llvm;

struct MetadataCollectorPass : public FunctionPass {
	static char ID;
	std::unordered_map<std::string, int64_t> upper_mp;

	MetadataCollectorPass() : FunctionPass(ID) {}

	bool runOnFunction(Function &F) override {
		upper_mp.clear();
		// Instruction().getName();
		// StoreInst().getName();
		// LoadInst().getName();
		// BinaryOperator().getName();

		for (auto &BB : F) for (auto &I : BB) {
			if (auto *INST = dyn_cast<Instruction>(&I)) {
				if (MDNode *N = INST->getMetadata("upper_data")) {
					if (auto *S = dyn_cast<MDString>(N->getOperand(0))) {
						std::string variableName = INST->getName().str();
						if (variableName == "") continue; // metadataそのもの
						std::string metadataStr = S->getString().str();
						int64_t upperValue = 0;
						upperValue = std::stoll(metadataStr);
						upper_mp[variableName] = upperValue;
					}
				}
			}
		}

		for (const auto &[key, value] : upper_mp) {
			errs() << key << "\r\t\t: " << value << "\n";
		}

		return false;
	}
};

char MetadataCollectorPass::ID = 0;
static RegisterPass<MetadataCollectorPass> X("downcastpass", "");
