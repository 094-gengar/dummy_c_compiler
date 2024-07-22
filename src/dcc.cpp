// #include "llvm/Assembly/PrintModulePass.h"
// #include "llvm/LLVMContext.h"
// #include "llvm/Module.h"
// #include "llvm/PassManager.h"
#include "llvm/LinkAllPasses.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/PrettyStackTrace.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/TargetSelect.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"

#include "lexer.hpp"
#include "AST.hpp"
#include "parser.hpp"
#include "codegen.hpp"

/*
 * オプション切り出し用クラス
 */
class OptionParser {
private:
	std::string InputFileName;
	std::string OutputFileName;
	std::string LinkFileName;
	bool WithJit;
	int Argc;
	char** Argv;
public:
	OptionParser(int argc, char** argv) : Argc(argc), Argv(argv), WithJit(false) {}
	void printHelp();
	std::string getInputFileName() { return InputFileName; }
	std::string getOutputFileName() { return OutputFileName; }
	std::string getLinkFilieName() { return LinkFileName; }
	bool getWithJit() { return WithJit; }
	bool parseOption();
};

/*
 * ヘルプ表示
 */
void OptionParser::printHelp() {
	fprintf(stdout, "Compiler for DummyC...\n");
}

/*
 * オプション切り出し
 * @return 成功：true、失敗：false
 */
bool OptionParser::parseOption() {
	if (Argc < 2) {
		fprintf(stderr, "引数が足りません\n");
		return false;
	}
	for (int i = 1; i < Argc; i++) {
		if (Argv[i][0] == '-' and Argv[i][1] == 'o' and Argv[i][2] == '\0') {
			OutputFileName.assign(Argv[++i]);
		} else if (Argv[i][0] == '-' and Argv[i][1] == 'h' and Argv[i][2] == '\0') {
			printHelp();
			return false;
		} else if (Argv[i][0] == '-' and Argv[i][1] == 'l' and Argv[i][2] == '\0') {
			LinkFileName.assign(Argv[++i]);
		} else if (Argv[i][0] == '-' and 
			Argv[i][1] == 'j' and
			Argv[i][2] == 'i' and
			Argv[i][3] == 't' and
			Argv[i][4] == '\0') {
			WithJit = true;
		} else if (Argv[i][0] == '-') { 
			fprintf(stderr, "%s は不明なオプションです\n", Argv[i]);
			return false;
		} else {
			InputFileName.assign(Argv[i]);
		}
	}
	// OutputFileName
	std::string ifn = InputFileName;
	int len = ifn.length();
	if (OutputFileName.empty() and (len > 2) and
		ifn[len - 3] == '.' and
		ifn[len - 2] == 'd' and
		ifn[len - 1] == 'c') {
		OutputFileName += std::string(begin(ifn), end(ifn));
		OutputFileName += ".s";
	} else if (OutputFileName.empty()) {
		OutputFileName = ifn;
		OutputFileName += ".s";
	}
	return true;
}

/*
 * main関数
 */
int main(int argc, char** argv)
{
	llvm::InitializeNativeTarget();
	llvm::sys::PrintStackTraceOnErrorSignal(*argv);
	llvm::PrettyStackTraceProgram X(argc, argv);

	llvm::EnableDebugBuffering = true;

	OptionParser opt(argc, argv);
	if (not opt.parseOption()) {
		exit(1);
	}

	// check
	if (opt.getInputFileName().length() == 0) {
		fprintf(stderr, "入力ファイル名が指定されていません\n");
		exit(1);
	}

	// lex and parse
	Parser* parser = new Parser(opt.getInputFileName());
	if (not parser->doParse()) {
		fprintf(stderr, "err at parser or lexer\n");
		SAFE_DELETE(parser);
		exit(1);
	}

	// get AST
	TranslationUnitAST& t_unit = parser->getAST();
	if (t_unit.empty()) {
		fprintf(stderr, "TranslationUnit is empty");
		SAFE_DELETE(parser);
		exit(1);
	}

	CodeGen* codegen = new CodeGen();
	if (not codegen->doCodeGen(t_unit, opt.getInputFileName(),
		opt.getLinkFilieName(), opt.getWithJit())) {
		fprintf(stderr, "err at codegen\n");
		SAFE_DELETE(parser);
		SAFE_DELETE(codegen);
		exit(1);
	}

	// get Module
	llvm::Module& mod = codegen->getModule();
	if (mod.empty()) {
		fprintf(stderr, "Module is empty");
		SAFE_DELETE(parser);
		SAFE_DELETE(codegen);
		exit(1);
	}

	llvm::legacy::PassManager pm;

	// mem2regを適用
	// pm.add(llvm::createPromoteMemoryToRegisterPass());

	// 出力
	std::error_code error;
	llvm::raw_fd_ostream raw_stream(llvm::StringRef(opt.getOutputFileName().c_str()), error);
	pm.add(llvm::createPrintModulePass(raw_stream));
	pm.run(mod);
	raw_stream.close();

	// delete
	SAFE_DELETE(parser);
	SAFE_DELETE(codegen);

	return 0;
}