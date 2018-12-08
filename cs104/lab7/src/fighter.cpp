#include "fighter.h"

using namespace std;

Fighter::Fighter(string name) : Player(name) {
	// nothing to do here
}

void Fighter::doAction(Player *target) {
	int hp = target -> getHP();
	hp -= 75;
	target -> setHP(hp);
}