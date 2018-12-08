#ifndef ALLCOMBOS_H
#define ALLCOMBOS_H

#include <string>
#include <vector>

void AllCombos(std::vector<std::string>& result, std::string input, int n);
void helper(std::vector<std::string>& result, std::string input, std::string& output, int begin, int end, int index, int k);

#endif