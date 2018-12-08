/*
 * Move.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

/* The Move class family encodes a move made by one player, including its type
   (PASS, EXCHANGE, PLACE), the tiles used (and use for blanks),
   start square, and direction (if needed).
   Call Move::parseMove() to turn an entered string into its subclass of
   Move, then call apply() on that returned move to have it execute.*/

#ifndef MOVE_H_
#define MOVE_H_

#include <vector>
#include <string>
#include <iostream>
#include "Tile.h"
#include "Bag.h"
#include "Dictionary.h"

// forward declaration to prevent circular includes
class Board;
class Player;

//I only used placemove
class PlaceMove
{

public:
	/* Creates a PLACE move, starting at row y, column x, placing the tiles
	   described by the string tileString. If "horizontal" is true, then the tiles
	   are placed horizontally, otherwise vertically.
	   Coordinates start with 1.
	   The string m is in the format described in HW4; in particular, a '?'
	   must be followed by the letter it is to be used as.
	*/
	PlaceMove (size_t x, size_t y, bool horizontal, std::string tileString, Player * p);

	~PlaceMove();

	void reset(size_t x, size_t y, std::string tileString);

	/* Returns true iff the move is a PLACE move */
	bool isWord () const
	{
		return true;
	}

	/* Returns the vector of tiles associated with a PLACE/EXCHANGE move.
	   Return value could be arbitrary for PASS moves. */
	std::vector<Tile*> tileVector () const;

	/* Executes this move, whichever type it is.
	   This may throw exceptions; students: it's up to you to
	   decide (and document) what exactly it throws*/
	//returns points earned
	int execute(Board* board, Bag* bag, Dictionary* dictionary);

	//Add more public/protected/private functions/variables here.
	int getMoveStartx() const;

	int getMoveStarty() const;

	bool isHorizontal() const;

	const std::string& getString() const;

private:
	int _x, _y;
	bool _horizontal;
	std::string tiles;
	Player* _player;
	int points;
};



#endif /* MOVE_H_ */
