#include "MaxScoreAI.h"
#include <algorithm>

MaxScoreAI::MaxScoreAI (std::string const & name, size_t maxTiles): AIPlayer(name, maxTiles) {
}

MaxScoreAI::~MaxScoreAI () {
}

//comparator to compare moves based on points
bool MaxScoreAI::MaxScoreAIComp(Board* board, PlaceMove& p1, PlaceMove& p2) {

	int startx1, starty1;
	string string1 = generateAITileString(board, p1, startx1, starty1);
	PlaceMove boardP1(startx1, starty1, p1.isHorizontal(), string1, this);
	int point1 = board -> pointsEarned(boardP1);

	int startx2, starty2;
	string string2 = generateAITileString(board, p2, startx2, starty2);
	PlaceMove boardP2(startx2, starty2, p2.isHorizontal(), string2, this);
	int point2 = board -> pointsEarned(boardP2);

	return point1 > point2;
}

//return whether p1 is better than p2
bool MaxScoreAI::larger(Board* board, PlaceMove& p1, PlaceMove&p2) {
	return MaxScoreAIComp(board, p1, p2);
}