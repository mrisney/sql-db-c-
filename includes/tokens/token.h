#ifndef TOKEN_H
#define TOKEN_H

#include "../tokenizer/constants.h"


class Token{
public:
    Token();
    virtual ~Token();
    friend ostream& operator <<(std::ostream& outs, const Token* token);
    friend ostream& operator <<(std::ostream& outs, const Token& token);
    virtual void print(std::ostream& outs = cout) const = 0;
    virtual TOKENS tokenType() const = 0;
    virtual string toString() const = 0;
};

bool compare(const Token* t1, const Token* t2);

#endif //TOKEN_H