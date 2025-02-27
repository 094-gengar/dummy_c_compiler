#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <map>
#include <vector>
#include <llvm/Support/Casting.h>
#include <llvm/Support/Error.h>
#include "APP.hpp"

//
// AST
//

/*
 * クラス宣言
 */
class BaseAST;
class TranslationUnitAST;
class FunctionAST;
class PrototypeAST;
class FunctionStmtAST;
class VariableDeclAST;

class ArrayDeclAST;

class BinaryExprAST;
class NullExprAST;
class CallExprAST;
class JumpStmtAST;
class VariableAST;
class ArrayAST;
class NumberAST;

/*
 * ASTの種類
 */
enum AstID {
	BaseID,
	VariableDeclID,
	ArrayDeclID,
	BinaryExprID,
	NullExprID,
	CallExprID,
	JumpStmtID,
	VariableID,
	NumberID
};

const int64_t Infty = (int64_t)(INT32_MAX) << 2;

// 基底
class BaseAST {
	AstID ID;
	// int64_t Upper;
public:
	BaseAST(AstID id) : ID(id) {}
	// BaseAST(AstID id) : ID(id), Upper(Infty) {}
	virtual ~BaseAST() {}
	AstID getValueID() const { return ID; }
	// void UpdateUpper(int64_t x) { Upper = x; }
	// int64_t getUpper() { return Upper; }	
};

// ソースコード
class TranslationUnitAST {
	std::vector<PrototypeAST*> Prototypes;
	std::vector<FunctionAST*> Functions;
public:
	TranslationUnitAST() {}
	~TranslationUnitAST();
	bool addPrototype(PrototypeAST* proto);
	bool addFunction(FunctionAST* func);
	bool empty();
	PrototypeAST* getPrototype(int i) {
		if (i < Prototypes.size()) {
			return Prototypes.at(i);
		} else {
			return NULL;
		}
	}
	FunctionAST* getFunction(int i) {
		if (i < Functions.size()) {
			return Functions.at(i);
		} else {
			return NULL;
		}
	}
};

// 関数宣言
class PrototypeAST {
	std::string Name;
	std::vector<std::string> Params;
public:
	PrototypeAST(const std::string& name, const std::vector<std::string>& params)
		: Name(name), Params(params) {}
	std::string getName() { return Name; }
	std::string getParamName(int i) { if (i < Params.size()) { return Params.at(i); } else {return NULL; } }
	int getParamNum() { return Params.size(); }
};

// 関数定義
class FunctionAST {
	PrototypeAST* Proto;
	FunctionStmtAST* Body;
public:
	FunctionAST(PrototypeAST* proto, FunctionStmtAST* body) : Proto(proto), Body(body) {}
	~FunctionAST();
	std::string getName() { return Proto->getName(); }
	PrototypeAST* getPrototype() { return Proto; }
	FunctionStmtAST* getBody() { return Body; }
};

// 関数定義（本文）
class FunctionStmtAST {
	std::vector<VariableDeclAST*> VariableDecls;
	std::vector<ArrayDeclAST*> ArrayDecls;
	std::vector<BaseAST*> StmtLists;
public:
	FunctionStmtAST() {}
	~FunctionStmtAST();
	bool addVariableDeclaration(VariableDeclAST* vdecl);
	bool addArrayDeclaration(ArrayDeclAST* vdecl);
	bool addStatement(BaseAST* stmt) { StmtLists.push_back(stmt); return true; }
	VariableDeclAST* getVariableDecl(int i) { if (i < VariableDecls.size()) { return VariableDecls.at(i); } else { return NULL; } }
	ArrayDeclAST* getArrayDecl(int i) { if (i < ArrayDecls.size()) { return ArrayDecls.at(i); } else { return NULL; } }
	BaseAST* getStatement(int i) { if (i < StmtLists.size()) { return StmtLists.at(i); } else { return NULL; } }
};

// 変数宣言
class VariableDeclAST : public BaseAST {
public:
	typedef enum {
		param,
		local
	} DeclType;
private:
	std::string Name;
	DeclType Type;
public:
	VariableDeclAST(const std::string& name) : BaseAST(VariableDeclID), Name(name) {}
	static inline bool classof(VariableDeclAST const*) { return true; }
	static inline bool classof(BaseAST const* base) {
		return base->getValueID() == VariableDeclID;
	}
	~VariableDeclAST() {}
	bool setDeclType(DeclType type) { Type = type; return true; }
	std::string getName() { return Name; }
	DeclType getType() { return Type; }
};

