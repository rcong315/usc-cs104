#include <fstream>
#include <iostream>
#include "Board.h"
#include "Exceptions.h"
#include <cctype>

//initialize private members with input file
Board::Board(std::string board_file_name) {
	std::ifstream ifile(board_file_name.c_str());
	if (ifile.fail()) {
		return;
	}
	ifile >> cols;
	ifile >> rows;
	ifile >> startcol;
	ifile >> startrow;
	board = new Square**[rows];
	for (unsigned int i = 0; i < rows; i++) {
		board[i] = new Square*[cols];
	}
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			Square* square;
			char multiplier;
			bool start = (i == startrow - 1 && j == startcol - 1);
			ifile >> multiplier;
			if (multiplier == '.') {
				square = new Square(1, 1, start);
			}
			else if (isdigit(multiplier)) {
				square = new Square(multiplier - '0', 1, start);
			}
			else if (multiplier == 'd') {
				square = new Square(1, 2, start);
			}
			else {
				square = new Square(1, 3, start);
			}
			board[i][j] = square;
		}
	}
	ifile.close();
}

//free all squares
Board::~Board() {
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			delete board[i][j];
		}
		delete[] board[i];
	}
	delete[] board;
	// for (unsigned int i = 0; i < tilestoplace.size(); i++) {
	// 	delete tilestoplace[i];
	// }
	tilestoplace.clear();
}

