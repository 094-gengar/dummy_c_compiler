#include "parser.hpp"

/*
 * コンストラクタ
 */
Parser::Parser(std::string filename) {
	Tokens = LexicalAnalysis(filename);
}

/*
 * 構文解析実行
 * @return 成功/失敗→T/F
 */
bool Parser::doParse() {
	if (not Tokens) {
		fprintf(stderr, "error at lexer\n");
		return false;
	} else {
		return visitTranslationUnit();
	}
}

/*
 * AST取得
 * @return TranslationUnitへの参照
 */
TranslationUnitAST& Parser::getAST() {
	if (TU) {
		return *TU;
	} else {
		return *(new TranslationUnitAST());
	}
}

/*
 * TranslationUnit用構文解析メソッド
 * @return 解析成功/失敗→T/F
 */
bool Parser::visitTranslationUnit() {
	TU = new TranslationUnitAST();
	std::vector<std::string> param_list;
	param_list.push_back("i");
	TU->addPrototype(new PrototypeAST("printnum", param_list));
	PrototypeTable["printnum"] = 1;
	// ExternalDecl
	while (true) {
		if (not visitExternalDeclaration(TU)) {
			SAFE_DELETE(TU);
			return false;
		}
		if (Tokens->getCurType() == TOK_EOF) {
			break;
		}
	}
	return true;
}


/*
 * ExternalDeclaration用構文解析クラス
 * 解析したPrototypeとFunctionASTをTranslationUnitに追加
 * @param TranslationUnitAST
 * @return true
 */
bool Parser::visitExternalDeclaration(TranslationUnitAST* t_unit) {
	// FunctionDeclaration
	PrototypeAST* proto = visitFunctionDeclaration();
	if (proto) {
		t_unit->addPrototype(proto);
		return true;
	}
	// FunctionDefinition
	FunctionAST* func_def = visitFunctionDefinition();
	if (func_def) {
		t_unit->addFunction(func_def);
		return true;
	}
	return false;
}

/*
 * FunctionDeclaration用構文解析メソッド
 * @return 解析成功：PrototypeAST、失敗：NULL
 */
PrototypeAST* Parser::visitFunctionDeclaration() {
	const int tmp = Tokens->getCurIndex();
	PrototypeAST* proto = visitPrototype();
	if (not proto) {
		return NULL;
	}
	// prototype
	if (Tokens->getCurString() == ";") {
		if (PrototypeTable.count(proto->getName()) or
			(FunctionTable.count(proto->getName()) and FunctionTable[proto->getName()] != proto->getParamNum())) {
			fprintf(stderr, "Function: %s is redefined", proto->getName().c_str());
			SAFE_DELETE(proto);
			return NULL;
		}
		PrototypeTable[proto->getName()] = proto->getParamNum();
		Tokens->getNextToken();
		return proto;
	} else {
		SAFE_DELETE(proto);
		Tokens->applyTokenIndex(tmp);
		return NULL;
	}
}

/*
 * FunctionDefinition用構文解析メソッド
 * @return 解析成功：FunctionAST、失敗：NULL
 */
FunctionAST* Parser::visitFunctionDefinition() {
	const int tmp = Tokens->getCurIndex();
	PrototypeAST* proto = visitPrototype();
	if (not proto) {
		return NULL;
	} else if (PrototypeTable.count(proto->getName()) or
		(FunctionTable.count(proto->getName()) and FunctionTable[proto->getName()] != proto->getParamNum())) {
		fprintf(stderr, "Function: %s is redefined", proto->getName().c_str());
		SAFE_DELETE(proto);
		return NULL;
	}

	VariableTable.clear();
	FunctionStmtAST* func_stmt = visitFunctionStatement(proto);
	if (func_stmt) {
		FunctionTable[proto->getName()] = proto->getParamNum();
		return new FunctionAST(proto, func_stmt);
	} else {
		SAFE_DELETE(proto);
		Tokens->applyTokenIndex(tmp);
		return NULL;
	}
}

/*
 * Prototype用構文解析メソッド
 * @return 解析成功：PrototypeAST、失敗：NULL
 */
PrototypeAST* Parser::visitPrototype() {
	std::string func_name;
	const int tmp = Tokens->getCurIndex();
	
	// type_specifier
	if (Tokens->getCurType() == TOK_INT) {
		Tokens->getNextToken();
	} else {
		return NULL;
	}

	// IDENTIFIER
	if (Tokens->getCurType() == TOK_IDENTIFIER) {
		func_name = Tokens->getCurString();
		Tokens->getNextToken();
	} else {
		Tokens->ungetToken(1); // unget TOK_INT
		return NULL;
	}

	// '('
	if (Tokens->getCurString() == "(") {
		Tokens->getNextToken();
	} else {
		Tokens->ungetToken(2); // unget TOK_INT IDENTIFIER
		return NULL;
	}

	// parameter_list
	std::vector<std::string> param_list;
	bool is_first_param = true;
	while (true) {
		// ','
		if (not is_first_param and Tokens->getCurType() == TOK_SYMBOL and Tokens->getCurString() == ",") {
			Tokens->getNextToken();
		}
		if (Tokens->getCurType() == TOK_INT) {
			Tokens->getNextToken();
		} else {
			break;
		}
		if (Tokens->getCurType() == TOK_IDENTIFIER) {
			if (std::find(begin(param_list), end(param_list), Tokens->getCurString()) != end(param_list)) {
				Tokens->applyTokenIndex(tmp);
				return NULL;
			}
			param_list.push_back(Tokens->getCurString());
			Tokens->getNextToken();
		} else {
			Tokens->applyTokenIndex(tmp);
			return NULL;
		}
		is_first_param = false;
	}

	// ')'
	if (Tokens->getCurString() == ")") {
		Tokens->getNextToken();
		return new PrototypeAST(func_name, param_list);
	} else {
		Tokens->applyTokenIndex(tmp);
		return NULL;
	}
}

// TODO