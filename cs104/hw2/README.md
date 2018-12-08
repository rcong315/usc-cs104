In order to compile selection sort, we need a file that has a main. If the main file is called "main_file.cpp", you can compile selection sort by typing the following,

g++ -g -Wall -std=c++11 selection_sort.cpp main_file.cpp -o selection_sort

Run selection sort by typing,

./selection_sort


To compile circular list, we also need a main. Using the same file as before, the compile command can be run as,

g++ -g -Wall -std=c++11 circular_list_int.cpp main_file.cpp -o circular_list_int

To run circular list, type,

./circular_list_int


duck_duck_goose.cpp has a main, so we can compile it by itself but we need to include the implementation for circular lists because the game uses circular lists to manage the players

g++ -g -Wall -std=c++11 duck_duck_goose.cpp circular_list_int.cpp -o duck_duck_goose

To run the game, you have to give a config and output file

./duck_duck_goose config.txt output.txt


However, for this assignment I used cmake . and make check to compile the files
