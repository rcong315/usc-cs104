#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

bool validColor(vector<int>& colors, int country, int color, map<int, set<int>>& neighbors);
bool setAndCheckColors(vector<int>& colors, unsigned int start, map<int, set<int>>& neighbors);

int main(int argc, char* argv[]) {
    //exit if no file given
    if (argc != 2) {
        return 1;
    }

    ifstream ifile;
    int countries;
    int rows;
    int cols;
    //open file, exit if failed
    ifile.open(argv[1]);
    if (ifile.fail()) {
        return 1;
    }

    //read from file
    ifile >> countries;
    ifile >> rows;
    ifile >> cols;

    //create 2d array to store letters (converted to ints)
    int** grid = new int*[rows];
    for (int i = 0; i < rows; i++) {
        grid[i] = new int[cols];
    }

    //read letters from file and convert to ints
    string row;
    for (int i = 0; i < rows; i++) {
        ifile >> row;
        for (int j = 0; j < cols; j++) {
            grid[i][j] = row.at(j) - 'A';
        }
    }

    //close file
    ifile.close();

    //create a map to hold neighbors of each country
    map<int, set<int>> neighbors;
    //loop through each element in array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int country = grid[i][j];

            //check element above and add neighbors if it is a different element
            if (i > 0 && country != grid[i - 1][j]) {
                neighbors[country].insert(grid[i - 1][j]);
                neighbors[grid[i - 1][j]].insert(country);
            }

            //check element to the left and add neighbors if it is a different element
            if (j > 0 && country != grid[i][j - 1]) {
                neighbors[country].insert(grid[i][j - 1]);
                neighbors[grid[i][j - 1]].insert(country);
            }
        }
    }

    //create vector to hold color for each country, initialize each country's color as -1
    vector<int> colors(countries, -1);
    
    //color countries
    setAndCheckColors(colors, 0, neighbors);

    //print countries and their respective colors
    for (unsigned int i = 0; i < colors.size(); i++) {
        cout << char(i + 'A') << " " << colors[i] << endl;
    }

    //exit normally
    return 0;
}

//checks if the countries color is different from all it's neighbors' colors
bool validColor(vector<int>& colors, int country, int color, map<int, set<int>>& neighbors) {
    //for each loop to loop through neighbors of each country
    for (int neighbor : neighbors[country]) {
        //if two neighbors have the same color return false
        if (colors[neighbor] == color) {
            return false;
        }
    }
    //no neighbors have same color, return true
    return true;
}

//sets colors for countries and uses backtracking and recursion to check if set colors are valid
bool setAndCheckColors(vector<int>& colors, unsigned int start, map<int, set<int>>& neighbors) {
    //base case, colors have been assigned to all countries
    if (start == colors.size()) {
        return true;
    }

    //loop through 4 colors
    for(int j = 1; j < 5; j++) {
        //set color j to current country if neighbors are not colored j
        if (validColor(colors, start, j, neighbors)) {
            colors[start] = j;

            //recursive call to check if color works with neighbors' colors
            if (setAndCheckColors(colors, start + 1, neighbors)) {
                return true;
            }

            //reset country's color to -1 if the set color didn't work with neighbors
            colors[start] = -1;
        }
    }

    //return false if end is reached, no valid color found
    return false;
}