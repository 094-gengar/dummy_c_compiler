#include <iostream>
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
		// Tokens->printTokens();
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
	TU->addPrototype(new PrototypeAST("inputnum", std::vector<std::string>{}));
	PrototypeTable["printnum"] = 1;
	PrototypeTable["inputnum"] = 0;
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

/*
 * FunctionStatement用構文解析メソッド
 * @param 関数名、引数を格納したPrototypeクラスのインスタンス
 * @return 解析成功：FunctionStmtAST、失敗：NULL
 */
FunctionStmtAST* Parser::visitFunctionStatement(PrototypeAST* proto) {
	const int tmp = Tokens->getCurIndex();
	// {
	if (Tokens->getCurString() == "{") {
		Tokens->getNextToken();
	} else {
		return NULL;
	}

	// create FunctionStatement
	FunctionStmtAST* func_stmt = new FunctionStmtAST();

	// add parameter to FunctionStatement
	for (int i = 0; i < proto->getParamNum(); i++) {
		VariableDeclAST* vdecl = new VariableDeclAST(proto->getParamName(i));
		vdecl->setDeclType(VariableDeclAST::param);
		func_stmt->addVariableDeclaration(vdecl);
		VariableTable.push_back(vdecl->getName());
	}

	VariableDeclAST* var_decl;
	ArrayDeclAST* arr_decl;
	BaseAST* stmt, * last_stmt;

	// {statement_list}
	if (stmt = visitStatement()) {
		while (stmt) {
			last_stmt = stmt;
			func_stmt->addStatement(stmt);
			stmt = visitStatement();
		}
	} else if (var_decl = visitVariableDeclaration()) { // variable_declaration list
		while (var_decl) {
			var_decl->setDeclType(VariableDeclAST::local);
			if (std::find(begin(VariableTable), end(VariableTable), var_decl->getName()) != end(VariableTable)) {
				SAFE_DELETE(var_decl);
				SAFE_DELETE(func_stmt);
				return NULL;
			}
			func_stmt->addVariableDeclaration(var_decl);
			VariableTable.push_back(var_decl->getName());
			// parse Variable Declaration
			var_decl = visitVariableDeclaration();
		}
		if (stmt = visitStatement()) {
			while (stmt) {
				last_stmt = stmt;
				func_stmt->addStatement(stmt);
				stmt = visitStatement();
			}
		}
	} else if (arr_decl = visitArrayDeclaration()) { // array_declaration list
		// std::cerr << "hoge\n";
		while (arr_decl) {
			arr_decl->setDeclType(ArrayDeclAST::local);
			if (std::find(begin(ArrayTable), end(ArrayTable), arr_decl->getName()) != end(ArrayTable)) {
				SAFE_DELETE(arr_decl);
				SAFE_DELETE(func_stmt);
				return NULL;
			}
			func_stmt->addArrayDeclaration(arr_decl);
			ArrayTable.push_back(arr_decl->getName());
			arr_decl = visitArrayDeclaration();
		}
		// std::cerr << "hoge" << std::endl;

		if (stmt = visitStatement()) {
			while (stmt) {
				last_stmt = stmt;
				// std::cerr << stmt->getValueID() << std::endl;
				func_stmt->addStatement(stmt);
				stmt = visitStatement();
			}
		} else if (var_decl = visitVariableDeclaration()) { // variable_declaration list
			while (var_decl) {
				var_decl->setDeclType(VariableDeclAST::local);
				if (std::find(begin(VariableTable), end(VariableTable), var_decl->getName()) != end(VariableTable)) {
					SAFE_DELETE(var_decl);
					SAFE_DELETE(func_stmt);
					return NULL;
				}
				func_stmt->addVariableDeclaration(var_decl);
				VariableTable.push_back(var_decl->getName());
				// parse Variable Declaration
				var_decl = visitVariableDeclaration();
			}
			if (stmt = visitStatement()) {
				while (stmt) {
					last_stmt = stmt;
					func_stmt->addStatement(stmt);
					stmt = visitStatement();
				}
			}
		}
	} else { // other
		SAFE_DELETE(func_stmt);
		Tokens->applyTokenIndex(tmp);
		return NULL;
	}


	// std::cerr << "fuga" << std::endl;
	// check if last statement is jump_statement
	if (not last_stmt or not llvm::isa<JumpStmtAST>(last_stmt)) {
		SAFE_DELETE(func_stmt);
		Tokens->applyTokenIndex(tmp);
		return NULL;
	}

	// }
	// std::cerr << Tokens->getCurString() << std::endl;
	if (Tokens->getCurString() == "}") {
		// std::cerr << "piyo" << std::endl;
		Tokens->getNextToken();
		return func_stmt;
	} else {
		SAFE_DELETE(func_stmt);
		Tokens->applyTokenIndex(tmp);
		return NULL;
	}
}

