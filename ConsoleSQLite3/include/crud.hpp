#pragma once

// C++ Standard Library
#include <iostream>
#include <string>
#include <vector>

// SQLite3 Library
#include <sqlite3.h>

/// <summary>
/// Opens an SQLite3 database connection.
/// </summary>
/// <param name="db">A pointer to the SQLite database</param>
/// <param name="databaseName">The name of the .sqlite file.</param>
sqlite3* openDb();

/// <summary>
/// Closes an SQLite3 database connection.
/// </summary>
/// <param name="db">A pointer to the SQLite database</param>
void closeDb(sqlite3* db);

/// <summary>
/// Creates a new table in the database.
/// </summary>
/// <param name="tableName">The name of the table to create</param>
/// <param name="columns">A string of the colum data for the table</param>
bool createNewTable(const std::string& tableName, const std::string& columns);

/// <summary>
/// Drops a table from the database.
/// </summary>
/// <param name="tableName">The name of the table to drop</param>
bool dropTable(const std::string& tableName);

/// <summary>
/// List all the current tables in the db.
/// </summary>
std::vector<std::string> listTables();

/// <summary>
///	Inserst data into a table.
/// </summary>
/// <param name="db">A pointer to the SQLite database</param>
/// <param name="tableName">The name of the table to modify</param>
///	<param name="colums">The colum to add the value to</param>
/// <param name="values">The value to add to the colum</param>
bool insertData(std::string tableName, std::string colums, std::string values);

/// <summary>
/// Select data from a table.
/// </summary>
/// <param name="db">A pointer to the SQLite database</param>
/// <param name="tableName">The name of the table to read</param>
std::vector<std::vector<std::string>> selectData(const std::string& tableName, const std::string& columns = "*");

/// <summary>
/// Delete data from a table.
/// </summary>
/// <param name="db">A pointer to the SQLite database</param>
/// <param name="tableName">The name of the table to modify</param>
bool deleteTableData(std::string tableName);

/// <summary>
/// Handles errors from the CRUD functions.
/// </summary>
/// <param name="db">A pointer to the SQLite database</param>
/// <param name="errorMsg">The error message to display</param>
void handleCRUDError(sqlite3* db, const std::string errorMsg);