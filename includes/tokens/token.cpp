#include "token.h"
using namespace std;

Token::Token(){ }

// Virtual destructor 
Token::~Token() { 
    std::cout << "Token destroyed" << std::endl;
}


ostream& operator<<(std::ostream& outs, const Token& token) {
    token.print(outs);
    return outs;
}

void Token::print(std::ostream& outs) const {
    outs << "Token [Type: " << tokenType() << ", Value: \"" << toString() << "\"]";
}

bool compare(const Token* t1, const Token* t2) {
    // Return false if either token is null (or handle differently based on your context)
    if (!t1 || !t2) {
        throw std::invalid_argument("Null Token passed to compare.");
    }

    // Compare tokens if both are of type LOGICAL
    if (t1->tokenType() == LOGICAL && t2->tokenType() == LOGICAL) {
        const string& t1Value = t1->toString();
        const string& t2Value = t2->toString();

        // Specific rule: "and" is considered less than "or"
        if (t1Value == "and" && t2Value == "or") {
            return true;
        }

        // Check if values are the same
        return t1Value == t2Value;
    }

    // Default comparison based on token types
    return t1->tokenType() < t2->tokenType();
}
