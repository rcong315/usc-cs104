#include "duck_duck_goose.h"
#include "circular_list_int.h"

#include <fstream>

int main(int argc, char* argv[]) {
	//check if any arguments missing
	if (argc != 3) {
		return 1;
	}

	//create streams for input and output
	std::ifstream inFile;
	std::ofstream outFile;
	//create a gameData
	GameData* game = new GameData();
	//create variable to hold data from input file
	int seed;
	int players;
	
	//open input and output files
	inFile.open(argv[1]);
	if (inFile.fail()) {
		return 1;
	}
	outFile.open(argv[2]);
	if (outFile.fail()) {
		return 1;
	}

	//take rand seed from input file
	inFile >> seed;
	srand(seed);
	//take number of players
	inFile >> players;
	//take it player
	inFile >> game -> itPlayerID;
	//loop until all players added
	for (int i = 0; i < players - 1; i++) {
		//take player id's from input file and add to a circular linked list
		int id;
		inFile >> id;
		game -> playerList.push_back(id);
	}
	//close input file
	inFile.close();

	//loop until game is over
	while (game -> itPlayerID != 0) {
		//run a round
		simulateDDGRound(game, outFile);
	}

	//close output file
	outFile.close();
	return 0;
}

void simulateDDGRound(GameData * gameData, std::ostream & output) {
	//choose the goose
	size_t goosePlace = (size_t)(rand() % (4 * (gameData -> playerList.size())));
	//loop through all the ducks
	for (size_t i = 0; i < goosePlace; i++) {
		output << gameData -> playerList.get(i) << " is a Duck." << std::endl;
	}

	//set the goose
	int gooseID = gameData -> playerList.get(goosePlace);
	output << gooseID << " is a Goose!" << std::endl;
	
	//goose and it compete for winner
	int goose = 0;
	int it = 0;
	while (goose == it) {
		goose = rand() % 49 + 1;
		it = rand() % 49 + 1;
	}

	//if the it wins
	if (it > goose) {
		//the it takes the goose's place and the goose becomes the new it
		gameData -> playerList.set(goosePlace, gameData -> itPlayerID);
		output << gameData -> itPlayerID << " took " << gooseID << "'s spot!" << std::endl;
		gameData -> itPlayerID = gooseID;
	}

	//if the goose wins
	else {
		//the it is out of the game
		output << gameData -> itPlayerID << " is out!" << std::endl;
		//if only one player left end the game
		if (gameData -> playerList.size() == 1) {
			output << "Winner is " << gooseID << "!" << std::endl;
			gameData -> itPlayerID = 0;
		}
		//otherwise choose a new it and remove them from the list
		else {
			size_t newItPlace = (size_t)(rand() % (4 * (gameData -> playerList.size())));
			int newIt = gameData -> playerList.get(newItPlace);
			gameData -> itPlayerID = newIt;
			gameData -> playerList.remove(newItPlace);
			output << newIt << " was chosen as the new it." << std::endl;
		}
	}
}