/*
 * VariableDeclaration用構文解析メソッド
 * @return 解析成功：VariableDeclAST、失敗：NULL
 */
VariableDeclAST* Parser::visitVariableDeclaration() {
	std::string name;
	// INT
	if (Tokens->getCurType() == TOK_INT) {
		Tokens->getNextToken();
	} else {
		return NULL;
	}
	// IDENTIFIER
	if (Tokens->getCurType() == TOK_IDENTIFIER) {
		name = Tokens->getCurString();
		Tokens->getNextToken();
	} else {
		Tokens->ungetToken(1);
		return NULL;
	}
	// ';'
	if (Tokens->getCurString() == ";") {
		Tokens->getNextToken();
		return new VariableDeclAST(name);
	} else {
		Tokens->ungetToken(2);
		return NULL;
	}
}

/*
 * ArrayDeclaration用構文解析メソッド
 * @return 解析成功：ArrayDeclAST、失敗：NULL
 */

ArrayDeclAST* Parser::visitArrayDeclaration() {
	std::string name;
	size_t size;
	// ARRAY
	if (Tokens->getCurType() == TOK_ARRAY) {
		Tokens->getNextToken();
		// std::cerr << "1\n"; 
	} else {
		return NULL;
	}
	// IDENTIFIER
	if (Tokens->getCurType() == TOK_IDENTIFIER) {
		name = Tokens->getCurString();
		Tokens->getNextToken();
	} else {
		Tokens->ungetToken(1);
		return NULL;
	}
	// [
	if (Tokens->getCurString() == "[") {
		Tokens->getNextToken();
	} else {
		Tokens->ungetToken(2);
		return NULL;
	}
	// DIGIT
	if (Tokens->getCurType() == TOK_DIGIT) {
		size = Tokens->getCurNumVal();
		Tokens->getNextToken();
	} else {
		Tokens->ungetToken(3);
		return NULL;
	}
	if (Tokens->getCurString() == "]") {
		Tokens->getNextToken();
	} else {
		Tokens->ungetToken(4);
		return NULL;
	}
	// ';'
	if (Tokens->getCurString() == ";") {
		Tokens->getNextToken();
		return new ArrayDeclAST(name, size);
	} else {
		Tokens->ungetToken(5);
		return NULL;
	}
	// example:
	// array a[5];
}

/*
 * Statement用構文解析メソッド
 * @return 解析成功：AST、失敗：NULL
 */
BaseAST* Parser::visitStatement() {
	BaseAST* stmt = NULL;
	if (stmt = visitExpressionStatement()) {
		return stmt;
	} else if (stmt = visitJumpStatement()) {
		return stmt;
	} else {
		return NULL;
	}
}

/*
 * ExpressionStatement用構文解析メソッド
 * @return 解析成功：AST、失敗：NULL
 */
BaseAST* Parser::visitExpressionStatement() {
	BaseAST* assign_expr;
	// NULL Expression
	if (Tokens->getCurString() == ";") {
		Tokens->getNextToken();
		return new NullExprAST();
	} else if (assign_expr = visitAssignmentExpression()) {
		if (Tokens->getCurString() == ";") {
			Tokens->getNextToken();
			return assign_expr;
		}
	}
	return NULL;
}

/*
 * JumpStatement用構文解析メソッド
 * @return 解析成功：AST、失敗：NULL
 */
BaseAST* Parser::visitJumpStatement() {
	const int tmp = Tokens->getCurIndex();
	BaseAST* expr;
	if (Tokens->getCurType() == TOK_RETURN) {
		Tokens->getNextToken();
		if (not (expr = visitAssignmentExpression())) {
			Tokens->applyTokenIndex(tmp);
			return NULL;
		}
		if (Tokens->getCurString() == ";") {
			Tokens->getNextToken();
			return new JumpStmtAST(expr);
		} else {
			Tokens->applyTokenIndex(tmp);
			return NULL;
		}
	} else {
		return NULL;
	}
}

/*
 * AssignmentExpression用構文解析メソッド
 * @return 解析成功：AST、解析失敗：NULL
 */
