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
int openDb(sqlite3* db, std::string databaseName);

/// <summary>
/// Closes an SQLite3 database connection.
/// </summary>
/// <param name="db">A pointer to the SQLite database</param>
void closeDb(sqlite3* db);

/// <summary>
/// Creates a new table in the database.
/// </summary>
/// <param name="db">A pointer to the SQLite database</param>
/// <param name="tableName">The name of the table to create</param>
/// <param name="columns">A string of the colum data for the table</param>
bool createNewTable(sqlite3* db, std::string tableName, std::string columns);

/// <summary>
/// Drops a table from the database.
/// </summary>
/// <param name="db">A pointer to the SQLite database</param>
/// <param name="tableName">The name of the table to drop</param>
bool dropTable(sqlite3* db, std::string tableName);

/// <summary>
/// List all the current tables in the db.
/// </summary>
void listTables(sqlite3* db);

/// <summary>
///	Inserst data into a table.
/// </summary>
/// <param name="db">A pointer to the SQLite database</param>
/// <param name="tableName">The name of the table to modify</param>
/// <param name="columns">The name of the colum to insert into</param>
/// <param name="values">The value to add to the colum</param>
bool insertData(sqlite3* db, std::string tableName, std::string columns, std::string values);

/// <summary>
/// Select data from a table.
/// </summary>
/// <param name="db">A pointer to the SQLite database</param>
/// <param name="tableName">The name of the table to read</param>
/// <param name="columns"></param>
void selectData(sqlite3* db, std::string tableName, std::string columns);

/// <summary>
///  Update data in a table.
/// </summary>
/// <param name="db"></param>
/// <param name="tableName">The name of the table to modify</param>
/// <param name="columns">The name of the colum to modify</param>
/// <param name="values">The value to update in the colum</param>
/// <param name="where">Filters for the colum</param>
void updateData(sqlite3* db, std::string tableName, std::string columns, std::string values, std::string where);

/// <summary>
/// Delete data from a table.
/// </summary>
/// <param name="db">A pointer to the SQLite database</param>
/// <param name="tableName">The name of the table to modify</param>
/// <param name="where">The filters for the delete</param>
void deleteData(sqlite3* db, std::string tableName, std::string where);