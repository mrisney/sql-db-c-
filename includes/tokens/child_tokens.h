#ifndef CHILD_TOKENS_H
#define CHILD_TOKENS_H

#include "token.h"
using namespace std;

class TokenStr : public Token{
public:
    TokenStr(){ _val = ""; }
    TokenStr(const string& value){ _val = value; }
    ~TokenStr(){ }
    void print(ostream &outs = cout) const { outs << "[" << _val << "]"; }
    TOKENS tokenType() const { return TOKENSTR; }
    string toString() const { return _val; }

private:
    string _val;
};

class Relational : public Token{
public:
    Relational(){ _val = ""; }
    Relational(const string& value){ _val = value; }
    ~Relational(){ }
    void print(ostream &outs = cout) const { outs << "[" << _val << "]"; }
    TOKENS tokenType() const { return RELATIONAL; }
    string toString() const { return _val; }

private:
    string _val;
};

class Logical : public Token{
public:
    Logical(){ _val = ""; }
    Logical(const string& value){ _val = value; }
    ~Logical(){ }
    void print(ostream &outs = cout) const { outs << "[" << _val << "]"; }
    TOKENS tokenType() const { return LOGICAL; }
    string toString() const { return _val; }

private:
    string _val;
};

class LParen : public Token{
public:
    LParen(){ }
    ~LParen(){ }
    void print(ostream &outs = cout) const { outs << "[L]"; }
    TOKENS tokenType() const { return LPAREN; }
    string toString() const { return "("; }
};

class RParen : public Token{
public:
    RParen(){ } 
    ~RParen(){ }
    void print(ostream &outs = cout) const { outs << "[R]"; }
    TOKENS tokenType() const { return RPAREN; }
    string toString() const { return ")"; }
};
#endif //CHILD_TOKENS_H