//returns vector of all words formed and their scores
std::vector< std::pair<std::string, unsigned int> > Board::getPlaceMoveResults(const PlaceMove &m) const {
	std::vector< std::pair<std::string, unsigned int> > wordsformed;
	std::pair<std::string, unsigned int> wordandscore;
	std::vector<Tile*> tiles = m.tileVector();
	std::string word;
	unsigned int startx = m.getMoveStartx();
	unsigned int starty = m.getMoveStarty();
	Square* currsquare;
	//add vertical words formed by placing horizontal tiles
	if (m.isHorizontal()) {
		unsigned int tileindex = 0;
		for (unsigned int x = startx; x < cols + 1; x++) {
			currsquare = getSquare(x, starty);
			
			//if square is empty then we check what words will be formed by placing a tile
			if (!currsquare -> isOccupied()) {
				word = "";
				int pointsperword = 0;
				unsigned int y = starty;
				//if there is a tile above add the word formed
				if (y > 1 && getSquare(x, y - 1) -> isOccupied()) {
					y = starty - 1;
					while (y > 0 && getSquare(x, y) -> isOccupied()) {
						y--;
					}
					y++;
					while (y < rows + 1) {
						if (y == starty) {
							word += tiles[tileindex] -> getLetter();
							pointsperword += tiles[tileindex] -> getPoints();
							y++;
						}
						if (getSquare(x, y) -> isOccupied()) {
							word += getSquare(x, y) -> getLetter();
							pointsperword += getSquare(x, y) -> getScore();
							y++;
						}
						else {
							break;
						}
					}
				}
				else if (y < rows && getSquare(x, y + 1) -> isOccupied()) {
					y = starty + 1;
					//The line below seems has problem, 
					word += tiles[tileindex] -> getLetter();
					pointsperword += tiles[tileindex] -> getPoints();
					while (y < rows + 1 && getSquare(x, y) -> isOccupied()) {
						word += getSquare(x, y) -> getLetter();
						pointsperword += getSquare(x, y) -> getScore();
						y++;
					}
				}
				if (word.length() > 0) {
					wordandscore.first = word;
					wordandscore.second = pointsperword;
					wordsformed.push_back(wordandscore);
				}
				tileindex++;
				if (tileindex == tiles.size()) {//already checked all tiles
					break;
				}
			}
		}
	}
	//add horizontal words formed by placing a vertical word
	else {
		unsigned int tileindex = 0;
		for (unsigned int y = starty; y < rows + 1; y++) {
			currsquare = getSquare(startx, y);
			//if square is empty then we check what words will be formed by placing a tile
			if (!currsquare -> isOccupied()) {
				word = "";
				int pointsperword = 0;
				unsigned int x = startx;
				//if there is a tile to the left add the word formed
				if (x > 1 && getSquare(x - 1, y) -> isOccupied()) {
					x = startx - 1;
					while (x > 0 && getSquare(x, y) -> isOccupied()) {
						x--;
					}
					x++;
					while (x < cols + 1) {
						if (x == startx) {
							word += tiles[tileindex] -> getLetter();
							pointsperword += tiles[tileindex] -> getPoints();
							x++;
						}
						if (getSquare(x, y) -> isOccupied()) {
							word += getSquare(x, y) -> getLetter();
							pointsperword += getSquare(x, y) -> getScore();
							x++;
						}
						else {
							break;
						}
					}
				}
				
				else if (x < cols && getSquare(x + 1, y) -> isOccupied()) {
					x = startx + 1;
					//the code below seems have problem, replace it
					word += tiles[tileindex] -> getLetter();
					pointsperword += tiles[tileindex] -> getPoints();
					while (x < cols + 1 && getSquare(x, y) -> isOccupied()) {
						word += getSquare(x, y) -> getLetter();
						pointsperword += getSquare(x, y) -> getScore();
						x++;
					}
				}
				if (word.length() > 0) {
					wordandscore.first = word;
					wordandscore.second = pointsperword;
					wordsformed.push_back(wordandscore);
				}
				tileindex++;
				if (tileindex == tiles.size()) {//already checked all times
					break;
				}
			}
		}
	}
	
	//main word
	word = "";
	int pointsperword = 0;
	unsigned int tileindex = 0;
	int wordmultiplier = 1;
	if (m.isHorizontal()) {
		//special case: only placing one tile
		bool firstcol = (startx == 1);
		bool lastcol = (startx == cols);
		bool leftoccupied;
		bool rightoccupied;
		if (tiles.size() == 1) {
			//tile is not at the first or last column
			if (!firstcol && !lastcol) {
				leftoccupied = getSquare(startx - 1, starty) -> isOccupied();
				rightoccupied = getSquare(startx + 1, starty) -> isOccupied();
				//return if tile does not have horizontally adjacent tiles
				if (!leftoccupied && !rightoccupied) {
					return wordsformed;
				}
			}
			//tile at first column
			else if (firstcol) {
				rightoccupied = getSquare(startx + 1, starty) -> isOccupied();
				//return if tile does not have horizontally adjacent tiles
				if (!rightoccupied) {
					return wordsformed;
				}
			}
			//tile at last column
			else {
				leftoccupied = getSquare(startx - 1, starty) -> isOccupied();
				//return if tile does not have horizontally adjacent tiles
				if (!leftoccupied) {
					return wordsformed;
				}
			}
		}
		//tiles before where we place first tile
		if (m.getMoveStartx() > 1 && getSquare(startx - 1, starty) -> isOccupied()) {
			int squaresback = 2;
			while (startx - squaresback > 0 && getSquare(startx - squaresback, starty) -> isOccupied()) {
				squaresback++;
			}
			squaresback--;
			while (squaresback > 0) {
				word += getSquare(startx - squaresback, starty) -> getLetter();
				pointsperword += getSquare(startx - squaresback, starty) -> getScore();
				squaresback--;
			}
		}
		//rest of word starting at first tile place
		unsigned int i;
		for (i = startx; i < cols + 1; i++) {
			currsquare = getSquare(i, starty);
			if (currsquare -> isOccupied()) {
				word += currsquare -> getLetter();
				pointsperword += currsquare -> getScore();
			}
			else {
				word += tiles[tileindex] -> getLetter();
				pointsperword += tiles[tileindex] -> getPoints() * currsquare -> getLMult();
				wordmultiplier *= currsquare -> getWMult();
				tileindex++;
				if (tileindex == tiles.size()) {
					//exit loop when all tiles placed
					i++;
					break;
				}
			}
		}
		//check for out of bounds
		if (tileindex != tiles.size()) {
			throw PlaceException("error: Word goes out of bounds");
		}
		//tiles after where we placed last tile
		while (i < cols + 1 && getSquare(i, starty) -> isOccupied()) {
			word += getSquare(i, starty) -> getLetter();
			pointsperword += getSquare(i, starty) -> getScore();
			i++;
		}
	}
	//if move is vertical
	else {
		//special case: only placing one tile
		bool firstrow = (starty == 1);
		bool lastrow = (starty == rows);
		bool upoccupied;
		bool downoccupied;
		if (tiles.size() == 1) {
			//tile is not at the first or last row
			if (!firstrow && !lastrow) {
				upoccupied = getSquare(startx, starty - 1) -> isOccupied();
				downoccupied = getSquare(startx, starty + 1) -> isOccupied();
				//return if tile does not have vertically adjacent tiles
				if (!upoccupied && !downoccupied) {
					return wordsformed;
				}
			}
			//tile at first row
			else if (firstrow) {
				downoccupied = getSquare(startx, starty + 1) -> isOccupied();
				//return if tile does not have vertically adjacent tiles
				if (!downoccupied) {
					return wordsformed;
				}
			}
			//tile at last row
			else {
				upoccupied = getSquare(startx, starty - 1) -> isOccupied();
				//return if tile does not have vertically adjacent tiles
				if (!upoccupied) {
					return wordsformed;
				}
			}
		}
		//tiles before where we place last tile
		if (m.getMoveStarty() > 1 && getSquare(startx, starty - 1) -> isOccupied()) {
			int squaresup = 2;
			while (starty - squaresup > 0 && getSquare(startx, starty - squaresup) -> isOccupied()) {
				squaresup++;
			}
			squaresup--;
			while (squaresup > 0) {
				word += getSquare(startx, starty - squaresup) -> getLetter();
				pointsperword += getSquare(startx, starty - squaresup) -> getScore();
				squaresup--;
			}
		}
		//rest of word starting at first tile place
		unsigned int i;
		for (i = starty; i < rows + 1; i++) {
			currsquare = getSquare(startx, i);
			if (currsquare -> isOccupied()) {
				word += currsquare -> getLetter();
				pointsperword += currsquare -> getScore();
			}
			else {
				word += tiles[tileindex] -> getLetter();
				pointsperword += tiles[tileindex] -> getPoints() * currsquare -> getLMult();
				wordmultiplier *= currsquare -> getWMult();
				tileindex++;
				if (tileindex == tiles.size()) {
					//exit loop when all tiles placed
					i++;
					break;
				}
			}
		}
		//check for out of bounds
		if (tileindex != tiles.size()) {
			throw PlaceException("error: Word goes out of bounds");
		}
		//tiles after where we placed last tile
		while (i < rows + 1 && getSquare(startx, i) -> isOccupied()) {
			word += getSquare(startx, i) -> getLetter();
			pointsperword += getSquare(startx, i) -> getScore();
			i++;
		}
	}
	//deallocate memory in tiles vector
	for (unsigned int i = 0; i < tiles.size(); i++) {
		delete tiles[i];
	}
	tiles.clear();
	//apply multipliers and add word and score
	pointsperword *= wordmultiplier;
	wordandscore.first = word;
	wordandscore.second = pointsperword;
	wordsformed.push_back(wordandscore);
	return wordsformed;
}