// array decl
class ArrayDeclAST : public BaseAST {
public:
	typedef enum {
		param,
		local
	} DeclType;
private:
	std::string Name;
	size_t Size;
	DeclType Type;
public:
	ArrayDeclAST(const std::string& name, size_t size) : BaseAST(VariableDeclID), Name(name), Size(size) {}
	static inline bool classof(ArrayDeclAST const*) { return true; }
	static inline bool classof(BaseAST const* base) {
		return base->getValueID() == ArrayDeclID;
	}
	~ArrayDeclAST() {}
	bool setDeclType(DeclType type) { Type = type; return true; }
	std::string getName() { return Name; }
	size_t getSize() { return Size; }
	DeclType getType() { return Type; }
};

// 二項演算
class BinaryExprAST : public BaseAST {
	std::string Op;
	BaseAST* LHS, * RHS;
public:
	BinaryExprAST(std::string op, BaseAST* lhs, BaseAST* rhs)
		: BaseAST(BinaryExprID), Op(op), LHS(lhs), RHS(rhs) {
		// (*this).UpdateUpper(lhs->getUpper() + rhs->getUpper());
	}
	~BinaryExprAST() { SAFE_DELETE(LHS); SAFE_DELETE(RHS); }
	static inline bool classof(BinaryExprAST const*) { return true; }
	static inline bool classof(BaseAST const* base) {
		return base->getValueID() == BinaryExprID;
	}
	std::string getOp() { return Op; }
	BaseAST* getLHS() { return LHS; }
	BaseAST* getRHS() { return RHS; }
};

// ;
class NullExprAST : public BaseAST {
public:
	NullExprAST() : BaseAST(NullExprID) {}
	static inline bool classof(NullExprAST const*) { return true; }
	static inline bool classof(BaseAST const* base) {
		return base->getValueID() == NullExprID;
	}
};

// 関数呼び出し
class CallExprAST : public BaseAST {
	std::string Callee;
	std::vector<BaseAST*> Args;
public:
	CallExprAST(const std::string& callee, std::vector<BaseAST*>& args)
		: BaseAST(CallExprID), Callee(callee), Args(args) {}
	~CallExprAST();
	std::string getCallee() { return Callee; }
	BaseAST* getArgs(int i) { if (i < Args.size()) { return Args.at(i); } else { return NULL; } }
	static inline bool classof(CallExprAST const*) { return true; }
	static inline bool classof(BaseAST const* base) {
		return base->getValueID() == CallExprID;
	}
};

// ジャンプ（今回はreturn）
class JumpStmtAST : public BaseAST {
	BaseAST* Expr;
public:
	JumpStmtAST(BaseAST* expr) : BaseAST(JumpStmtID), Expr(expr) {}
	~JumpStmtAST() { SAFE_DELETE(Expr); }
	BaseAST* getExpr() { return Expr; }
	static inline bool classof(JumpStmtAST const*) { return true; }
	static inline bool classof(BaseAST const* base) {
		return base->getValueID() == JumpStmtID;
	}
};

// 変数参照（整数）
class VariableAST : public BaseAST {
	std::string Name;
public:
	VariableAST(const std::string& name) : BaseAST(VariableID), Name(name) {}
	~VariableAST() {}
	static inline bool classof(VariableAST const*) { return true; }
	static inline bool classof(BaseAST const* base) {
		return base->getValueID() == VariableID;
	}
	std::string getName() { return Name; }
};

// 配列参照
class ArrayAST : public BaseAST {
	std::string Name;
public:
	ArrayAST(const std::string& name) : BaseAST(VariableID), Name(name) {}
	~ArrayAST() {}
	static inline bool classof(ArrayAST const*) { return true; }
	static inline bool classof(BaseAST const* base) {
		return base->getValueID() == VariableID;
	}
	std::string getName() { return Name; }
};

// 整数
class NumberAST : public BaseAST {
	int64_t Val; // TODO
public:
	NumberAST(int64_t val) : BaseAST(NumberID), Val(val) {
		//  (*this).UpdateUpper(val);
	};
	~NumberAST() {}
	int64_t getNumberValue() { return Val; }
	static inline bool classof(NumberAST const*) { return true; }
	static inline bool classof(BaseAST const* base) {
		return base->getValueID() == NumberID;
	}
};

#endif