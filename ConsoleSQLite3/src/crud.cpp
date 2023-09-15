#include "../include/crud.hpp"

sqlite3* openDb()
{
	sqlite3* db;

	int rc = sqlite3_open("db.sqlite", &db);

	if (rc)
	{
		handleCRUDError(db, "Error opening SQLite3 database: " + std::string(sqlite3_errmsg(db)));
		exit(1);
	}

	return db;
}

void closeDb(sqlite3* db)
{
	if (db)
	{
		sqlite3_close(db);
	}
}

// Function to create a new table
bool createNewTable(const std::string& tableName, const std::string& columns) {
	sqlite3* db = openDb();

	std::string createTableSQL = "CREATE TABLE IF NOT EXISTS " + tableName + " (" + columns + ");";

	int rc = sqlite3_exec(db, createTableSQL.c_str(), 0, 0, 0);

	if (rc != SQLITE_OK)
	{
		handleCRUDError(db, "Error creating table: " + std::string(sqlite3_errmsg(db)));
		return false;
	}

	closeDb(db);

	return true;
}

bool dropTable(const std::string& tableName)
{
	sqlite3* db = openDb();

	std::string dropTableSQL = "DROP TABLE IF EXISTS " + tableName + ";";

	int rc = sqlite3_exec(db, dropTableSQL.c_str(), 0, 0, 0);

	if (rc != SQLITE_OK)
	{
		handleCRUDError(db, "Error dropping table: " + std::string(sqlite3_errmsg(db)));
		return false;
	}

	closeDb(db);

	return rc == SQLITE_OK;
}


std::vector<std::string> listTables()
{
	sqlite3* db = openDb();

	std::string sql = "SELECT name FROM sqlite_master WHERE type='table';";

	sqlite3_stmt* stmt;

	int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

	if (rc != SQLITE_OK)
	{
		handleCRUDError(db, "Error listing tables: " + std::string(sqlite3_errmsg(db)));
		return std::vector<std::string>();
	}

	std::vector<std::string> tables;

	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
	{
		tables.push_back(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0))));
	}

	sqlite3_finalize(stmt);

	closeDb(db);

	return tables;
}

bool insertData(std::string tableName, std::string colums, std::string values)
{
	sqlite3* db = openDb();

	// todo - uncomment this when parsing for colums and values is implemented
	//std::string sql = "INSERT INTO " + tableName + " (" + colums + ") VALUES (" + values + ");";

	std::string sql = "INSERT INTO people (name, age) VALUES ('bob', 25)";

	int rc = sqlite3_exec(db, sql.c_str(), 0, 0, 0);

	if (rc != SQLITE_OK)
	{
		handleCRUDError(db, "Error inserting data: " + std::string(sqlite3_errmsg(db)));
		return false;
	}

	closeDb(db);

	return true;
}


std::vector<std::vector<std::string>> selectData(const std::string& tableName, const std::string& columns)
{
	sqlite3* db = openDb();
	std::string sql = "SELECT " + columns + " FROM " + tableName + ";";

	// Initialize the results vector
	std::vector<std::vector<std::string>> results;

	int rc = sqlite3_exec(db, sql.c_str(), [](void* data, int argc, char** argv, char** colNames) -> int {
		// Callback function to collect query results into the 'results' vector
		std::vector<std::string> row;
		for (int i = 0; i < argc; ++i) {
			if (argv[i]) {
				row.push_back(argv[i]);
			}
			else {
				row.push_back("NULL");
			}
		}
		static_cast<std::vector<std::vector<std::string>>*>(data)->push_back(row);
		return 0;
	}, &results, nullptr);

	if (rc != SQLITE_OK)
	{
		handleCRUDError(db, "Error selecting data: " + std::string(sqlite3_errmsg(db)));
	}

	closeDb(db);

	return results;
}

bool deleteTableData(std::string tableName)
{
	sqlite3* db = openDb();

	std::string sql = "DELETE FROM " + tableName + ";";

	int rc = sqlite3_exec(db, sql.c_str(), 0, 0, 0);

	if (rc != SQLITE_OK)
	{
		handleCRUDError(db, "Error deleting data: " + std::string(sqlite3_errmsg(db)));
		return false;
	}

	closeDb(db);

	return true;
};

// Function to emit an error message and close the database
void handleCRUDError(sqlite3* db, const std::string errorMsg) {
	std::cerr << "Error: " << errorMsg << std::endl;
	if (db)
	{
		sqlite3_close(db);
	}
}