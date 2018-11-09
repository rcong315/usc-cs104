#include "stackint.h"

StackInt::StackInt() {
    
}

StackInt::~StackInt() {
    
}

bool StackInt::empty() const {
    //check if stack is empty
    return stack.empty();
}

void StackInt::push(const int& val) {
    //add item  with value val to stack
    stack.push(val);
}

int StackInt::top() const {
    //get the value of the last item in the stack
    return stack.top();
}

void StackInt::pop() {
    //remove the last item in the stack
    stack.pop();
}

int StackInt::size() {
    //return the size of the stack
    return stack.size();
}