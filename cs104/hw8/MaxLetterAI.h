#ifndef MAXLETTERAI_H_
#define MAXLETTERAI_H_

#include "AIPlayer.h"

class MaxLetterAI: public AIPlayer
{

public:
	/* Constructor giving the player the given name, and setting their points to 0.
	   Does not give the player any tiles.
	*/
	MaxLetterAI (std::string const & name, size_t maxTiles);

	/* Destructor for a player. Deletes all the tiles the player still has. */
	~MaxLetterAI ();
	
	virtual bool larger(Board* board, PlaceMove& p1, PlaceMove&p2);

};

#endif /* PLAYER_H_ */