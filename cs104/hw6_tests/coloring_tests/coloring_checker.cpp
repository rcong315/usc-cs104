//
// Created by cs104 on 11/29/18.
//

#include "coloring_checker.h"

#include <kwsys/SystemTools.hxx>

#include <misc_utils.h>
#include <user_code_runner.h>

#include <fstream>

testing::AssertionResult testColoring(std::string const &testName, size_t numCountries, InputMap const &map,
                                      bool useValgrind)
{
	// set up file structure
	std::string executablePath = USER_CODE_DIR "/coloring";
	std::string testFolder =  TEST_BINARY_DIR "/coloring_tests/testFiles/" + testName;
	kwsys::SystemTools::MakeDirectory(testFolder);
	std::string inputFilePath = testFolder + "/input.txt";
	std::string outputFilePath = testFolder + "/output.txt";

	std::ofstream inputWriter(inputFilePath);
	inputWriter << numCountries << " " << map.size() << " " << map[0].size() << std::endl;

	for(std::string const & line : map)
	{
		inputWriter << line << std::endl;
	}

	// run the program
	UserCodeRunner runner(testFolder, executablePath, {inputFilePath}, outputFilePath, useValgrind);
	testing::AssertionResult result = runner.execute();

	if(!result)
	{
		return result;
	}


	// read in output
	std::vector<MapColoring> colorings;
	MapColoring currentColoring;

	{
		std::ifstream outputFile(outputFilePath);

		if(!outputFile)
		{
			return testing::AssertionFailure() << "Couldn't open output file " << outputFilePath;
		}

		while(outputFile)
		{
			std::string outputLine;
			std::getline(outputFile, outputLine);

			// skip blank lines
			if(outputLine.empty())
			{
				continue;
			}

			std::istringstream lineStream(outputLine);

			char countryChar;
			Color color;

			lineStream >> countryChar;
			lineStream >> color;

			if(color < 1 || color > 4)
			{
				return testing::AssertionFailure() << "Illegal value " << color << " for color of country " << countryChar << ".  Must be in the range 1-4.";
			}

			//std::cout << "Parsed color " << color << " for country " << countryChar << std::endl;

			currentColoring[countryChar] = color;

			// students can output multiple solutions, so if we've gotten a complete set of colors, start reading in the next solution
			if(currentColoring.size() >= numCountries)
			{
				colorings.push_back(currentColoring);
				currentColoring.clear();

				//std::cout << ">> Moving to next coloring!" << std::endl;
			}
		}

	}

	// check output

	if(colorings.empty())
	{
		return testing::AssertionFailure() << "A complete set of map colorings was not output!";
	}

	if(colorings.size() > 1)
	{
		std::cout << "Test suite: Beginning check of all " << colorings.size() << " solutions" << std::endl;
	}

	for(size_t index = 0; index < colorings.size(); ++index)
	{
		testing::AssertionResult checkResult = checkValidColoring(map, colorings[index]);

		if(!checkResult)
		{
			// print something so the user knows which coloring the failure occurred on

			std::cout << "Checking returned coloring " << index << ": FAIL" << std::endl;
			return checkResult;
		}

		// below print commented because it introduced too much lag when we got into the hundreds of thousands of solutions
		//std::cout << "Checking returned coloring " << index << ": PASS" << std::endl;

	}

	std::cout << "Test suite: all coloring solutions validated!" << std::endl;

	return testing::AssertionSuccess();

}

InputMap makeMap(std::string const & mapString)
{
	InputMap map = splitString(mapString, "\n");

	// check consistency of map
	const size_t mapWidth = map[0].length();
	for(std::string line : map)
	{
		// check consistency of input
		if(line.size() != mapWidth)
		{
			throw std::runtime_error("test suite internal error: not all lines of input map are the same length!");
		}
	}

	return map;
}

testing::AssertionResult checkValidColoring(InputMap const &map, MapColoring const &coloring)
{
	// check each border and make sure that different letters are the same color

	for(size_t yPos = 0; yPos < map.size() - 1; ++yPos)
	{
		for(size_t xPos = 0; xPos < map[0].length() - 1; ++xPos)
		{
			if(map[yPos][xPos] != map[yPos][xPos + 1])
			{
				char leftCountryChar = map[yPos][xPos];
				char rightCountryChar = map[yPos][xPos + 1];

				// horizontal border between countries
				MapColoring::const_iterator leftColorIter = coloring.find(leftCountryChar);
				MapColoring::const_iterator rightColorIter = coloring.find(rightCountryChar);

				if (leftColorIter == coloring.end())
				{
					return testing::AssertionFailure() << "The country with letter " << leftCountryChar
					                                   << " was not assigned a color!";
				}
				else if (rightColorIter == coloring.end())
				{
					return testing::AssertionFailure() << "The country with letter " << rightCountryChar
					                                   << " was not assigned a color!";
				}
				else if (leftColorIter->second == rightColorIter->second)
				{
					return testing::AssertionFailure() << "Countries " << leftCountryChar << " and " << rightCountryChar << " share a border at (" << xPos << ".5, " << yPos << "), but were issued the same color!";
				}

			}

			if(map[yPos][xPos] != map[yPos + 1][xPos])
			{
				char topCountryChar = map[yPos][xPos];
				char bottomCountryChar = map[yPos + 1][xPos];

				// horizontal border between countries
				MapColoring::const_iterator topColorIter = coloring.find(topCountryChar);
				MapColoring::const_iterator bottomColorIter = coloring.find(bottomCountryChar);

				if (topColorIter == coloring.end())
				{
					return testing::AssertionFailure() << "The country with letter " << topCountryChar
					                                   << " was not assigned a color!";
				}
				else if (bottomColorIter == coloring.end())
				{
					return testing::AssertionFailure() << "The country with letter " << bottomCountryChar
					                                   << " was not assigned a color!";
				}
				else if (topColorIter->second == bottomColorIter->second)
				{
					return testing::AssertionFailure() << "Countries " << topCountryChar << " and " << bottomCountryChar << " share a border at (" << xPos << ", " << yPos << ".5), but were issued the same color!";
				}

			}
		}
	}

	return testing::AssertionSuccess();
}