BaseAST* Parser::visitAssignmentExpression() {
	const int tmp = Tokens->getCurIndex();
	// | IDENTIFIER '=' additive_expression
	BaseAST* lhs;
	if (Tokens->getCurType() == TOK_IDENTIFIER) {
		// 変数が宣言されているか確認
		if (std::find(begin(VariableTable), end(VariableTable), Tokens->getCurString()) != end(VariableTable)) {
			lhs = new VariableAST(Tokens->getCurString());
			Tokens->getNextToken();
			BaseAST* rhs;
			if (Tokens->getCurType() == TOK_SYMBOL and 
				Tokens->getCurString() == "=") {
				Tokens->getNextToken();
				if (rhs = visitAdditiveExpression(NULL)) {
					return new BinaryExprAST("=", lhs, rhs);
				} else {
					SAFE_DELETE(lhs);
					Tokens->applyTokenIndex(tmp);
				}
			} else if (Tokens->getCurType() == TOK_SYMBOL and
				Tokens->getCurString() == "$") {
				Tokens->getNextToken();
				if (rhs = visitAdditiveExpression(NULL)) {
					return new BinaryExprAST("$", lhs, rhs); // TODO
				} else {
					SAFE_DELETE(lhs);
					Tokens->applyTokenIndex(tmp);
				}
			} else {
				SAFE_DELETE(lhs);
				Tokens->applyTokenIndex(tmp);
			}
		} else if (std::find(begin(ArrayTable), end(ArrayTable), Tokens->getCurString()) != end(ArrayTable)) {
			lhs = new ArrayAST(Tokens->getCurString());
			Tokens->getNextToken();
			BaseAST* rhs;
			if (Tokens->getCurType() == TOK_SYMBOL and 
				Tokens->getCurString() == "=") {
				Tokens->getNextToken();
				if (rhs = visitAdditiveExpression(NULL)) {
					return new BinaryExprAST("=", lhs, rhs);
				} else {
					SAFE_DELETE(lhs);
					Tokens->applyTokenIndex(tmp);
				}
			} else if (Tokens->getCurType() == TOK_SYMBOL and
				Tokens->getCurString() == "$") {
				Tokens->getNextToken();
				if (rhs = visitAdditiveExpression(NULL)) {
					return new BinaryExprAST("$", lhs, rhs); // TODO
				} else {
					SAFE_DELETE(lhs);
					Tokens->applyTokenIndex(tmp);
				}
			} else if (Tokens->getCurType() == TOK_IDENTIFIER and 
				Tokens->getCurString() == "inc") {
				Tokens->getNextToken();
				if (rhs = visitAdditiveExpression(NULL)) {
					return new BinaryExprAST("inc", lhs, rhs);
				} else {
					SAFE_DELETE(lhs);
					Tokens->applyTokenIndex(tmp);	
				}
			} else {
				SAFE_DELETE(lhs);
				Tokens->applyTokenIndex(tmp);
			}
		} else {
			Tokens->applyTokenIndex(tmp);
		}
	}
	// additive_expression
	BaseAST* add_expr = visitAdditiveExpression(NULL);
	if (add_expr) {
		return add_expr;
	}
	return NULL;
}

/*
 * AdditiveExpression用構文解析メソッド
 * @param lhs(左辺)、初回呼び出し時はNULL
 * @return 解析成功：AST、失敗：NULL
 */
BaseAST* Parser::visitAdditiveExpression(BaseAST* lhs) {
	const int tmp = Tokens->getCurIndex();
	if (not lhs) {
		lhs = visitMultiplicativeExpression(NULL);
	}
	if (not lhs) {
		return NULL;
	}
	BaseAST* rhs;
	// +
	if (Tokens->getCurType() == TOK_SYMBOL and Tokens->getCurString() == "+") {
		Tokens->getNextToken();
		rhs = visitMultiplicativeExpression(NULL);
		if (rhs) {
			return visitAdditiveExpression(new BinaryExprAST("+", lhs, rhs));
		} else {
			SAFE_DELETE(lhs);
			Tokens->applyTokenIndex(tmp);
			return NULL;
		}
	} else if (Tokens->getCurType() == TOK_SYMBOL and Tokens->getCurString() == "-") {
		Tokens->getNextToken();
		rhs = visitMultiplicativeExpression(NULL);
		if (rhs) {
			return visitAdditiveExpression(new BinaryExprAST("-", lhs, rhs));
		} else {
			SAFE_DELETE(lhs);
			Tokens->applyTokenIndex(tmp);
			return NULL;
		}
	}
	return lhs;
}

/*
 * MultiplicativeExpression用解析メソッド
 * @param lhs（左辺）、初回呼び出し時はNULL
 * @return 解析成功：AST、失敗：NULL
 */
BaseAST* Parser::visitMultiplicativeExpression(BaseAST* lhs) {
	const int tmp = Tokens->getCurIndex();
	if (not lhs) {
		lhs = visitPostfixExpression();
	}
	if (not lhs) {
		return NULL;
	}
	BaseAST* rhs;
	// *
	if (Tokens->getCurType() == TOK_SYMBOL and Tokens->getCurString() == "*") {
		Tokens->getNextToken();
		rhs = visitPostfixExpression();
		if (rhs) {
			return visitAdditiveExpression(new BinaryExprAST("*", lhs, rhs));
		} else {
			SAFE_DELETE(lhs);
			Tokens->applyTokenIndex(tmp);
			return NULL;
		}
	} else if (Tokens->getCurType() == TOK_SYMBOL and Tokens->getCurString() == "/") {
		Tokens->getNextToken();
		rhs = visitPostfixExpression();
		if (rhs) {
			return visitAdditiveExpression(new BinaryExprAST("/", lhs, rhs));
		} else {
			SAFE_DELETE(lhs);
			Tokens->applyTokenIndex(tmp);
			return NULL;
		}
	}
	return lhs;
}

