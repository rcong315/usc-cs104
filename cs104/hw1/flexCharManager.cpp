#include "flexCharManager.h"

flexCharManager::flexCharManager(){
	used_mem_size = 2;
	used_memory = new Mem_Block*[used_mem_size];
	free_mem = BUF_SIZE;
	active_requests = 0;
	for (int i = 0; i < BUF_SIZE; i++) {
		buffer[i] = '\0';
	}
	free_place = buffer;
}

flexCharManager::~flexCharManager(){
	delete [] used_memory;
}
             
char* flexCharManager::alloc_chars(int n){
	if (n <= 0 || n > BUF_SIZE) {
		return nullptr;
	}
    int count;
	for (int i = free_place - buffer; i < BUF_SIZE; i++) {
		if (buffer[i] == '\0') {
			bool cont = true;
			for (int index = 0; index < active_requests; index++) {
				int begin = used_memory[index] -> physical_location - buffer;
				int end = used_memory[index] -> physical_location - buffer + used_memory[index] -> size - 1;
				if (i >= begin && i <= end) {
					cont = false;
				}
			}
			if (!cont) {
				continue;
			}
			count = 1;
			int j = i + 1;
			for (j = i + 1; j < i + n; j++) {
				if (buffer[j] != '\0') {
					i = j;
					break;
				}
				else {
					count++;
				}
			}
			if (count == n) {
				bool in_array = false;
				for (int k = 0; k < active_requests; k++) {
					char* loc = used_memory[k] -> physical_location;
					if (loc == &buffer[i]) {
						in_array = true;
						break;
					}
				}
				if (!in_array) {
					free_place = &buffer[j];
					if (active_requests == used_mem_size) {
						used_mem_size *= 2;
						Mem_Block** array = new Mem_Block*[used_mem_size];
						for (int i = 0; i < used_mem_size / 2; i++) {
							array[i] = used_memory[i];
						}
						delete [] used_memory;
						used_memory = array;
					}
					used_memory[active_requests] = new Mem_Block(n, &buffer[i]);
					free_mem -= n;
					active_requests++;
					return &buffer[i];
				}
			}
			else if (j == i + n - 1) {
				free_place = nullptr;
			}
		}
	}
    return nullptr;
}

void flexCharManager::free_chars(char* p){
	if (p - buffer >= BUF_SIZE) {
		return;
	}
	for (int i = 0; i < active_requests; i++) {
		char* loc = used_memory[i] -> physical_location;
		if (p == loc) {
			int count = 0;
			while (count < used_memory[i] -> size) {
				buffer[loc - buffer + count] = '\0';
				count++;
				free_mem--;
	 		}
	 		for (int j = i; j < active_requests - 1; j++) {
	 			used_memory[j] = used_memory[j + 1];
	 		}
	 		used_memory[active_requests - 1] = '\0';
	 		active_requests--;
	 		if (p - buffer < free_place - buffer) {
				free_place = p;
			}
			return;
		}


	}
}         