//puts tiles on the board
int Board::executePlaceMove(const PlaceMove & m) {
	tilestoplace = m.tileVector();
	int pointsearned = 0;
	int startx = m.getMoveStartx();
	int starty = m.getMoveStarty();
	//get the words formed
	std::vector< std::pair<std::string, unsigned int> > words = getPlaceMoveResults(m);
	unsigned int tilenum = 0;
	Square* currsquare;
	if (m.isHorizontal()) {
		//place tiles on squares
		unsigned int i = startx;
		while (tilenum != tilestoplace.size()) {
			currsquare = getSquare(i, starty);
			if (currsquare -> isOccupied()) {
				i++;
				continue;
			}
			else {
				currsquare -> placeTile(tilestoplace[tilenum]);
				i++;
				tilenum++;
			}
		}
	}
	else {
		//place tiles on squares
		unsigned int i = starty;
		while (tilenum != tilestoplace.size()) {
			currsquare = getSquare(startx, i);
			if (currsquare -> isOccupied()) {
				i++;
				continue;
			}
			else {
				currsquare -> placeTile(tilestoplace[tilenum]);
				i++;
				tilenum++;
			}
		}
	}
	//add points
	for (unsigned int i = 0; i < words.size(); i++) {
		pointsearned += words[i].second;
	}
	//return points
	return pointsearned;
}

//returns square at certain location
Square* Board::getSquare(size_t x, size_t y) const {
	return board[y - 1][x - 1];
}

//returns number of rows
size_t Board::getRows() const {
	return rows;
}

//returns number of columns
size_t Board::getColumns() const {
	return cols;
}

