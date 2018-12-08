#include "CheckBalanced.h"
#include <stack>

using namespace std;

bool CheckBalancedParentheses(std::string input) {
    stack<char> stk;
    //Finish The Function :D
    for (unsigned int i = 0; i < input.length(); i++) {
        if (input.at(i) == '(') {
        	stk.push(input.at(i));
        }
        else if (input.at(i) == ')') {
        	if (stk.empty()) {
        		return false;
        	}
        	stk.pop();
        }
    }
    return stk.empty();
}

bool CheckBalancedAll(std::string input) {
    stack<char> stk;
    //Finish The Function :D
	for (unsigned int i = 0; i < input.length(); i++) {
        if (input.at(i) == '(') {
        	stk.push(input.at(i));
        }
        else if (input.at(i) == ')') {
        	if (stk.empty() || stk.top() != '(') {
        		return false;
        	}
        	stk.pop();
        }
        else if (input.at(i) == '[') {
        	stk.push(input.at(i));
        }
        else if (input.at(i) == ']') {
        	if (stk.empty() || stk.top() != '[') {
        		return false;
        	}
        	stk.pop();
        }
        else if (input.at(i) == '{') {
        	stk.push(input.at(i));
        }
        else if (input.at(i) == '}') {
        	if (stk.empty() || stk.top() != '{') {
        		return false;
        	}
        	stk.pop();
        }
    }
    return stk.empty();
}
