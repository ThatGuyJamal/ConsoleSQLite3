#pragma once

// C++ Standard Library
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include "crud.hpp"

/// <summary>
/// Runs the command line interface for the program.
/// </summary>
/// <param name="db">A pointer to the SQLite database</param>
void runCLI(sqlite3* db);

void printFormatedCommandList();

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
void processTokens(sqlite3* db, std::vector<std::string> tokens);