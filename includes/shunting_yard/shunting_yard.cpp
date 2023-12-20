#include "shunting_yard.h"
using namespace std;

ShuntingYard::ShuntingYard(){
    _queue = Queue<Token*>();
    _stack = Stack<Token*>();
}

ShuntingYard::ShuntingYard(const Queue<Token*>& input_q){
    infix(input_q);
}

void ShuntingYard::infix(const Queue<Token*>& input_q){
    _queue = input_q;
    _stack = Stack<Token*>();
}

Queue<Token*> ShuntingYard::postfix(){ 
    return shunting_yard();
}

Queue<Token*> ShuntingYard::postfix(const Queue<Token*>& input_q){
    infix(input_q);
    return shunting_yard();
}

Queue<Token*> ShuntingYard::shunting_yard(){
    Queue<Token*> result;

    while (_queue.size() != 0){
        Token* token = _queue.pop();

        switch (token->tokenType()){
            case TOKENSTR:
                result.push(token);
                break;

            case RELATIONAL:
                _stack.push(token);
                break;
            
            case LOGICAL:{
                while (_stack.size() != 0 && _stack.top()->tokenType() != LPAREN && compare(_stack.top(), token))
                    result.push(_stack.pop());

                _stack.push(token);
                break;
            }

            case LPAREN:
                _stack.push(token);
                break;

            case RPAREN:
                while (_stack.top()->tokenType() != LPAREN){
                    assert(_stack.size() != 0 && "MISSING L PARANTHESIS");
                    result.push(_stack.pop());
                }
                assert(_stack.top()->tokenType() == LPAREN && "MISSING L PARANTHESIS");
                _stack.pop();
                break;

            default:
                break;
        }
    }
    while (_stack.size() != 0){
        // assert(_stack.top()->TypeOf() != LPAREN && "PARANTHESIS PROBLEM!");
        result.push(_stack.pop());
    }
    return result;
}