#include "crud.hpp"

int openDb(sqlite3* db, std::string databaseName)
{
	std::cout << "Running sqlite3 version: " << sqlite3_libversion() << std::endl;
	return sqlite3_open(databaseName.c_str(), &db);
}

void closeDb(sqlite3* db)
{
	sqlite3_close(db);
}

bool createNewTable(sqlite3* db, std::string tableName, std::string columns)
{
	// SQL statement to create the table
	std::string createTableSQL = "CREATE TABLE IF NOT EXISTS " + tableName + " (" + columns + ");";

	// Execute SQL statement
	char* errMsg = nullptr;

	// Execute the SQL statement to create the table
	int result = sqlite3_exec(db, createTableSQL.c_str(), nullptr, nullptr, &errMsg);

	if (result != SQLITE_OK)
	{
		std::cout << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
		return false;
	}
	else
	{
		std::cout << "Table created successfully or already exist in the database." << std::endl;
		return true;
	}
}

bool dropTable(sqlite3* db, std::string tableName)
{
	// SQL statement to drop the table
	std::string dropTableSQL = "DROP TABLE " + tableName + ";";

	// Execute SQL statement
	char* errMsg = nullptr;

	// Execute the SQL statement to drop the table
	int result = sqlite3_exec(db, dropTableSQL.c_str(), nullptr, nullptr, &errMsg);

	if (result != SQLITE_OK)
	{
		std::cout << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
		return false;
	}
	else
	{
		std::cout << "Table dropped successfully." << std::endl;
		return true;
	}
}

void listTables(sqlite3* db)
{
	std::vector<std::string> tableNames;
	sqlite3_stmt* stmt = nullptr;

	// SQL statement to query for table names in the database
	const char* sql = "SELECT name FROM sqlite_master WHERE type='table';";

	// Prepare the SQL statement
	int result = sqlite3_prepare(db, sql, -1, &stmt, nullptr);

	if (result != SQLITE_OK)
	{
		std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
		return;
	}

	// Execute the prepared statement and collect table names
	while ((result = sqlite3_step(stmt)) == SQLITE_ROW)
	{
		const unsigned char* tableName = sqlite3_column_text(stmt, 0);
		tableNames.push_back(reinterpret_cast<const char*>(tableName));
	}

	// Finalize the statement to release resources
	sqlite3_finalize(stmt);

	if (tableNames.empty())
	{
		std::cout << "No tables found in the database." << std::endl;
		return;
	}

	// Print the list of table names
	std::cout << "Tables in the database:" << std::endl;
	for (size_t i = 0; i < tableNames.size(); ++i)
	{
		std::cout << tableNames[i];

		// Add a comma and space if it's not the last table name
		if (i < tableNames.size() - 1) {
			std::cout << ", ";
		}
	}

	std::cout << std::endl;
}


bool insertData(sqlite3* db, std::string tableName, std::string columns, std::string values)
{
	// SQL statement to insert data into the table
	std::string insertSQL = "INSERT INTO " + tableName + " VALUES (" + values + ");";

	char* errMsg = nullptr;

	// Execute the SQL statement to insert data into the table
	int result = sqlite3_exec(db, insertSQL.c_str(), nullptr, nullptr, &errMsg);

	if (result != SQLITE_OK)
	{
		std::cerr << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg); // Free error message
		return false; // Data insertion failed
	}
	else
	{
		std::cout << "Records created successfully." << std::endl;
		return true; // Data insertion succeeded
	}
};

void selectData(sqlite3* db, std::string tableName, std::string columns)
{
	// SQL statement to select data from the table
	std::string selectSQL = "SELECT " + columns + " FROM " + tableName + ";";

	// Prepare the SQL statement and get a pointer to the compiled statement
	sqlite3_stmt* stmt = nullptr;

	// Prepare the SQL statement
	int result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);

	if (result != SQLITE_OK)
	{
		std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
		return;
	}

	// Execute the prepared statement
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		// Fetch and print data from the selected columns
		std::cout << "Data: ";
		for (int i = 0; i < sqlite3_column_count(stmt); i++) {
			const char* value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}

	// Finalize the statement to release resources
	sqlite3_finalize(stmt);
};

void updateData(sqlite3* db, std::string tableName, std::string columns, std::string values, std::string where)
{
	// SQL statement to update data in the table
	std::string updateSQL = "UPDATE " + tableName + " SET " + columns + " = " + values + " WHERE " + where + ";";

	char* errMsg = nullptr;

	// Execute the SQL statement to update data in the table
	int result = sqlite3_exec(db, updateSQL.c_str(), nullptr, nullptr, &errMsg);

	if (result != SQLITE_OK)
	{
		std::cerr << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg); // Free error message
		return;
	}

	std::cout << "Data updated successfully!" << std::endl;
};

void deleteData(sqlite3* db, std::string tableName, std::string where)
{
	// SQL statement to delete data from the table
	std::string deleteSQL = "DELETE FROM " + tableName + " WHERE " + where + ";";

	char* errMsg = nullptr;

	// Execute the SQL statement to delete data from the table
	int result = sqlite3_exec(db, deleteSQL.c_str(), nullptr, nullptr, &errMsg);

	if (result != SQLITE_OK)
	{
		std::cerr << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg); // Free error message
		return;
	}

	std::cout << "Data deleted successfully!" << std::endl;
}