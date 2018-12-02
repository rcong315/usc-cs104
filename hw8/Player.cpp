#include "Player.h"
#include <iostream>

//initialize private members
Player::Player (std::string const & name, size_t maxTiles) {
    pname = name;
    points = 0;
    maxhandsize = maxTiles;
}

//free tiles
Player::~Player () {
    std::vector<Tile*>::iterator it;
    for(it = hand.begin(); it != hand.end(); ++it) {
        delete *it;
    }
    hand.clear();
}

//returns the player's hand
std::vector<Tile*> Player::getHandTiles() const {
    return hand;
}

//checks to see if player has the tiles in string move
bool Player::hasTiles(std::string const & move, bool resolveBlanks) const {
    std::string movecopy = move;
    std::vector<Tile*> handcopy = hand;
    std::vector<Tile*>::iterator it;
    //if move is place then remove characters after ?'s
    if (resolveBlanks) {
        for (unsigned int i = 0; i < movecopy.length(); i++) {
            if (movecopy.at(i) == '?') {
                movecopy.erase(i + 1, 1);
            }
        }
    }
    //look for each tile
    for (unsigned int i = 0; i < movecopy.length(); i++) {
        it = handcopy.begin();
        while(1) {
            if (it == handcopy.end()) {
                return false;
            }
            if (movecopy.at(i) == (*it) -> getLetter()) {
                handcopy.erase(it);
                break;
            }
            ++it;
        }
    }
    return true;
}

//removes and returns tiles from player
std::vector<Tile*> Player::takeTiles (std::string const & move, bool resolveBlanks) {
    std::string movecopy = move;
    std::vector<Tile*> tiles;
    std::vector<Tile*>::iterator it;
    //if move is place then remove characters after ?'s
    if (resolveBlanks) {
        for (unsigned int i = 0; i < movecopy.length(); i++) {
            if (movecopy.at(i) == '?') {
                movecopy.erase(i + 1, 1);
            }
        }
    }
    //remove tiles from hand
    for(unsigned int i = 0; i < movecopy.length(); i++) {
        for (it = hand.begin(); it != hand.end(); ++it) {
            if (movecopy.at(i) == (*it) -> getLetter()) {
                tiles.push_back(*it);
                hand.erase(it);
                break;
            }
        }
    }
    tilestakeninlastmove = tiles.size();
    return tiles;
}

//add tiles to player's hand
void Player::addTiles (std::vector<Tile*> const & tilesToAdd) {
    for (unsigned int i = 0; i < tilesToAdd.size(); i++) {
        hand.push_back(tilesToAdd[i]);
    }
}

//max hand size
size_t Player::getMaxTiles() const {
    return maxhandsize;
}

//player's name
std::string Player::getName() {
    return pname;
}

//points player has
int Player::getPoints() {
    return points;
}

//add to player's points
void Player::addPoints(int pointstoadd) {
    points += pointstoadd;
}

//point total of tiles in hand
int Player::pointsInHand() {
    int handpoints = 0;
    std::vector<Tile*>::iterator it;
    for(it = hand.begin(); it != hand.end(); ++it) {
        int point = (*it) -> getPoints();
        handpoints += point;
    }
    return handpoints;
}

//whether hand is empty
bool Player::handEmpty() {
    return hand.empty();
}

//turns tiles taken in last move to a string
std::string Player::newTilesToString() {
    std::string tiles = "";
    for (unsigned int i = getMaxTiles() - tilestakeninlastmove; i < hand.size(); i++) {
        tiles += hand[i] -> getLetter();
    }
    return tiles;
}

//not an ai
bool Player::isAI() {
    return false;
}

//no ai move
std::string Player::getAIMove(Board* board, Dictionary* dictionary) {
    return "";
}

//turns tiles in hand to string of letters
std::string Player::handToString() {
    std::string tiles = "";
    for (unsigned int i = 0; i < hand.size(); i++) {
        tiles += hand[i] -> getLetter();
    }
    return tiles;
}