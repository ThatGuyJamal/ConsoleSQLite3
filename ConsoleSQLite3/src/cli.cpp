#include "../include/cli.hpp"

std::string const WELCOME_MESSAGE = "Welcome to my simple SQLite3 database program!";
std::string const PROMPT = ">> ";

void runCLI()
{
	// The current input from the user
	std::string userInput;

	std::cout << WELCOME_MESSAGE << std::endl;

	// Display the list of commands
	printFormattedCommandList();

	while (true)
	{
		std::cout << PROMPT;

		// Get the entire line of input from the user.
		std::getline(std::cin, userInput);

		// Tokenize the input to separate the command and arguments
		std::vector<std::string> tokens = tokenize(userInput);

		processTokens(tokens);
	}

	return;
};

void processTokens(std::vector<std::string> tokens)
{
	if (!tokens.empty())
	{
		if (tokens[0] == "exit")
		{
			std::cout << "Exiting program." << std::endl;
			exit(0);
		}

		else if (tokens[0] == "help")
		{
			printFormattedCommandList();
		}

		else if (tokens[0] == "clear")
		{
			clearConsole();
		}

		else if (tokens[0] == "list")
		{
			std::vector<std::string> tables = listTables();

			if (tables.empty())
			{
				std::cout << "No tables found in the database." << std::endl;
				return;
			}

			for (size_t i = 0; i < tables.size(); ++i)
			{
				std::cout << "\"" << tables[i] << "\"";

				// Add a comma and space if it's not the last element
				if (i < tables.size() - 1)
				{
					std::cout << ", ";
				}

			}

			std::cout << std::endl;
		}

		else if (tokens[0] == "create")
		{
			if (tokens.size() < 3)
			{
				std::cout << "Invalid command. Usage: table-create [name of table] (column data)" << std::endl;
			}
			else
			{
				std::string tableName = tokens[1];
				std::string sqlStatement = parseSQLStatement(tokens, 2);

				// Call the createNewTable function to create the table
				bool success = createNewTable(tableName, sqlStatement);

				if (success)
				{
					std::cout << "Table created successfully or already exists in the database." << std::endl;
				}
				else
				{
					std::cout << "Failed to create the table." << std::endl;
				}
			}
		}

		else if (tokens[0] == "drop")
		{
			if (tokens.size() < 2)
			{
				std::cout << "Invalid command. Usage: table-drop [name of table]" << std::endl;
			}
			else
			{
				std::string tableName = tokens[1];

				bool success = dropTable(tableName);

				if (success)
				{
					std::cout << "Table '" << tableName << "' dropped successfully." << std::endl;
				}
				else
				{
					std::cout << "Failed to drop the table." << std::endl;
				}
			}
		}

		else if (tokens[0] == "insert")
		{
			if (tokens.size() < 2)
			{
				std::cout << "Invalid command. Usage: insert [name of table] (colums) (values)" << std::endl;
			}
			else
			{
				// Call the insertData function to insert the data
				bool success = insertData("", "", "");

				if (success)
				{
					std::cout << "Data inserted successfully." << std::endl;
				}
				else
				{
					std::cout << "Failed to insert data." << std::endl;
				}
			}
		}

		else if (tokens[0] == "select")
		{
			if (tokens.size() < 2)
			{
				std::cout << "Invalid command. Usage: select [name of table] [optional columns]" << std::endl;
			}
			else
			{
				std::string tableName = tokens[1];
				std::string columns = "*"; // Default to "*"

				// Check if optional columns are provided
				if (tokens.size() > 2)
				{
					// Join the remaining tokens to form the columns string
					columns = tokens[2];
					for (size_t i = 3; i < tokens.size(); ++i)
					{
						columns += " " + tokens[i];
					}
				}

				// Call selectData and pass the table name and columns
				std::vector<std::vector<std::string>> selectedData = selectData(tableName, columns);

				// Process and display the selected data
				if (!selectedData.empty())
				{
					std::cout << "Selected data from table '" << tableName << "':" << std::endl;
					for (const auto& row : selectedData)
					{
						for (const auto& value : row)
						{
							std::cout << value << "\t";
						}
						std::cout << std::endl;
					}
				}
				else
				{
					std::cout << "No data selected from table '" << tableName << "'." << std::endl;
				}
			}
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

// Function to parse the SQL statement and remove parentheses and semicolon
std::string parseSQLStatement(const std::vector<std::string>& tokens, size_t startIndex)
{
	if (startIndex >= tokens.size())
	{
		return "";  // Return an empty string if there are no tokens to parse
	}

	std::string sqlStatement = tokens[startIndex];

	for (size_t i = startIndex + 1; i < tokens.size(); ++i)
	{
		sqlStatement += " " + tokens[i];
	}

	// Remove parentheses and semicolon from the SQL statement
	sqlStatement = sqlStatement.substr(1, sqlStatement.length() - 2);

	return sqlStatement;
}

void printFormattedCommandList()
{
	std::array<std::string, 8> const cmds = {
		"help",
		"clear",
		"list",
		"create",
		"drop",
		"insert",
		"select",
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

void clearConsole()
{
	// Use system-specific command to clear the console
#ifdef _WIN32 // Windows
	std::system("cls");
#else // Assume Unix-like (Linux, macOS)
	std::system("clear");
#endif
}