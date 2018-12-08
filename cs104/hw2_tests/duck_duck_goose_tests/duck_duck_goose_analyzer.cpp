//
// Created by cs104 on 7/26/18.
//

#include "duck_duck_goose_analyzer.h"

#include <sstream>
#include <algorithm>

// regexes used in analysis
kwsys::RegularExpression isDuckRegex("^([0-9]+) is a Duck\\.$");
kwsys::RegularExpression isGooseRegex("^([0-9]+) is a Goose!$");
kwsys::RegularExpression itBeatGooseRegex("^([0-9]+) took ([0-9]+)'s spot!$");
kwsys::RegularExpression gooseBeatItRegex("^([0-9]+) is out!$");
kwsys::RegularExpression newItChosenRegex("^([0-9]+) was chosen as the new it\\.$");
kwsys::RegularExpression winnerRegex("^Winner is ([0-9]+)!$");

testing::AssertionResult analyzeDDGRoundOutput(std::string const & roundOutput, std::vector<int> const & circlePlayers, int const & itPlayer, DuckDuckGooseRoundResults & roundResults, size_t currRoundNumber)
{
	// reset round results
	roundResults.gameWon = false;
	roundResults.gooseWon = false;
	roundResults.goosePlayer = 0;
	roundResults.newItPlayer = 0;

	std::istringstream roundStream(roundOutput);

	// true iff it has picked the first duck yet
	bool startedCounting = false;

	// circular index that "it" stopped at to choose the goose
	size_t gooseIndex = 0;

	// iterator to the player that was previously counted as duck (if startedCounting was true)
	std::vector<int>::const_iterator itCurrentIterator;

	// true iff a goose has been chosen a nd the next line should be the result of their chase
	bool gooseChosen = false;

	// true iff a new it has been chosen
	bool newItChosen = false;

	// true iff the chase has concluded
	bool roundOver = false;

	// prefix for error messages with the round number
	std::string roundPrefix = "In round " + std::to_string(currRoundNumber) + ": ";

	// iterate through each line of output
	while(!roundStream.eof())
	{
		std::string outputLine;
		std::getline(roundStream, outputLine);

		if(roundStream.eof() && outputLine.empty())
		{
			break;
		}

		// this code below kind of works like a state machine: for each line, it checks which
		// type of line it is, then determines whether that line is valid in at this point in the round,
		// and finally updates some variables to reflect the new state.
		if(isDuckRegex.find(outputLine)) // "<player> is a Duck."
		{
			if(roundOver)
			{
				return testing::AssertionFailure() << roundPrefix << "Extra messages after end of round!";
			}

			int playerCounted = std::stoi(isDuckRegex.match(1));

			if(!startedCounting)
			{
				// set start of count-off
				itCurrentIterator = std::find(circlePlayers.begin(), circlePlayers.end(), playerCounted);

				if(itCurrentIterator == circlePlayers.end())
				{
					return testing::AssertionFailure() << roundPrefix << "Program counted off nonexistant player " << playerCounted;
				}

				startedCounting = true;
			}
			else
			{
				// move it iterator to next player
				++itCurrentIterator;
				if(itCurrentIterator == circlePlayers.end())
				{
					itCurrentIterator = circlePlayers.begin();
				}

				if(playerCounted != *itCurrentIterator)
				{
					return testing::AssertionFailure() << roundPrefix << "Program counted off player " << playerCounted << ", but the correct next player was " << *itCurrentIterator;
				}
			}

			++gooseIndex;
		}
		else if(isGooseRegex.find(outputLine)) // "<player> is a Goose!"
		{
			if(roundOver)
			{
				return testing::AssertionFailure() << roundPrefix << "Extra messages after end of round!";
			}

			int playerCounted = std::stoi(isGooseRegex.match(1));
			std::vector<int>::const_iterator goosePlayerIter = std::find(circlePlayers.begin(), circlePlayers.end(), playerCounted);

			if(goosePlayerIter == circlePlayers.end())
			{
				return testing::AssertionFailure() << roundPrefix << "Program chose nonexistent player " << playerCounted << " as a goose!";
			}

			if(startedCounting)
			{
				// move it iterator to next player
				++itCurrentIterator;
				if(itCurrentIterator == circlePlayers.end())
				{
					itCurrentIterator = circlePlayers.begin();
				}

				if(playerCounted != *itCurrentIterator)
				{
					return testing::AssertionFailure() << roundPrefix << "Program chose player " << playerCounted << " as a goose, but the correct next player was " << *itCurrentIterator;
				}
			}
			else
			{
				// first player counted was a goose
				startedCounting = true;
			}

			gooseChosen = true;
			roundResults.gooseIndex = gooseIndex;
			roundResults.goosePlayer = playerCounted;
		}
		else if(itBeatGooseRegex.find(outputLine)) // "<it player> took <goose player>'s spot!"
		{
			if(roundOver)
			{
				return testing::AssertionFailure() << roundPrefix << "Extra messages after end of round!";
			}

			if(!gooseChosen)
			{
				return testing::AssertionFailure() << roundPrefix << "Program did not select a goose before starting the chase!";
			}

			int reportedItPlayer = std::stoi(itBeatGooseRegex.match(1));
			int goosePlayer = std::stoi(itBeatGooseRegex.match(2));

			if(reportedItPlayer != itPlayer)
			{
				return testing::AssertionFailure() << roundPrefix << "Incorrect it player in chase winner message!";
			}

			if(goosePlayer != roundResults.goosePlayer)
			{
				return testing::AssertionFailure() << roundPrefix << "Incorrect goose player in chase winner message!";
			}

			roundResults.gooseWon = false;
			roundResults.newItPlayer = roundResults.goosePlayer;
			roundOver = true;
			newItChosen = true;
		}
		else if(gooseBeatItRegex.find(outputLine)) // "<it player> is out!"
		{
			if(roundOver)
			{
				return testing::AssertionFailure() << roundPrefix << "Extra messages after end of round!";
			}

			if(!gooseChosen)
			{
				return testing::AssertionFailure() << roundPrefix << "Program did not select a goose before starting the chase!";
			}

			int reportedItPlayer = std::stoi(gooseBeatItRegex.match(1));

			if(reportedItPlayer != itPlayer)
			{
				return testing::AssertionFailure() << roundPrefix << "Incorrect it player in chase winner message!  Was " << reportedItPlayer << ", should have been " << itPlayer;
			}

			roundResults.gooseWon = true;
			roundOver = true;
		}
		else if(newItChosenRegex.find(outputLine)) // "<new it player> was chosen as the new it."
		{
			if(!roundOver)
			{
				return testing::AssertionFailure() << roundPrefix << "New it was chosen before round ended!";
			}

			if(newItChosen)
			{
				return testing::AssertionFailure() << roundPrefix << "New it was chosen multiple times!";
			}

			roundResults.newItPlayer = std::stoi(newItChosenRegex.match(1));

			if(std::find(circlePlayers.begin(), circlePlayers.end(), roundResults.newItPlayer) == circlePlayers.end())
			{
				return testing::AssertionFailure() << roundPrefix << "Program chose nonexistent player " << roundResults.newItPlayer << " as the new it!";
			}

			newItChosen = true;

		}
		else if(winnerRegex.find(outputLine)) // "Winner is <player>!"
		{
			if(!roundOver)
			{
				return testing::AssertionFailure() << roundPrefix << "Winner was chosen before round ended!";
			}

			if(std::stoi(winnerRegex.match(1)) != roundResults.goosePlayer)
			{
				return testing::AssertionFailure() << roundPrefix << "Winner chosen was not the goose player!";
			}

			roundResults.gameWon = true;
		}
		else
		{
			return testing::AssertionFailure() << roundPrefix << "Unrecognized output line \"" << outputLine << '\"';
		}

	}

	if(!startedCounting)
	{
		return testing::AssertionFailure() << roundPrefix << "It player never started counting in this round!";
	}

	if(!gooseChosen)
	{
		return testing::AssertionFailure() << roundPrefix << "No goose was chosen in this round!";
	}

	if(!roundOver)
	{
		return testing::AssertionFailure() << roundPrefix << "The goose vs it chase never occurred in this round!";
	}

	if(!roundResults.gameWon && !newItChosen)
	{
		return testing::AssertionFailure() << roundPrefix << "No new it player was chosen in this round!";
	}

	return testing::AssertionSuccess();
}

