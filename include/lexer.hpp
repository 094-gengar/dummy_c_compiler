#ifndef LEXER_HPP
#define LEXER_HPP

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <list>
#include <string>
#include <vector>

#include "APP.hpp"

/*
 * token enum
 */
enum TokenType {
	TOK_IDENTIFIER,
	TOK_DIGIT,
	TOK_SYNBOL,
	TOK_INT,
	TOK_RETURN,
	TOK_EOF
};

/*
 * 個別 token class
 */
typedef class Token {
private:
	TokenType Type;
	std::string TokenString;
	int Number; // TODO
	int Line;

public:
	Token(std::string string, TokenType type, int line)
		: TokenString(string), Type(type), Line(line) {
		if (type == TOK_DIGIT) {
			Number = atoi(string.c_str());
		} else {
			Number = 0x7fffffff;
		}
	}
	~Token() {}

	TokenType getTokenType() { return Type; }
	std::string getTokenString() { return TokenString; }
	int getNumberValue() { return Number; }
	bool setLine(int line) { Line = line; return true; }
	int getLine() { return Line; }
} Token;

/*
 * 切り出したToken格納用クラス
 */
class TokenStream {
private:
	std::vector<Token*> Tokens;
	int CurIndex;
public:
	TokenStream() : CurIndex(0) {}
	~TokenStream();
	bool ungetToken(int Times = 1);
	bool getNextToken();
	bool pushToken(Token* token) {
		Tokens.push_back(token);
		return true;
	}
	Token getToken();
	TokenType getCurType() { return Tokens[CurIndex]->getTokenType(); }
	std::string getCurString() { return Tokens[CurIndex]->getTokenString(); }
	int getCurNumVal() { return Tokens[CurIndex]->getNumberValue(); }
	bool printTokens();
	int getCurIndex() { return CurIndex; }
	bool applyTokenIndex(int index) { CurIndex = index; return true; }
};

TokenStream* LexicalAnalysis(std::string input_filename);

#endif