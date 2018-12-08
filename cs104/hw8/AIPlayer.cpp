#include "AIPlayer.h"
#include <climits>
#include <stdlib.h>

AIPlayer::AIPlayer(std::string const & name, size_t maxTiles):Player(name, maxTiles)
{
}

AIPlayer::~AIPlayer()
{
}

bool AIPlayer::isAI() {
	return true;
}

//find best move for ai
string AIPlayer::getAIMove(Board* board, Dictionary* dictionary) {
	vector<PlaceMove> res;
	//horizontal
	for (size_t x = 1; x <= board -> getColumns(); x++) {
		for (size_t y = 1; y <= board -> getRows(); y++) {
			Square* pos = board -> getSquare(x, y);
			if (pos -> isOccupied()) {
				vector<bool> tileUsed_hor(hand.size(), false);
				if (x == 1) {
					vector<PlaceMove> moves = extendLeft_hor(board, dictionary, "", dictionary -> getRoot(), x, y, tileUsed_hor.size(), tileUsed_hor);
					mergeMoves(dictionary, board, res, moves);
				}
				else if (!board -> getSquare(x - 1, y) -> isOccupied() && (x == 2 || !board -> getSquare(x - 2, y) -> isOccupied())) { //find an other point
					vector<PlaceMove> moves = extendLeft_hor(board, dictionary, "", dictionary -> getRoot(), x - 1, y, tileUsed_hor.size(), tileUsed_hor);
					mergeMoves(dictionary, board, res, moves);
				}
				vector<bool> tileUsed_ver(hand.size(), false);
				if (y == 1) {
					vector<PlaceMove> moves = extendLeft_ver(board, dictionary, "", dictionary -> getRoot(), x, y, tileUsed_ver.size(), tileUsed_ver);
					mergeMoves(dictionary, board, res, moves);
				}
				else if (!board -> getSquare(x, y - 1) -> isOccupied() && (y == 2 || !board -> getSquare(x, y - 2) -> isOccupied())) { //find an other point
					vector<PlaceMove> moves = extendLeft_ver(board, dictionary, "", dictionary -> getRoot(), x, y - 1, tileUsed_ver.size(), tileUsed_ver);
					mergeMoves(dictionary, board, res, moves);
				}
			}
		}
	}
	//vertical
	for (size_t x = 1; x <= board -> getColumns(); x++) {
		for (size_t y = 1; y <= board -> getRows(); y++) {
			Square* pos = board -> getSquare(x, y);
			if (pos -> isOccupied()) {
				vector<bool> tileUsed_hor(hand.size(), false);
				if (y == 1) {
					vector<PlaceMove> moves = extendLeft_hor(board, dictionary, "", dictionary -> getRoot(), x, y, tileUsed_hor.size(), tileUsed_hor);
					mergeMoves(dictionary, board, res, moves);
				}
				else if (!board -> getSquare(x, y - 1) -> isOccupied() && (y == 2 || !board -> getSquare(x, y - 2) -> isOccupied())) { //find an other point
					vector<PlaceMove> moves = extendLeft_hor(board, dictionary, "", dictionary -> getRoot(), x, y - 1, tileUsed_hor.size(), tileUsed_hor);
					mergeMoves(dictionary, board, res, moves);
				}
				vector<bool> tileUsed_ver(hand.size(), false);
				if (x == 1) {
					vector<PlaceMove> moves = extendLeft_ver(board, dictionary, "", dictionary -> getRoot(), x, y, tileUsed_ver.size(), tileUsed_ver);
					mergeMoves(dictionary, board, res, moves);
				}
				else if (!board -> getSquare(x - 1, y) -> isOccupied() && (x == 2 || !board -> getSquare(x - 2, y) -> isOccupied())) { //find an other point
					vector<PlaceMove> moves = extendLeft_ver(board, dictionary, "", dictionary -> getRoot(), x - 1, y, tileUsed_ver.size(), tileUsed_ver);
					mergeMoves(dictionary, board, res, moves);
				}
			}
		}
	}
	//choose command
	string cmd;
	if (res.size() > 0) {
		cmd = generateCommand(board, res[0]);
	}
	//pass or exchange if no place move
	else {
		//67% chance of exchange 33% of pass
		int random = rand() % 3;
		if (random == 0) {
			cmd = "pass";
		}
		else {
			int tiles = rand() % 7 + 1;
			cmd = "exchange " + handToString().substr(0, tiles);
		}
	}
	return cmd;
}

//combine two set of moves and find best
void AIPlayer::mergeMoves(Dictionary* dictionary, Board* board, vector<PlaceMove>& moves, vector<PlaceMove> newMoves)
{
	for (PlaceMove& m : newMoves) {
		if (m.getString().size() > 1 && useCorrectNumberOfTiles(dictionary, board, m) > 0) {
			if (moves.size() == 0) {
				moves.push_back(m);
			}
			else {
				if (larger(board, m, moves[0])) {
					moves[0] = m;
				}
			}
		}
	}
}

