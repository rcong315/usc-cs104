#include "MaxLetterAI.h"
#include <algorithm>

MaxLetterAI::MaxLetterAI (std::string const & name, size_t maxTiles): AIPlayer(name, maxTiles) {
}

MaxLetterAI::~MaxLetterAI () {
}

//comparator to compare moves by letters used
static bool MaxLetterAIComp(PlaceMove& p1, PlaceMove& p2) {
	return p1.getString().size() > p2.getString().size();
}

//return whether p1 is better than p2
bool MaxLetterAI::larger(Board* board, PlaceMove& p1, PlaceMove&p2) {
	return MaxLetterAIComp(p1, p2);
}