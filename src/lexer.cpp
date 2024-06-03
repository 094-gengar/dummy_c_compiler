#include "lexer.hpp"

/*
 * トークン切り出し関数
 * @param 字句解析対象ファイル名
 * @return 切り出したトークンを格納したTokenStream 
 */
TokenStream* LexicalAnalysis(std::string input_filename) {
	TokenStream* tokens = new TokenStream();
	std::ifstream ifs;
	std::string cur_line;
	std::string token_str;
	int line_num = 0;
	bool iscomment = false;

	ifs.open(input_filename.c_str(), std::ios::in);
	if (not ifs) {
		return NULL;
	}
	while (ifs and getline(ifs, cur_line)) {
		char next_char;
		std::string line;
		Token* next_token;
		int index = 0;
		int len = cur_line.length();
		while (index< len) {
			next_char = cur_line.at(index++);
			// コメントアウト読み飛ばし
			if (iscomment) {
				if ((len - index) < 2 or cur_line.at(index) != '*' or cur_line.at(index++) != '/') {
					continue;
				} else {
					iscomment = false;
				}
			}
			// EOF
			if (next_char == EOF) {
				token_str = EOF;
				next_token = new Token(token_str, TOK_EOF, line_num);
			} else if (isspace(next_char)) {
				continue;
			} else if (isalpha(next_char)) { // IDENTIFIER
				token_str += next_char;
				next_char = cur_line.at(index++);
				while (isalnum(next_char)) {
					token_str += next_char;
					next_char = cur_line.at(index++);
					if (index == len) {
						break;
					}
				}
				index--;
				if (token_str == "int") {
					next_token = new Token(token_str, TOK_INT, line_num);
				} else if(token_str == "return") {
					next_token = new Token(token_str, TOK_RETURN, line_num);
				} else {
					next_token = new Token(token_str, TOK_IDENTIFIER, line_num);
				}
			} else if (isdigit(next_char)) { // 数字
				if (next_char == '0') {
					token_str += next_char;
					next_token = new Token(token_str, TOK_DIGIT, line_num);
				} else {
					token_str += next_char;
					next_char = cur_line.at(index++);
					while (isdigit(next_char)) {
						token_str += next_char;
						next_char = cur_line.at(index++);
					}
					next_token = new Token(token_str, TOK_DIGIT, line_num);
					index--;
				}
			} else if (next_char == '/') { // コメント or '/'
				token_str += next_char;
				next_char = cur_line.at(index++);

				if (next_char == '/') { // 1行コメントの場合
					break;
				} else if (next_char == '*') { // 2行コメントの場合
					iscomment = true;
					continue;
				} else { // div
					index--;
					next_token = new Token(token_str, TOK_SYNBOL, line_num);
				}
			} else { // それ以外
				if (next_char == '*' or
					next_char == '+' or
					next_char == '-' or
					next_char == '=' or
					next_char == ';' or
					next_char == ',' or
					next_char == '(' or
					next_char == ')' or
					next_char == '{' or
					next_char == '}') {
					token_str += next_char;
					next_token = new Token(token_str, TOK_SYNBOL, line_num);
				} else {
					fprintf(stderr, "unclear token : %c", next_char);
					SAFE_DELETE(tokens);
					return NULL;
				}
			}

			// Tokensに追加
			tokens->pushToken(next_token);
			token_str.clear();
		}
		token_str.clear();
		line_num++;
	}

	if (ifs.eof()) {
		tokens->pushToken(new Token(token_str, TOK_EOF, line_num));
	}
	ifs.close();
	return tokens;
}

/*
 * デストラクタ
 */
TokenStream::~TokenStream() {
	for (int i = 0; i < Tokens.size(); i++) {
		SAFE_DELETE(Tokens[i]);
	}
	Tokens.clear();
}

/*
 * トークン取得
 * @return CurIndex番目のToken
 */
Token TokenStream::getToken() {
	return *Tokens[CurIndex];
}

/*
 * インデックスを一つ増やして次のトークンに進める
 * @return 成功/失敗→T/F
 */
bool TokenStream::getNextToken() {
	int siz = Tokens.size();
	if (--siz == CurIndex) {
		return false;
	} else if (CurIndex < siz) {
		CurIndex++;
		return true;
	} else {
		return false;
	}
}

/*
 * インデックスをtimes回戻す
 * @return 成功/失敗→T/F
 */
bool TokenStream::ungetToken(int times) {
	for (int i = 0; i < times; i++) {
		if (CurIndex == 0) {
			return false;
		} else {
			CurIndex--;
		}
	}
	return true;
}

/*
 * 格納されたトークン一覧を表示する
 */
bool TokenStream::printTokens() {
	std::vector<Token*>::iterator t_iter = begin(Tokens);
	while (t_iter != end(Tokens)) {
		fprintf(stdout, "%d:", (*t_iter)->getTokenType());
		if ((*t_iter)->getTokenType() != TOK_EOF) {
			fprintf(stdout, "%s\n", (*t_iter)->getTokenString().c_str());
		}
		t_iter++;
	}
	return true;
}