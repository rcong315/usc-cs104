#ifndef __AI_PLAYER__
#define __AI_PLAYER__

#include "Player.h"
#include "Board.h"
#include "Dictionary.h"
#include "Square.h"

using namespace std;

class AIPlayer : public Player
{
public:
	AIPlayer(std::string const & name, size_t maxTiles);
	virtual ~AIPlayer();

	bool isAI();

	virtual string getAIMove(Board* board, Dictionary* dictionary);

protected:
	virtual vector<PlaceMove> extendLeft_hor(Board* board, Dictionary* dictionary, string prefix, TrieNode* node, int x, int y, int limit, vector<bool>& tileUsed);
	virtual vector<PlaceMove> extendRight_hor(Board* board, Dictionary* dictionary, string prefix, TrieNode* node, int x, int y, vector<bool>& tileUsed);
	virtual vector<PlaceMove> extendLeft_ver(Board* board, Dictionary* dictionary, string prefix, TrieNode* node, int x, int y, int limit, vector<bool>& tileUsed);
	virtual vector<PlaceMove> extendRight_ver(Board* board, Dictionary* dictionary, string prefix, TrieNode* node, int x, int y, vector<bool>& tileUsed);
	virtual string generateCommand(Board* board, PlaceMove& move);

	virtual bool useCorrectNumberOfTiles(Dictionary* dictionary, Board* board, PlaceMove& move); // check how may tiles from hand used
	virtual int tilesUsed(Board* board, PlaceMove& move); 

	virtual bool larger(Board* board, PlaceMove& p1, PlaceMove&p2) = 0;

	virtual string generateAITileString(Board* board, PlaceMove& move, int& startx, int& starty);

private:

	void mergeMoves(Dictionary* dictionary, Board* board, vector<PlaceMove>& moves, vector<PlaceMove> newMoves);
};

#endif
