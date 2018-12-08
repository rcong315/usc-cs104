#include "hashtables.h"

#include <utility>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
#include <iostream>
#include <string>

using namespace std; 

//case does not matter
//ignore special characters ie. only consider letters a-z

bool isAnagram(std::string s, std::string t) {
    unordered_map<char, int> map;
    for (int i = 0; i < s.size(); i++) {
        if ((int) s[i] >= 65 && (int) s[i] <= 90) {
            map[tolower(s[i])]++;
        }
        else if ((int) s[i] >= 97 && (int) s[i] <= 122){
            map[s[i]]++;
        }
    }
    for (int i = 0; i < t.size(); i++) {
        if ((int) t[i] >= 65 && (int) t[i] <= 90) {
            t[i] = tolower(t[i]);
        }
        if (map.find(t[i]) != map.end()){
            map[t[i]]--;
        }
    }
    for (auto x : map) {
        if (x.second != 0) {
            return false;
        }
    }
    return true;
}

//output FIRST pair found

pair<int, int> twoSum(vector<int> input, int target) {
    unordered_map<char, int> map;
    for (int i = 0; i < input.size(); i++) {
        map[target-input.at(i)] = i;
        if (map.count(input.at(i)) != 0) {
            return make_pair(map[input.at(i)], i);
        }
    }
    return make_pair(-1, -1);
}