#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "stackint.h"

using namespace std;

int evaluate(stringstream& formula);
int malformed(StackInt* stack);

int main(int argc, char* argv[]) {
    const int MALFORMED = -9;
    const int WHITESPACE = -10;
    //check if input file included
    if (argc != 2) {
        return 1;
    }
    //create stream to read file
    ifstream inFile;
    inFile.open(argv[1]);
    if (inFile.fail()) {
        return 1;
    }
    //loop until end of file is reached
    while (!inFile.eof()) {
        stringstream formula;
        string line;
        getline(inFile, line);
        //skip empty lines
        if (line.empty()) {
            continue;
        }
        //parse string line into a stringstream
        formula << line;
        //evaluate the formula
        int evaluated = evaluate(formula);
        //move to next line if malformed
        if (evaluated == MALFORMED || evaluated == WHITESPACE) {
            continue;
        }
        //print the value of the expression
        cout << evaluated << endl;
    }
	return 0;
}

int evaluate(stringstream& formula) {
    //set values for characters
    const int OPEN_PAREN = -1;
    const int ADD = -2;
    const int MULTIPLY = -3;
    const int SHIFT_LEFT = -4;
    const int SHIFT_RIGHT = -5;   
    const int WHITESPACE = -10;
    //initialize a stack
    StackInt* stack = new StackInt();
    //create a char and parse the first character in formula to it
    char character;
    formula >> character;
    //check if line is just whitespace
    string line = formula.str();
    unsigned int i = 0;
    while (line.at(i) == ' ' || line.at(i) == '\t') {
        if (i == line.length() - 1) {
            return WHITESPACE;
        }
        i++;
    }
    //loop until end of line is reached
    while (!formula.eof()) {
        //if the character is not a number
        if (!isdigit(character)) {
            //check for which character it is
            if (character == ' ') {
                continue;
            }
            if (character == '(') {
                //malformed if a number is followed by an open is parentheses
                if (!stack -> empty() && stack -> top() > -1) {
                    return malformed(stack);
                }
                stack -> push(OPEN_PAREN);
            }
            else if (character == '+') {
                stack -> push(ADD);
            }
            else if (character == '*') {
                stack -> push(MULTIPLY);
            }
            else if (character == '<') {
                stack -> push(SHIFT_LEFT);
            }
            else if (character == '>') {
                stack -> push(SHIFT_RIGHT);
            }
            //return malformed if the character is not any of the above or a closed parentheses
            else if (character != ')') {
                return malformed(stack);
            }
            //evaluate the stack if the character is a closed parentheses
            else {
                //return malformed if there is only one or zero characters left
                if (stack -> size() < 2) {
                    return malformed(stack);
                }
                //return malformed if the top of the stack is not a number
                if (stack -> top() < 0) {
                    return malformed(stack);
                }
                else {
                    int total = 0;
                    //string to see if multiply and add are used in the same set of parentheses
                    char addOrMultiply = ' ';
                    //loop until an open parentheses has been reached
                    while (stack -> top() != OPEN_PAREN) {
                        //give total the value of top of the stack
                        if (stack -> top() > -1) {
                            total = stack -> top();
                            stack -> pop();
                        }
                        //if the top of the stack is not a number enter
                        if (!stack -> empty() && stack -> top() < 0) {
                            //adding numbers
                            if (stack -> top() == ADD) {
                                //return malformed if multiply was used
                                if (addOrMultiply == 'm') {
                                    return malformed(stack);
                                }   
                                addOrMultiply = 'a';
                                //keep on adding until the top of the stack is not add
                                while (stack -> top() == ADD) {
                                    stack -> pop();
                                    //return malformed if the top of the stack is not a number
                                    if (stack -> top() < 0) {
                                        return malformed(stack);
                                    }
                                    //store the number we are adding
                                    int secondNum = stack -> top();
                                    stack -> pop();
                                    //check to see if there are shifts for the number
                                    while (stack -> top() == SHIFT_LEFT || stack -> top() == SHIFT_RIGHT) {
                                        if (stack -> top() == SHIFT_LEFT) {
                                            secondNum *= 2;
                                        }
                                        else {
                                            secondNum /= 2;
                                        }
                                        stack -> pop();
                                    }
                                    //add to total
                                    total += secondNum;
                                }
                            }
                            //multiplying numbers
                            else if (stack -> top() == MULTIPLY) {
                                //return malformed if add was used
                                if (addOrMultiply == 'a') {
                                    return malformed(stack);
                                }
                                addOrMultiply = 'm';
                                //keep on multiplying until the top of the stack is not multiply
                                while (stack -> top() == MULTIPLY) {
                                    stack -> pop();
                                    //return malformed if the top of the stack is not a number
                                    if (stack -> top() < 0) {
                                        return malformed(stack);
                                    }
                                    //store the number we are multiplying
                                    int secondNum = stack -> top();
                                    stack -> pop();
                                    //check to see if there are shifts for the number
                                    while (stack -> top() == SHIFT_LEFT || stack -> top() == SHIFT_RIGHT) {
                                        if (stack -> top() == SHIFT_LEFT) {
                                            secondNum *= 2;
                                        }
                                        if (stack -> top() == SHIFT_RIGHT) {
                                            secondNum /= 2;
                                        }
                                        stack -> pop();
                                    }
                                    //add to total
                                    total *= secondNum;
                                }
                            }
                            //check for shifters
                            else if (stack -> top() == SHIFT_LEFT || stack -> top() == SHIFT_RIGHT) {
                                while (stack -> top() == SHIFT_LEFT || stack -> top() == SHIFT_RIGHT) {
                                    if (stack -> top() == SHIFT_LEFT) {
                                        total *= 2;
                                    }
                                    else {
                                        total /= 2;
                                    }
                                    stack -> pop();
                                }
                            }
                            //exit loop if open parentheses is reached
                            else {
                                break;
                            }
                        } 
                    }
                    //return malformed if no adding or multiplying in parentheses
                    if (addOrMultiply == ' ') {
                        return malformed(stack);
                    }
                    //add the total to top of stack
                    stack -> pop();
                    stack -> push(total);
                }
            }
            //move to next character
            formula >> character;
        }
        //if the character is a digit
        else {
            //create a string to combine the char of digits
            string num(1, character);
            formula >> character;
            while (!formula.eof() && isdigit(character)) {
                num += character;
                formula >> character;
            }
            //change the string to an int
            stringstream ss(num);
            int number;
            ss >> number;
            //return malformed if the top of the stack is a number
            if (stack -> size() > 1 && stack -> top() > -1) {
                return malformed(stack);
            }
            //push the number
            stack -> push(number);
        }
    }
    //return malformed if the top of the stack is not a number
    if (stack -> top() < 0) {
        return malformed(stack);
    }
    int final = stack -> top();
    stack -> pop();
    //return final value if the stack is empty after popping
    if (stack -> empty()) {
        delete stack;
        return final;
    }
    //evaluate the shifters onto the final value
    else {
        while (!stack -> empty()) {
            if (stack -> top() == SHIFT_LEFT) {
                final *= 2;
            }
            else if (stack -> top() == SHIFT_RIGHT) {
                final /= 2;
            }
            else {
                return malformed(stack);
            }
            stack -> pop();
        }
        while (!stack -> empty()) {
            stack -> pop();
        }
        delete stack;
        return final;
    }
    while (!stack -> empty()) {
        stack -> pop();
    }
    delete stack;
    return final;
}

int malformed(StackInt* stack) {
    const int MALFORMED = -9;
    cout << "Malformed" << endl;
    //clear stack
    while (!stack -> empty()) {
        stack -> pop();
    }
    delete stack;
    return MALFORMED;
}