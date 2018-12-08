#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

int main(int argc, char* argv[]) {
    //exit if no file given
    if (argc != 2) {
        return 1;
    }

    ifstream ifile;
    int letters;
    int rows;
    int cols;
    //open file, exit if failed
    ifile.open(argv[1]);
    if (ifile.fail()) {
        return 1;
    }

    //read from file
    ifile >> letters;
    ifile >> rows;
    ifile >> cols;

    //create 2d array to store letters
    char** map = new char*[rows];
    for (int i = 0; i < rows; i++) {
        map[i] = new char[cols];
    }

    //read letters from file
    string row;
    for (int i = 0; i < rows; i++) {
        ifile >> row;
        for (int j = 0; j < cols; j++) {
            map[i][j] = row.at(j);
        }
    }

    //close file
    ifile.close();

    //create array to hold adjacent coordinates
    int adjacents[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int maxsize = 0;
    //loop through 2d array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char letter = map[i][j];

            //enter if letter has not been visited
            if (letter != ' ') {
                //create queue to store indices of letters we need to explore from
                queue<pair<int, int>> indices;
                indices.push({i, j});
                //set letter as visited after pushed into queue
                map[i][j] = ' ';
                int size = 0;

                //find size of a country
                while (!indices.empty()) {
                    //remove the first pair from queue
                    pair<int, int> p = indices.front();
                    indices.pop();
                    //increment size
                    size++;

                    //check neighbors of the letter at the indices from the pair
                    for (int k = 0; k < 4; k++) {
                        int y = p.first + adjacents[k][0];
                        int x = p.second + adjacents[k][1];
                        //check in bounds
                        if (y >= 0 && y < rows && x >= 0 && x < cols) {
                            //push letter onto queue and set as visited if it is the correct letter
                            if (map[y][x] == letter) {
                                indices.push({y, x});
                                map[y][x] = ' ';
                            }
                        }
                    } 
                }

                //compare size to maxsize
                if (size > maxsize) {
                    maxsize = size;
                }
            } 
        }
    }

    //deallocate 2d array
    for (int i = 0; i < rows; i++) {
        delete[] map[i];
    }
    delete[] map;

    //print maxsize
    cout << maxsize << endl;
    return 0;
}