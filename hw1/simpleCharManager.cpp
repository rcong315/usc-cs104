#include <cstddef>
#include "simpleCharManager.h"



simpleCharManager::simpleCharManager(){
	for (int i = 0; i < BUF_SIZE; i++) {
		buffer[i] = '\0';
	}
	free_place = buffer;
}

simpleCharManager::~simpleCharManager(){
	for (int i = 0; i < BUF_SIZE; i++) {
		buffer[i] = '\0';
	}
	free_place = buffer;
}

char* simpleCharManager::alloc_chars(int n){
 	if (n <= 0 || n > BUF_SIZE || free_place == NULL) {
 		return NULL;
  	}
	int count;
	for (int i = free_place - buffer; i < BUF_SIZE; i++) {
		if (buffer[i] == '\0') {
			count = 1;
			int j = i + 1;
			for (j = i + 1; j < i + n; j++) {
				if (j < BUF_SIZE && buffer[j] != '\0') {
					i = j;
					break;
				}
				else {
					count++;
				}
			}
			if (count == n) {
				if (j < BUF_SIZE) {
					free_place = &buffer[j];
				}
				else {
					free_place = nullptr;
				}
				return &buffer[i];
			}	
		}
	}
	return nullptr;
}			

void simpleCharManager::free_chars(char* p){
	if (p - buffer >= BUF_SIZE || p - buffer < 0) {
		return;
	}
	for (int i = p - buffer; i < BUF_SIZE; i++) {
		buffer[i] = '\0';
	}
	if (p - buffer < free_place - buffer) {
		free_place = p;
	}
}         




