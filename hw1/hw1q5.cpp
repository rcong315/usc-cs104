#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Please enter file" << endl;
		return -1;
	}
	ifstream inFile;
	string* array;
	int num;
	string word;
	inFile.open(argv[1]);
	if (inFile.fail()) {
		return 1;
	}
	inFile >> num;
	array = new string[num];
	for (int i = 0; i < num; i++) {
		inFile >> word;
		array[i] = word;
	}
	for (int i = num - 1; i > -1; i--) {
		cout << array[i] << endl;
	}
	delete [] array;
	return 0;
}