//
// Created by cs104 on 7/26/18.
//

#ifndef CS104_HW2_TEST_SUITE_DUCK_DUCK_GOOSE_ANALYZER_H
#define CS104_HW2_TEST_SUITE_DUCK_DUCK_GOOSE_ANALYZER_H

#include <gtest/gtest.h>

#include <kwsys/RegularExpression.hxx>

#include <vector>
#include <string>

// struct to store data about a duck duck goose round obtained by parsing the output
struct DuckDuckGooseRoundResults
{
	int newItPlayer;
	int goosePlayer;
	size_t gooseIndex; // index of goose in circlePlayers
	bool gooseWon;
	bool gameWon; // if true, the goose player just won the game
};

// analyzes the text printed by a Duck Duck Goose round
// and determines whether or not the results were valid for the current game state.
// Also figures out what happened in the round, and returns the result in roundResults.
// NOTE: if an assertion failure is returned, the data in roundResults is undefined.
testing::AssertionResult analyzeDDGRoundOutput(std::string const & roundOutput, std::vector<int> const & circlePlayers, int const & itPlayer, DuckDuckGooseRoundResults & roundResults, size_t roundNumber = 1);

// analyzes the text printed by an entire Duck Duck Goose game
// and determines whether or not the output appears correct.
testing::AssertionResult checkDDGGameOutput(std::string const & gameOutput, std::vector<int> const & startingPlayers, int const & startingItPlayer);

#endif //CS104_HW2_TEST_SUITE_DUCK_DUCK_GOOSE_ANALYZER_H
