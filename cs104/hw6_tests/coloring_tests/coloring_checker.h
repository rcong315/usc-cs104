//
// CS104 Coloring test suite automatic checker
//

#ifndef CS104_HW6_TEST_SUITE_COLORING_UTILS_H
#define CS104_HW6_TEST_SUITE_COLORING_UTILS_H

#include <gtest/gtest.h>

#include <map>
#include <vector>
#include <string>

typedef uint16_t Color;

// type for input map to the coloring program
typedef std::vector<std::string> InputMap;

// the result of a map coloring is parsed into this structure
typedef std::map<char, Color> MapColoring;

/**
 * Check that user's executable colors the provided map successfully.
 * @param testName
 * @param numCountries
 * @param map
 * @param useValgrind
 * @return
 */
testing::AssertionResult testColoring(std::string const &testName, size_t numCountries, InputMap const &map,
                                      bool useValgrind = true);

/**
 * Makes an input map from a multiline string
 * @param map
 * @return
 */
InputMap makeMap(std::string const & map);

/**
 * Checks that a coloring is valid for the given map
 * @param map
 * @param coloring
 * @return
 */
testing::AssertionResult checkValidColoring(InputMap const &map, MapColoring const &coloring);

#endif //CS104_HW6_TEST_SUITE_COLORING_UTILS_H
