#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "inventory.h"

class Player {
	public:
		Player(std::string);
		virtual ~Player();

		int getHP();
		int getMaxHP();
		void setHP(int);
		Inventory * getInv();
		bool isDead();
		std::string getName();
		
		virtual void doAction(Player*) = 0;

	private:
		std::string name_;
		Inventory * inv;
		int maxhp_;
		int hp_;
};

#endif