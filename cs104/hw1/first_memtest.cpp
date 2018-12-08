#include <iostream>
#include <stdlib.h>
#include "simpleCharManager.h"
using namespace std;

int main(int argc, char *argv[])
{
	simpleCharManager simplest_mem_manager;

	/*write driver code as described in the assignment to replace this */
	char string[] = "Hello world!\n";
	int size = 13;
	char* cstr = simplest_mem_manager.alloc_chars(size);
	for (int i = 0; i < size; i++) {
		cstr[i] = string[i];
	}
	cout << cstr;
	simplest_mem_manager.free_chars(cstr + 6);
	simplest_mem_manager.alloc_chars(11);
	char string2[] = "moon! Bye.\n";
	for (int i = 0; i < size; i++) {
		cstr[i + 6] = string2[i];
	}
	cout << cstr;
	return 0;
}

