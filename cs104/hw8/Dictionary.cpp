#include <iostream>
#include <fstream>
#include <ostream>
#include "Dictionary.h"

using namespace std;

//add all words to set
Dictionary::Dictionary(std::string dictionary_file_name) {
	std::ifstream ifile(dictionary_file_name.c_str());
	_trie = new TrieSet();
	if (ifile.fail()) {
		return;
	}
	while (!ifile.eof()) {
		std::string word;
		ifile >> word;
		_trie -> insert(word);
	}
	ifile.close();
}

//clear the set
Dictionary::~Dictionary() {
	delete _trie;
	dictionary.clear();
}

//look for word in dictionary
bool Dictionary::isLegalWord(std::string const & word) {
	std::string lowercase = "";
	for (unsigned int i = 0; i < word.length(); i++) {
		lowercase += std::tolower(word[i]);
	}
	TrieNode* node = _trie -> prefix(lowercase);
	return node && node -> inSet;
}

//check if string is prefix of any words with trie
bool Dictionary::isLegalPrefix(TrieNode* node, std::string prefix) {
	std::string lowercase = "";
	for (unsigned int i = 0; i < prefix.length(); i++) {
		lowercase += std::tolower(prefix[i]);
	}
	if (node == NULL) {
		node = _trie -> getRoot();
	}
	return _trie -> prefix(node, lowercase) != NULL;
}

//check if string is prefix of any words
bool Dictionary::isLegalPrefix(std::string prefix) {
	return isLegalPrefix(NULL, prefix);
}

//get the root of the trie
TrieNode* Dictionary::getRoot() {
	return _trie -> getRoot();
}

//look for words with the prefix
TrieNode* Dictionary::search(TrieNode* node, std::string prefix) {
	return _trie -> prefix(node, prefix);
}