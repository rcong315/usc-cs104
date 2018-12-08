#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Board.h"
#include "Bag.h"
#include "Dictionary.h"
#include "Player.h"
#include "ConsolePrinter.h"
#include "Exceptions.h"

using namespace std;

vector<Player*> setPlayers(Bag*& bag, int maxhandsize);
void printWinners(vector<Player*> playerlist);
void freeMemory(vector<Player*>& playerlist);

int main(int argc, char* argv[]) {
    //check if config file given
    if (argc != 2) {
        return 1;
    }
    //open config file
    ifstream config(argv[1]);
    if (config.fail()) {
        return 1;
    }
    //take input from config file
    string keyword;
    int maxhandsize;
    string boardfile;
    string tilesfile;
    string dictionaryfile;
    uint32_t seed;
    while (!config.eof()) {
        config >> keyword;
        if (keyword == "HANDSIZE:") {
            config >> maxhandsize;
        }
        else if (keyword == "BOARD:") {
            config >> boardfile;
        }
        else if (keyword == "TILES:") {
            config >> tilesfile;
        }
        else if (keyword == "DICTIONARY:") {
            config >> dictionaryfile;
        }
        else {
            config >> seed;
        }
    }
    config.close();
    //initialize classes
    Board* board = new Board(boardfile);
    Bag* bag = new Bag(tilesfile, seed);
    Dictionary* dictionary = new Dictionary(dictionaryfile);
    ConsolePrinter* game = new ConsolePrinter;
    //initilize players
    vector<Player*> playerlist = setPlayers(bag, maxhandsize);
    int players = playerlist.size();
    game -> printBoard(*board);
    //loop until a winner is found
    int turn = 0;
    int passesinarow = 0;
    bool firstplace = true;
    while (1) {
        int playerturn = turn % players;
        Player* currplayer = playerlist[playerturn];
        game -> printHand(*currplayer);
        cout << endl << currplayer -> getName() << "'s turn: ";
        string move;
        getline(cin, move);
        stringstream movestream(move);
        string movetype;
        string movetiles;
        //take move from user ignoring case
        string temp;
        movestream >> temp;
        for (unsigned int i = 0; i < temp.size(); i++) {
            movetype += toupper(temp.at(i));
        }
        //player places
        if (movetype == "PLACE") {
            char dir;
            int x, y;
            movestream >> dir;
            movestream >> y;
            movestream >> x;
            string temptiles;
            movestream >> temptiles;
            //ignore case
            for (unsigned int i = 0; i < temptiles.size(); i++) {
                movetiles += tolower(temptiles.at(i));
            }
            bool horizontal = (dir == '-');
            vector< pair<string, unsigned int> > wordsformed;
            PlaceMove place(x, y, horizontal, movetiles, currplayer);
            bool outofbounds = false;
            //make sure not out of bounds
            try {
                wordsformed = board -> getPlaceMoveResults(place);
            }
            catch (PlaceException e) {
                outofbounds = true;
                cout << e.getMessage() << endl;
            }
            //loop while input is not valid
            while (outofbounds || !board -> isLegal(place, dictionary, wordsformed) || (!firstplace && !board -> checkForAdjacentTiles(place)) || !currplayer -> hasTiles(movetiles, true) || (firstplace && !board -> moveHasStart(place))) {
                if (outofbounds) {
                }
                else if (!firstplace && !board -> checkForAdjacentTiles(place)) {
                    cout << "error: Place move has to be adjacent to at least one tile" << endl;
                }
                else if (!currplayer -> hasTiles(movetiles, true)) {
                    cout << "error: Player does not have required tiles" << endl;
                }
                else if (firstplace && !board -> moveHasStart(place)) {
                    cout << "error: First move does not land on start" << endl;
                }
                //take input again
                cout << "Try again: ";
                getline(cin, move);
                cout << endl;
                movestream.clear();
                movestream.str(move);
                movestream >> movetype;
                movestream >> dir;
                movestream >> y;
                movestream >> x;
                movestream >> movetiles;
                horizontal = (dir == '-');
                place = PlaceMove(x, y, horizontal, movetiles, currplayer);
                try {
                    wordsformed = board -> getPlaceMoveResults(place);
                    outofbounds = false;
                }
                catch (PlaceException e) {
                    cout << e.getMessage() << endl;
                }
            }
            //execute place move
            firstplace = false;
            int pointsearned = place.execute(board, bag, dictionary);
            string drawn = currplayer -> newTilesToString();
            game -> printBoard(*board);
            //print result
            cout << endl << currplayer -> getName() << " formed the words: ";
            for (unsigned int i = 0; i < wordsformed.size(); i++) {
                cout << wordsformed[i].first << " ";
            }
            cout << endl << "Points earned: " << pointsearned << endl;
            cout << "Total points: " << currplayer -> getPoints() << endl;
            cout << "New tiles drawn: " << drawn << endl;
            passesinarow = 0;
            game -> printHand(*currplayer);
            cout << endl << "Press enter to continue";
            //wait for user confirmation
            cin.ignore(); 
        }
        //player exchanges
        else if (movetype == "EXCHANGE") {
            string temptiles;
            movestream >> temptiles;
            //ignore case
            for (unsigned int i = 0; i < temptiles.size(); i++) {
                movetiles += tolower(temptiles.at(i));
            }
            //loop while command not valid
            while (movetiles.empty() || !currplayer -> hasTiles(movetiles, false)) {
                if (movetiles.empty()) {
                    cout << "error: Please choose tiles to exchange" << endl;
                }
                else {
                    cout << "error: Player does not have the required tiles" << endl;
                }
                //take input again
                cout << "Try again: ";
                getline(cin, move);
                movestream.clear();
                movestream.str(move);
                movestream >> movetype;
                movestream >> movetiles;
            }
            //execute exchange move
            int numtiles = movetiles.length();
            bag -> addTiles(currplayer -> takeTiles(movetiles, false));
            vector<Tile*> drawntiles = bag -> drawTiles(numtiles);
            currplayer -> addTiles(drawntiles);
            string drawn;
            for (unsigned int i = 0; i < drawntiles.size(); i++) {
                drawn += drawntiles[i] -> getLetter();
            }
            //print move results
            cout << currplayer -> getName() << " exchanged " << movetiles;
            cout << " for " << drawn << endl;
            passesinarow = 0;
            game -> printHand(*currplayer);
            cout << endl << "Press enter to continue";
            //wait for user confirmation
            cin.ignore();
        }
        //player passes
        else {
            cout << currplayer -> getName() << " passes" << endl;
            passesinarow++;
            cout << "Press enter to continue";
            //wait for user confirmation
            cin.ignore();
        }
        game -> printBoard(*board);
        //check for endgame
        if (currplayer -> handEmpty()) {
            cout << endl << currplayer -> getName() << "'s hand is empty and the bag is empty" << endl;
            //add points to players according to their hand
            for (int i = 0; i < players; i++) {
                Player* otherplayer = playerlist[i];
                if (currplayer != otherplayer) {
                    otherplayer -> addPoints((otherplayer -> pointsInHand()) * -1);
                    currplayer -> addPoints(otherplayer -> pointsInHand());
                }
            }
            printWinners(playerlist);
            break;
        }
        //if all players pass in a row, end game
        if (passesinarow == players) {
            cout << endl << "All players passed" << endl;
            printWinners(playerlist);
            break;
        }
        turn++;
    }
    //free all memory
    freeMemory(playerlist);
    delete board;
    delete bag;
    delete dictionary;
    delete game;
    return 0;
}