/*
 * PostfixExpression用構文解析メソッド
 * @return 解析成功：AST、失敗：NULL
 */
BaseAST* Parser::visitPostfixExpression() {
	const int tmp = Tokens->getCurIndex();
	// primary_expression
	BaseAST* prim_expr = visitPrimaryExpression();
	if (prim_expr) {
		return prim_expr;
	}
	// FUNCTION_IDENTIFIER
	if (Tokens->getCurType() == TOK_IDENTIFIER) {
		// is FUNCTION_IDENTIFIER
		int param_num;
		if (PrototypeTable.count(Tokens->getCurString())) {
			param_num = PrototypeTable[Tokens->getCurString()];
		} else if (FunctionTable.count(Tokens->getCurString())) {
			param_num = FunctionTable[Tokens->getCurString()];
		} else {
			return NULL;
		}

		// 関数名取得
		std::string Callee = Tokens->getCurString();
		Tokens->getNextToken();

		// LEFT PALEN
		if (Tokens->getCurType() != TOK_SYMBOL or Tokens->getCurString() != "(") {
			Tokens->applyTokenIndex(tmp);
			return NULL;
		}
		Tokens->getNextToken();

		// argument list
		std::vector<BaseAST*> args;
		BaseAST* assign_expr = visitAssignmentExpression();
		if (assign_expr) {
			args.push_back(assign_expr);
			while (Tokens->getCurType() == TOK_SYMBOL and Tokens->getCurString() == ",") {
				Tokens->getNextToken();
				// IDENTIFIER
				assign_expr = visitAssignmentExpression();
				if (assign_expr) {
					args.push_back(assign_expr);
				} else {
					break;
				}
			}
		}

		// 引数の数を確認
		if (args.size() != param_num) {
			for (int i = 0; i < args.size(); i++) {
				SAFE_DELETE(args[i]);
			}
			Tokens->applyTokenIndex(tmp);
			return NULL;
		}

		// RIGHT PALEN
		if (Tokens->getCurType() == TOK_SYMBOL and Tokens->getCurString() == ")") {
			Tokens->getNextToken();
			return new CallExprAST(Callee, args);
		} else {
			for (int i = 0; i < args.size(); i++) {
				SAFE_DELETE(args[i]);
			}
			Tokens->applyTokenIndex(tmp);
			return NULL;
		}
	} else {
		return NULL;
	}
}

/*
 * PrimaryExpression用構文解析メソッド
 * @return 解析成功：AST、失敗：NULL
 */
BaseAST* Parser::visitPrimaryExpression() {
	const int tmp = Tokens->getCurIndex();
	// VARIABLE_IDENTIFIER
	if (Tokens->getCurType() == TOK_IDENTIFIER and
		std::find(begin(VariableTable), end(VariableTable), Tokens->getCurString()) != end(VariableTable)) {
		std::string var_name = Tokens->getCurString();
		Tokens->getNextToken();
		return new VariableAST(var_name);
	} else if (Tokens->getCurType() == TOK_DIGIT) { // integer
		auto val = Tokens->getCurNumVal();
		Tokens->getNextToken();
		return new NumberAST(val);
	} else if (Tokens->getCurType() == TOK_SYMBOL and Tokens->getCurString() == "-") { // negative integer
		Tokens->getNextToken();
		if (Tokens->getCurType() == TOK_DIGIT) {
			auto val = Tokens->getCurNumVal();
			Tokens->getNextToken();
			return new NumberAST(-val);
		} else {
			Tokens->applyTokenIndex(tmp);
			return NULL;
		}
	} else if (Tokens->getCurType() == TOK_SYMBOL and Tokens->getCurString() == "(") { // '(' expression ')'
		Tokens->getNextToken();
		// expression
		BaseAST* assign_expr;
		if (not (assign_expr = visitAssignmentExpression())) {
			Tokens->applyTokenIndex(tmp);
			return NULL;
		}
		// RIGHT PALEN
		if (Tokens->getCurString() == ")") {
			Tokens->getNextToken();
			return assign_expr;
		} else {
			SAFE_DELETE(assign_expr);
			Tokens->applyTokenIndex(tmp);
			return NULL;
		}
	}
	return NULL;
}