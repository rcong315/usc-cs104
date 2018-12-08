#include <iostream>
#include <fstream>
#include <ostream>
#include "Dictionary.h"

//add all words to set
Dictionary::Dictionary (std::string dictionary_file_name) {
    std::ifstream ifile(dictionary_file_name.c_str());
    if (ifile.fail()) {
        return;
    }
    while (!ifile.eof()) {
        std::string word;
        ifile >> word;
        dictionary.insert(word);
    }   
    ifile.close();
}

//clear the set
Dictionary::~Dictionary () {
    dictionary.clear();
}

//look for word in dictionary
bool Dictionary::isLegalWord (std::string const & word) const {
    std::set<std::string>::iterator it = dictionary.find(word);
    if (it == dictionary.end()) {
        return false;
    }
    return true;
}