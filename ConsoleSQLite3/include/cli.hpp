#pragma once

// C++ Standard Library
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <cstdlib>

#include "crud.hpp"

/// <summary>
/// Runs the command line interface for the program.
/// </summary>
void runCLI();

void printFormattedCommandList();

/// <summary>
/// Creates a vector of tokens from the input string.
/// </summary>
/// <param name="input">The string to tokenize</param>
/// <returns></returns>
std::vector<std::string> tokenize(std::string input);

/// <summary>
/// Processes the tokens from the user input.
/// </summary>
/// <param name="db">A pointer to the SQLite database</param>
/// <param name="tokens">The tokens to process</param>
void processTokens(std::vector<std::string> tokens);

/// <summary>
/// Parses the tokens for a SQL statement.
/// </summary>
/// <param name="tokens">The tokens to parse</param>
/// <param name="startIndex">The index to start parsing from</param>
std::string parseSQLStatement(const std::vector<std::string>& tokens, size_t startIndex);

void clearConsole();