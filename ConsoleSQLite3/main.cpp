#include "main.hpp"

int main()
{
	// Declare a pointer to the SQLite database
	sqlite3* db{};

	int result = openDb(db, "db.sqlite");

	if (result != SQLITE_OK) {
		std::cout << "Error Connecting to the Sqlite3 Database: " << sqlite3_errmsg(db) << std::endl;
		return 1;
	}
	else {
		runCLI(db);
	}

	closeDb(db);

	return 0;
}