//check if move is legal
bool Board::isLegal(const PlaceMove& m, Dictionary* dictionary, std::vector< std::pair<std::string, unsigned int> > wordsformed) {
	if (wordsformed.empty()) {
		return false;
	}
	unsigned int wordlength = wordsformed[wordsformed.size() - 1].first.length();;
	unsigned int startx = m.getMoveStartx();
	unsigned int starty = m.getMoveStarty();
	//check if the the square where first tile is being placed is occupied
	if (getSquare(startx, starty) -> isOccupied()) {
		std::cout << "error: Tiles occupied" << std::endl;
		std::cout << "Try again: ";
		return false;
	}
	//check if word goes out of bounds
	if (m.isHorizontal() && startx + wordlength - 1 > cols) {
		std::cout << "error: Word goes out of bounds" << std::endl;
		std::cout << "Try again: ";
		return false;
	}
	//check if word goes out of bounds
	else if (!m.isHorizontal() && starty + wordlength - 1 > rows) {
		std::cout << "error: Word goes out of bounds" << std::endl;
		std::cout << "Try again: ";
		return false;
	}
	//check if words are all in dictionary
	std::vector< std::pair<std::string, unsigned int> >::iterator it;
	for (it = wordsformed.begin(); it != wordsformed.end(); ++it) {
		if (!dictionary -> isLegalWord(it -> first)) {
			std::cout << "error: Illegal words formed" << std::endl;
			return false;
		}
	}
	return true;
}

//check if the move occupies the start tile
bool Board::moveHasStart(const PlaceMove& m) {
	std::vector< std::pair<std::string, unsigned int> > wordsformed = getPlaceMoveResults(m);
	unsigned int startx = m.getMoveStartx();
	unsigned int starty = m.getMoveStarty();
	if (m.isHorizontal()) {
		for (unsigned int i = startx; i < startx + wordsformed[wordsformed.size() - 1].first.length(); i++) {
			if (getSquare(i, starty) -> isStart()) {
				return true;
			}
		}
	}
	else {
		for (unsigned int i = starty; i < starty + wordsformed[wordsformed.size() - 1].first.length(); i++) {
			if (getSquare(startx, i) -> isStart()) {
				return true;
			}
		}
	}
	return false;
}

//checks if the place move is adjacent to at least one tile
bool Board::checkForAdjacentTiles(const PlaceMove& m) {
	unsigned int startx = m.getMoveStartx();
	unsigned int starty = m.getMoveStarty();
	if (m.isHorizontal()) {
		if (startx > 1 && getSquare(startx - 1, starty) -> isOccupied()) {
			return true;
		}
		unsigned int i;
		if (getPlaceMoveResults(m).empty()) {
			return false;
		}
		for (i = 0; i < getPlaceMoveResults(m)[getPlaceMoveResults(m).size() - 1].first.length(); i++) {
			if (getSquare(startx + i, starty) -> isOccupied()) {
				return true;
			}
			else if (starty > 1 && getSquare(startx + i, starty - 1) -> isOccupied()) {
				return true;
			}
			else if (starty < rows && getSquare(startx + i, starty + 1) -> isOccupied()) {
				return true;
			}
		}
		if (startx + i < cols + 1 && getSquare(startx + i, starty) -> isOccupied()) {
			return true;
		}
	}
	else {
		if (starty > 1 && getSquare(startx, starty - 1) -> isOccupied()) {
			return true;
		}
		unsigned int i;
		if (getPlaceMoveResults(m).empty()) {
			return false;
		}
		for (i = 0; i < getPlaceMoveResults(m)[getPlaceMoveResults(m).size() - 1].first.length(); i++) {
			if (getSquare(startx, starty + i) -> isOccupied()) {
				return true;
			}
			else if (startx > 1 && getSquare(startx - 1, starty + i) -> isOccupied()) {
				return true;
			}
			else if (startx < cols && getSquare(startx + 1, starty + i) -> isOccupied()) {
				return true;
			}
		}
		if (starty + i < rows + 1 && getSquare(startx, starty + i) -> isOccupied()) {
			return true;
		}
	}
	return false;
}

//initialize board with starting tiles
void Board::init(std::string initfile) {
	std::ifstream ifile(initfile.c_str());
	if (ifile.fail()) {
		return;
	}
	int row = 0;
	while (!ifile.eof()) {
		std::string line;
		getline(ifile, line);
		for (unsigned int i = 0; i < line.length(); i += 3) {
			if (line[i] != '.') {
				int points = (line[i + 1] - '0') * 10 + line[i + 2] - '0';
				Tile* tile = new Tile(std::tolower(line[i]), points);
				board[row][i / 3] -> placeTile(tile);
			}
		}
		row++;
	}
}