//returns number of tiles used in move
int AIPlayer::tilesUsed(Board* board, PlaceMove& move) {
	string str = move.getString();
	int count = 0;
	for (unsigned int i = 0; i < str.size(); ++i) {
		int x = move.getMoveStartx();
		int y = move.getMoveStarty();
		if (move.isHorizontal()) {
			x += i;
		}
		else {
			y += i;
		}
		if (x < 1 || (unsigned int)x > board -> getColumns() || y < 1 || (unsigned int)y > board -> getRows()) {
			return false; //should not happen
		}
		Square* s = board -> getSquare(x, y);
		if (s -> isOccupied()) {
			if (s -> getLetter() != str[i]) {
				return false; //should not happen
			}
		}
		else {
			count++;
		}
	}
	return count;
}

//returns whether correct number of tiles are used in move
bool AIPlayer::useCorrectNumberOfTiles(Dictionary* dictionary, Board* board, PlaceMove& move) {
	string str = move.getString();
	int count = 0;
	if (move.isHorizontal()) {
		if (move.getMoveStartx() > 1 && board -> getSquare(move.getMoveStartx() - 1, move.getMoveStarty()) -> isOccupied()) { //inserted in the middle
			int x = move.getMoveStartx() - 1;
			int y = move.getMoveStarty();
			string str = move.getString();
			while (x >= 1 && board -> getSquare(x, y) -> isOccupied() ) {
				str = string(1, board -> getSquare(x, y) -> getLetter()) + str;
				x--;
			}
			if (dictionary -> isLegalWord(str)) {
				move.reset(x, y, str);
			}
			else {
				return false;
			}
		}
	}
	else {
		if (move.getMoveStarty() > 1 && board -> getSquare(move.getMoveStartx(), move.getMoveStarty() - 1) -> isOccupied()) {
			int x = move.getMoveStartx();
			int y = move.getMoveStarty() - 1;
			string str = move.getString();
			while (y >= 1 && board -> getSquare(x, y) -> isOccupied()) {
				str = string(1, board -> getSquare(x, y) -> getLetter()) + str;
				y--;
			}
			if (dictionary -> isLegalWord(str)) {
				move.reset(x, y, str);
			}
			else {
				return false;
			}
		}
	}
	for (unsigned int i = 0; i < str.size(); ++i) {
		int x = move.getMoveStartx();
		int y = move.getMoveStarty();
		
		if (move.isHorizontal()) {
			x += i;
		}
		else {
			y += i;
		}
		if (x < 1 || (unsigned int)x > board -> getColumns() || y < 1 || (unsigned int)y > board -> getRows()) {
			return false; //should not happen
		}
		Square* s = board -> getSquare(x, y);
		if (s -> isOccupied()) {
			if (s -> getLetter() != str[i]) {
				return false; //should not happen
			}
		}
		else {
			count++;
		}
	}
	return count > 0 && (unsigned int)count < str.size();
}

//turn move to a string
std::string AIPlayer::generateAITileString(Board* board, PlaceMove& move, int& startx, int& starty) {
	string str = move.getString();
	string place;
	vector<int> hist(26, 0);//histogram to check for '?' in hand
	for (Tile* t : hand) {
		int c = t -> getLetter();
		if (c != '?') {
			hist[c - 'a']++;
		}
	}
	startx = INT_MAX;
	starty = INT_MAX;
	for (unsigned int i = 0; i < str.size(); ++i) {
		int x = move.getMoveStartx();
		int y = move.getMoveStarty();
		if (move.isHorizontal()) {
			x += i;
		}
		else {
			y += i;
		}
		if (!board -> getSquare(x, y) -> isOccupied()) {
			startx = std::min(startx, x); //find the first empty cell
			starty = std::min(starty, y);
			hist[str[i] - 'a']--;
			if (hist[str[i] - 'a'] < 0) { //use '?' in hand
				place += "?";
			}
			place += str[i];
		}
	}
	return place;
}

//take the move and put in format for command line
string AIPlayer::generateCommand(Board* board, PlaceMove& move){
	int startx, starty;
	string place = generateAITileString(board, move, startx, starty);
	string cmd = "place " + (move.isHorizontal() ? string("- ") : string("| ")) + to_string(starty) + string(" ") + to_string(startx) + " " + place;
	return cmd;
}

//find all possible moves horizontally
vector<PlaceMove> AIPlayer::extendLeft_hor(Board* board, Dictionary* dictionary, string prefix, TrieNode* node, int x, int y, int limit, vector<bool>& tileUsed)
{
	vector<PlaceMove> res;
	vector<PlaceMove> moves;
	moves = extendRight_hor(board, dictionary, prefix, node, x, y, tileUsed);
	mergeMoves(dictionary, board, res, moves);
	if (limit > 0) {
		for (unsigned int i = 0; i < hand.size(); ++i) {
			if (!tileUsed[i]) {
				Tile* t = hand[i];
				for (int c = 'a'; c <= 'z'; ++c) {
					if (t -> getLetter() == '?' || t -> getLetter() == c) {
						string s(1, c);
						TrieNode* subNode = dictionary -> search(node, s);
						if (subNode && board -> canPlacePrefix(dictionary, prefix + s, x, y, true)) { //D project does not check perpendicular
							tileUsed[i] = true;
							vector<PlaceMove> moves = extendLeft_hor(board, dictionary, prefix + s, subNode, x, y, limit - 1, tileUsed);
							mergeMoves(dictionary, board, res, moves);
							tileUsed[i] = false;
						}
					}
				}
			}
		}
	}
	return res;
}