//sets up players and gives them a hand each
vector<Player*> setPlayers(Bag*& bag, int maxhandsize) {
    int players;
    cout << "How many players? ";
    cin >> players;
    cin.ignore();
    vector<Player*> playerlist;
    for (int i = 0; i < players; i++) {
        string name;
        cout << endl << "What is player " << i + 1 << "'s name? ";
        getline(cin, name);
        Player* player = new Player(name, maxhandsize);
        player -> addTiles(bag -> drawTiles(maxhandsize));
        playerlist.push_back(player);
    }
    return playerlist;
}

//print the winners, winners have the most points
void printWinners(vector<Player*> playerlist) {
    vector<Player*> winners;
    int players = playerlist.size();
    int maxpoints = playerlist[0] -> getPoints();
    for (int i = 1; i < players; i++) {
        if (playerlist[i] -> getPoints() > maxpoints) {
            maxpoints = playerlist[i] -> getPoints();
        }
    }
    for (int i = 0; i < players; i++) {
        if (playerlist[i] -> getPoints() == maxpoints) {
            winners.push_back(playerlist[i]);
        }
    }
    cout << "Game over" << endl;
    for (int i = 0; i < players; i++) {
        cout << "Player " << i + 1 << ": " << playerlist[i] -> getName();
        cout << " has " << playerlist[i] -> getPoints() << " points" << endl;
    }
    if (winners.size() == 1) {
        cout << endl << "Winner: " << winners[0] -> getName() << endl;
    }
    else {
        cout << endl << "Winners: ";
        for (unsigned int i = 0; i < winners.size(); i++) {
            cout << winners[i] -> getName() << " ";
        }
        cout << endl;
    }
}

//free player memory
void freeMemory(vector<Player*>& playerlist) {
    for (unsigned int i = 0; i < playerlist.size(); i++) {
        delete playerlist[i];
    }
    playerlist.clear();
}