#include "AllCombos.h"
#include <iostream>

//you may write any helper functions you need
using namespace std;

int main (){
    vector<string> result;
    AllCombos(result, "USC", 2);
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << endl;
    }
}

void AllCombos(vector<string>& result, string input, int k){
	string word = "";
    helper(result, input, word, 0, input.length() - 1, 0, k);
}

void helper(vector<string>& result, string input, string& output, int begin, int end, int index, int k) {
    if (index == k) {
        string outputcopy = output;
        result.push_back(outputcopy);
        return;
    }
    for (int i = begin; i <= end && end - i + 1 >= k - index; i++) {
        output.insert(index, string(1, input.at(i)));
        helper(result, input, output, i + 1, end, index + 1, k);
    }
}