testing::AssertionResult checkDDGGameOutput(std::string const & gameOutput, std::vector<int> const & startingPlayers, int const & startingItPlayer)
{
	std::istringstream gameOutputStream(gameOutput);
	std::stringstream currentRoundOutput;

	bool prevLineWasChase = false;

	// tracks if the program outputted a winner message
	bool gameWon = false;

	// keeps track of the players present in the current round of the game
	std::vector<int> currentPlayers = startingPlayers;
	int currentItPlayer = startingItPlayer;

	// for debugging messages only
	size_t currRoundNumber = 1;

	// iterate through each line of output and chunk it into rounds, which are fed to analyzeDDGRoundOutput
	while(!gameOutputStream.eof())
	{
		bool skipCurrentLine = false;

		std::string outputLine;
		std::getline(gameOutputStream, outputLine);

		bool endOfRound = false;

		bool finalBlankLine = gameOutputStream.eof() && outputLine.empty();

		if(finalBlankLine)
		{
			if(currentRoundOutput.str().empty())
			{
				break;
			}
			else
			{
				// end of data, but there's still a round to be processed
				endOfRound = true;
				skipCurrentLine = true;
			}
		}

		if(!endOfRound)
		{
			if(winnerRegex.find(outputLine) || newItChosenRegex.find(outputLine))
			{
				// this is the last line, append it
				currentRoundOutput << outputLine << std::endl;
				skipCurrentLine = true;
				endOfRound = true;
			}
		}

		if(!endOfRound && prevLineWasChase)
		{
			//this is the first line of the new round, append it
			endOfRound = true;
		}

		if(endOfRound)
		{
			//std::cout << ">> Sending round for analysis: " << std::endl << currentRoundOutput.str();

			// analyze the round that just ended
			DuckDuckGooseRoundResults results;
			testing::AssertionResult analysisAssertion = analyzeDDGRoundOutput(currentRoundOutput.str(), currentPlayers, currentItPlayer, results, currRoundNumber);
			if(!analysisAssertion)
			{
				return analysisAssertion;
			}

			// update what we know about the players
			if(results.gooseWon)
			{
				if(!results.gameWon)
				{
					// remove the new it from the list
					currentPlayers.erase(std::find(currentPlayers.begin(), currentPlayers.end(), results.newItPlayer));
				}
			}
			else
			{
				// replace goose player with it player
				*std::find(currentPlayers.begin(), currentPlayers.end(), results.goosePlayer) = currentItPlayer;
			}
			currentItPlayer = results.newItPlayer;
			gameWon |= results.gameWon;


			// reset accumulated output
			currentRoundOutput.str(std::string{});
		}

		if(!skipCurrentLine)
		{
			// read next line of output in
			currentRoundOutput << outputLine << std::endl;
		}

		prevLineWasChase = (gooseBeatItRegex.find(outputLine) || itBeatGooseRegex.find(outputLine));

	}

	if(!currentRoundOutput.str().empty())
	{
		return testing::AssertionFailure() << "There is extra data at end of file that was not part of a round: \"" << currentRoundOutput.str() << '\"';
	}

	if(!gameWon)
	{
		return testing::AssertionFailure() << "Game ended with no winner!";
	}

	return testing::AssertionSuccess();
}