//find first character of the word the current tile is in
int Board::firstCharacter(int col, int row, bool isHorizontal) {
	if (isHorizontal) {
		int oldcol = col;
		while (col - 1 > 0 && getSquare(col - 1, row) -> isOccupied()) {
			col--;
		}
		if (oldcol == col && !getSquare(col, row) -> isOccupied()) {
			return -1;
		}
		return col;
	}
	else {
		int oldrow = row;
		while (row - 1 > 0 && getSquare(col, row - 1) -> isOccupied()) {
			row--;
		}
		if (oldrow == row && !getSquare(col, row) -> isOccupied()) {
			return -1;
		}
		return row;
	}
}

//return the word a tile is part of
std::string Board::getWord(int col, int row, bool isHorizontal) {
	std::string word = "";
	if (isHorizontal) {
		col = firstCharacter(col, row, true);
		if (col == -1) {
			return "";
		}
		word += getSquare(col, row) -> getLetter();
		int numcols = cols;
		while (col + 1 <= numcols && getSquare(col + 1, row) -> isOccupied()) {
			word += getSquare(col + 1, row) -> getLetter();
			col++;
		}
	}
	else {
		row = firstCharacter(col, row, false);
		if (row == -1) {
			return "";
		}
		word += getSquare(col, row) -> getLetter();
		int numrows = rows;
		while (row + 1 <= numrows && getSquare(col, row + 1) -> isOccupied()) {
			word += getSquare(col, row + 1) -> getLetter();
			row++;
		}
	}
	return word;
}

//find the word perpendicular to the word of a tile
bool Board::checkPerpendicular(Dictionary* dictionary, char letter, int col, int row, bool isHorizontal) {
	std::string before, after;
	if (isHorizontal) {
		before = getWord(col, row, false);
		int numrows = rows;
		if (row + 1 <= numrows && getSquare(col, row + 1) -> isOccupied()) {
			after = getWord(col, row + 1, false);
		}
		std::string all = before + letter + after;

		return all.size() == 1 || dictionary -> isLegalWord(before + letter + after);
	}
	else {
		before = getWord(col, row, true);
		int numcols = cols;
		if (col + 1 <= numcols && getSquare(col + 1, row) -> isOccupied()) {
			after = getWord(col + 1, row, true);
		}
		std::string all = before + letter + after;
		return all.size() == 1 || dictionary -> isLegalWord(before + letter + after);
	}
}

//return tiles to place
std::vector<Tile*>& Board::getTilesToPlace() {
	return tilestoplace;
}

//check if prefix is legal
bool  Board::canPlacePrefix(Dictionary* dictionary, std::string prefix, int col, int row, bool isHorizontal)
{
	if (isHorizontal) {
		if ((unsigned int)col <= prefix.size()) {
			return false;
		}
		int x = col - prefix.size();
		int y = row;
		for (unsigned int i = 0; i < prefix.size(); ++i, ++x) {
			if (getSquare(x, y) -> isOccupied()){
				if (getSquare(x, y) -> getLetter() != prefix[i]) {
					return false;
				}
			}
			else {
				if (!checkPerpendicular(dictionary, prefix[i], x, y, isHorizontal)) {
					return false;
				}
			}

		}
	}
	else {
		if ((unsigned int)row <= prefix.size()) {
			return false;
		}
		int x = col;
		int y = row - prefix.size();
		for (unsigned int i = 0; i < prefix.size(); ++i, ++y) {
			if (getSquare(x, y) -> isOccupied()) {
				if (getSquare(x, y) -> getLetter() != prefix[i]) {
					return false;
				}
			}
			else {
				if (!checkPerpendicular(dictionary, prefix[i], x, y, isHorizontal)) {
					return false;
				}
			}

		}
	}
	return true;
}

//return the points earned for a move
int Board::pointsEarned(PlaceMove& m) {
	int points = 0;
	std::vector< std::pair<std::string, unsigned int> > words = getPlaceMoveResults(m);
	for (unsigned int i = 0; i < words.size(); i++) {
		points += words[i].second;
	}
	return points;
}
