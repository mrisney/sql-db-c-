#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../tokens/child_tokens.h"
using namespace std;

class ShuntingYard{
public:
    ShuntingYard();
    ShuntingYard(const Queue<Token*>& input_q);
    void infix(const Queue<Token*>& input_q);
    
    Queue<Token*> postfix();                     
    Queue<Token*> postfix(const Queue<Token*>& input_q);
    Queue<Token*> shunting_yard(); 

private:
    Queue<Token*> _queue;
    Stack<Token*> _stack;
};

#endif //SHUNTING_YARD_H