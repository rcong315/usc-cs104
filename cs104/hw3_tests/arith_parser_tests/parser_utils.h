/*
 * Header for utility functions for testing hw3's parser problem
 */

#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include <user_code_runner.h>

#include <gtest/gtest.h>

#include <string>
#include <vector>

// Runs the parser program on the given input, and set output to the line it returned.
testing::AssertionResult runParser(std::string const & testName, std::string const & input, std::string & output);

// Runs the parser program on the given inputs, and set outputs to the list of lines it returned.
testing::AssertionResult runParser(std::string const & testName, std::vector<std::string> const & input, std::vector<std::string> & output);

#endif