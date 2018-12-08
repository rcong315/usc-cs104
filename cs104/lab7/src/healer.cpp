#include "healer.h"

using namespace std;

Healer::Healer(string name) : Player(name) {
	// nothing to do here
}

void Healer::doAction(Player *target) {
	int hp = target -> getHP();
	hp += 75;
	if (hp > target -> getMaxHP()) {
		hp = target -> getMaxHP();
	}
	target -> setHP(hp);
}