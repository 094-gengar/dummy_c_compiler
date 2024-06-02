#ifndef CODEGEN_HPP 
#define CODEGEN_HPP

#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
#include <llvm/ADT/APInt.h>
// #include <llvm/Constants.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
// #include <llvm/ExecutionEngine/JIT.h>
// #include <llvm/Linker.h>
// #include <llvm/LLVMContext.h>
// #include <llvm/Module.h>
// #include <llvm/Metadata.h>
#include <llvm/Support/Casting.h>
// #include <llvm/IRBuilder.h>
// #include <llvm/Support/IRReader.h>
// #include <llvm/MDBuilder.h>
// #include <llvm/ValueSymbolTable.h>

#include <llvm/IR/IRBuilder.h>

#include "APP.hpp"
#include "AST.hpp"

/*
 * コード生成クラス
 */
class CodeGen {
private:
	llvm::Function* CurFunc; // 現在コード生成中のFunc
	llvm::Module* Mod; // 生成したModuleを格納
	llvm::IRBuilder<>* Builder; // LLVM-IRを生成するIRBuilderクラス

public:
	CodeGen();
	~CodeGen();
	bool doCodeGen(TranslationUnitAST& tunit, std::string name, std::string link_file, bool with_jit);
	llvm::Module& getModule();

private:
	bool generateTranslationUnit(TranslationUnitAST& tunit, std::string name);
	llvm::Function* generateFunctionDefinition(FunctionAST* func, llvm::Module* mod);
	llvm::Function* generatePrototype(PrototypeAST* proto, llvm::Module* mod);
	llvm::Value* generateFunctionStatement(FunctionStmtAST* func_stmt);
	llvm::Value* generateVariableDeclaration(VariableDeclAST* vdecl);
	llvm::Value* generateStatement(BaseAST* stmt);
	llvm::Value* generateBinaryExpression(BinaryExprAST* bin_expr);
	llvm::Value* generateCallExpression(CallExprAST* call_expr);
	llvm::Value* generateJumpStatement(JumpStmtAST* jump_stmt);
	llvm::Value* generateVariable(VariableAST* var);
	llvm::Value* generateNumber(int value);
	bool linkModule(llvm::Module* dest, std::string file_name);
};

#endif