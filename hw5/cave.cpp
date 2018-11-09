#include <iostream>
#include <stack>
#include <sstream>

using namespace std;

int main() {
    //take input string
    string input;
    getline(cin, input);
    stack<char> path;

    //loop through string
    for (unsigned int i = 0; i < input.length(); i++) {
        char dir = input.at(i);
        //if stack is empty and the char is a direction then push onto the stack
        if (path.empty() && (dir == 'n' || dir == 's' || dir == 'e' || dir == 'w')) {
            path.push(dir);
        }
        //if stack is not empty pop the top if it is the opposite of the current char
        //else push the direction onto the stack
        else if (dir == 'n') {
            if (path.top() == 's') {
                path.pop();
                continue;
            }
            path.push(dir);
        }
        else if (dir == 's') {
            if (path.top() == 'n') {
                path.pop();
                continue;
            }
            path.push(dir);
        }
        else if (dir == 'e') {
            if (path.top() == 'w') {
                path.pop();
                continue;
            }
            path.push(dir);
        }
        else if (dir == 'w') {
            if (path.top() == 'e') {
                path.pop();
                continue;
            }
            path.push(dir);
        }
        //if the char is not a direction return invalid
        else {
            cout << "invalid" << endl;
            return 1;
        }
    }

    //if stack is empty then the rope is rolled up
    if (path.empty()) {
        cout << "rolled up" << endl;
        return 0;
    }

    //else it is not rolled up
    else {
        cout << "not rolled up" << endl;
        return 0;
    }
}