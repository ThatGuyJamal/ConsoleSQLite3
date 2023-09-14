#include "cli.hpp"

std::string const WELCOME_MESSAGE = "Welcome to my simple SQLite3 database program!";
std::string const PROMPT = ">> ";

void runCLI(sqlite3* db)
{
	// The current input from the user
	std::string userInput;

	std::cout << WELCOME_MESSAGE << std::endl;

	// Display the list of commands
	printFormatedCommandList();

	while (true)
	{
		std::cout << PROMPT;

		// Get the entire line of input from the user.
		std::getline(std::cin, userInput);

		// Tokenize the input to separate the command and arguments
		std::vector<std::string> tokens = tokenize(userInput);

		processTokens(db, tokens);
	}
};

void processTokens(sqlite3* db, std::vector<std::string> tokens)
{
	if (!tokens.empty())
	{
		if (tokens[0] == "exit")
		{
			std::cout << "Exiting program." << std::endl;
			closeDb(db); // Make sure we close the database before exiting the program.
			exit(0);
		}

		if (tokens[0] == "table-list")
		{
			listTables(db);
		}
		else if (tokens[0] == "table-create")
		{
			std::cout << "table-create command todo" << std::endl;
		}
		else if (tokens[0] == "table-drop")
		{
			std::cout << "table-drop command todo" << std::endl;
		}
		else if (tokens[0] == "table-insert")
		{
			std::cout << "table-insert command todo" << std::endl;
		}
		else if (tokens[0] == "table-select")
		{
			std::cout << "table-select command todo" << std::endl;
		}
		else if (tokens[0] == "table-update")
		{
			std::cout << "table-update command todo" << std::endl;
		}
		else
		{
			std::cout << "Invalid command. Please try again..." << std::endl;
		}
	}
}

std::vector<std::string> tokenize(std::string input)
{
	std::vector<std::string> tokens;

	size_t start = 0, end = 0;
	while ((end = input.find(' ', start)) != std::string::npos)
	{
		tokens.push_back(input.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(input.substr(start)); // Add the last token

	return tokens;
}

void printFormatedCommandList()
{
	std::array<std::string, 7> const cmds = {
		"table-list",
		"table-create",
		"table-drop",
		"table-insert",
		"table-select",
		"table-update",
		"exit"
	};

	// Display the list of commands separated by commas
	std::cout << "Available commands: ";

	for (size_t i = 0; i < cmds.size(); ++i)
	{
		std::cout << "\"" << cmds[i] << "\"";

		// Add a comma and space if it's not the last element
		if (i < cmds.size() - 1)
		{
			std::cout << ", ";
		}
	}

	std::cout << std::endl;
}