//find all possible moves vertically
vector<PlaceMove> AIPlayer::extendLeft_ver(Board* board, Dictionary* dictionary, string prefix, TrieNode* node, int x, int y, int limit, vector<bool>& tileUsed)
{
	vector<PlaceMove> res;
	vector<PlaceMove> moves;
	moves = extendRight_ver(board, dictionary, prefix, node, x, y, tileUsed);
	mergeMoves(dictionary, board, res, moves);
	if (limit > 0) {
		for (unsigned int i = 0; i < hand.size(); ++i) {
			if (!tileUsed[i]) {
				Tile* t = hand[i];
				for (int c = 'a'; c <= 'z'; ++c) {
					if (t -> getLetter() == '?' || t -> getLetter() == c) {
						string s(1, c);
						TrieNode* subNode = dictionary -> search(node, s);
						if (subNode && board -> canPlacePrefix(dictionary, prefix + s, x, y, false)) { //D project does not check perpendicular
							tileUsed[i] = true;
							vector<PlaceMove> moves = extendLeft_ver(board, dictionary, prefix + s, subNode, x, y, limit - 1, tileUsed);
							mergeMoves(dictionary, board, res, moves);
							tileUsed[i] = false;
						}
					}
				}
			}
		}
	}
	return res;
}

//find all possible moves horizontally
vector<PlaceMove> AIPlayer::extendRight_hor(Board* board, Dictionary* dictionary, string prefix, TrieNode* node, int x, int y, vector<bool>& tileUsed)
{
	vector<PlaceMove> res;
	if (!board -> getSquare(x, y) -> isOccupied()) {
		if (node -> inSet || prefix == "") {
			mergeMoves(dictionary, board, res, { PlaceMove(x - prefix.size(), y, true, prefix, this) });
		}
		for (unsigned int i = 0; i < hand.size(); ++i) {
			if (!tileUsed[i]) {
				Tile* t = hand[i];
				for (int c = 'a'; c <= 'z'; ++c) {
					if (t -> getLetter() == '?' ||  t -> getLetter() == c) { //for testing purpose
						string s(1, c);
						TrieNode* subNode = dictionary -> search(node, s);
						if (subNode && board -> checkPerpendicular(dictionary, c, x, y, true)) {
							tileUsed[i] = true;
							if ((unsigned int)x < board -> getColumns()) {
								vector<PlaceMove> moves = extendRight_hor(board, dictionary, prefix + s, subNode, x + 1, y, tileUsed);
								mergeMoves(dictionary, board, res, moves);
							}
							tileUsed[i] = false;
						}
					}
				}
			}
		}
	}
	else {
		Square* s = board -> getSquare(x, y);
		string c(1, s -> getLetter());
		TrieNode* subNode = dictionary -> search(node, c);
		if (subNode) {
			if ((unsigned int)x < board -> getColumns()) {
				vector<PlaceMove> moves = extendRight_hor(board, dictionary, prefix + c, subNode, x + 1, y, tileUsed);
				mergeMoves(dictionary, board, res, moves);
			}
		}
	}
	return res;
}

//find all possible moves vertically
vector<PlaceMove> AIPlayer::extendRight_ver(Board* board, Dictionary* dictionary, string prefix, TrieNode* node, int x, int y, vector<bool>& tileUsed)
{
	vector<PlaceMove> res;
	if (!board -> getSquare(x, y) -> isOccupied()) {
		if (node -> inSet || prefix == "") {
			mergeMoves(dictionary, board, res, { PlaceMove(x, y - prefix.size(), false, prefix, this) });
		}
		for (unsigned int i = 0; i < hand.size(); ++i) {
			if (!tileUsed[i]) {
				Tile* t = hand[i];
				for (int c = 'a'; c <= 'z'; ++c) {
					if (t -> getLetter() == '?' || t -> getLetter() == c) { //for testing purpose
						string s(1, c);
						TrieNode* subNode = dictionary -> search(node, s);
						if (subNode && board -> checkPerpendicular(dictionary, c, x, y, false)) {
							tileUsed[i] = true;
							if ((unsigned int)y < board -> getColumns()) {
								vector<PlaceMove> moves = extendRight_ver(board, dictionary, prefix + s, subNode, x, y + 1, tileUsed);
								mergeMoves(dictionary, board, res, moves);
							}
							tileUsed[i] = false;
						}
					}
				}
			}
		}
	}
	else {
		Square* s = board -> getSquare(x, y);
		string c(1, s -> getLetter());
		TrieNode* subNode = dictionary -> search(node, c);
		if (subNode) {
			if ((unsigned int)y < board -> getRows()) {
				vector<PlaceMove> moves = extendRight_ver(board, dictionary, prefix + c, subNode, x, y + 1, tileUsed);
				mergeMoves(dictionary, board, res, moves);
			}
		}
	}
	return res;
}
