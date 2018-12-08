#include "Move.h"
#include "Board.h"
#include "Player.h"

//initialize private memberss
PlaceMove::PlaceMove (size_t x, size_t y, bool horizontal, std::string tileString, Player * p) {
    _x = x;
    _y = y;
    _horizontal = horizontal;
    _player = p;
    tiles = tileString;
}

PlaceMove::~PlaceMove() {
    //nothing to delete
}

//turn move tiles to string
std::vector<Tile*> PlaceMove::tileVector() const {
    std::string tilescopy = tiles;
    std::vector<Tile*> tilestoplace;
    std::vector<Tile*> handcopy = _player -> getHandTiles();
    for (unsigned int i = 0; i < tilescopy.length(); i++) {
        //remove blank tiles
        if (tilescopy.at(i) == '?') {
            tilescopy.erase(i, 1);
            tilestoplace.push_back(new Tile(tilescopy.at(i), 0));
            i++;
            if (i == tilescopy.length()) {
                break;
            }
        }
        for (unsigned int j = 0; j < handcopy.size(); j++) {
            if (tilescopy.at(i) == handcopy[j] -> getLetter()) {
                tilestoplace.push_back(new Tile(handcopy[j] -> getLetter(), handcopy[j] -> getPoints()));
                break;
            }
        }
    }
    return tilestoplace;
    //player assumed to have all tiles we are looking for
}

//execute the move
int PlaceMove::execute(Board* board, Bag* bag, Dictionary* dictionary) {
    //calls board's execute function
    int pointsearned = board -> executePlaceMove(*this);
    //take and add tiles from player to bag and bag to player
    std::vector<Tile*> placedtiles = _player -> takeTiles(tiles, true);
    bag -> addTiles(placedtiles);
    std::vector<Tile*> drawntiles = bag -> drawTiles(placedtiles.size());
    _player -> addTiles(drawntiles);
    //add 50 points if player used all tiles
    if (placedtiles.size() == _player -> getMaxTiles()) {
        pointsearned += 50;
    }
    _player -> addPoints(pointsearned);
    return pointsearned;
}

//get x position of first tile
int PlaceMove::getMoveStartx() const {
    return _x;
}

//get y position of first tile
int PlaceMove::getMoveStarty() const {
    return _y;
}

//returns whether move is horizontal or vertical
bool PlaceMove::isHorizontal() const {
    return _horizontal;
}

//return tiles to be used as string
const std::string& PlaceMove::getString() const {
	return tiles;
}

//reset the move
void PlaceMove::reset(size_t x, size_t y, std::string tileString) {
	_x = x;
	_y = y;
	tiles = tileString;
}
