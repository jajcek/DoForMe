#pragma once

#include <qstring.h>
#include <qmessagebox.h>
#include <qdatetime.h>
#include "sqlite3.h"
#include "action.h"
#include "scripts_manager.h"
#include "action_settings.h"
#include "player_settings.h"
#include "recorder_settings.h"
#include "reminder_settings.h"

/**
	\class Database database.h "database.h"
	\brief Allows saving and loading actions to/from database.
	\author Jacek Topolski
	\version 1.0
	\date 28.07.2012
*/
class Database {
private:
	/**
		\brief Name of the database;
	*/
	const QString m_dbName;
	/**
		\brief Pointer to the sqlite engine.
	*/
	sqlite3* m_db;
	/**
		\brief Vector of the last selected actions.
	*/
	static QVector<QPair<QDate, Action*>> m_lastSelectedActions;

private:
	/**
		\brief Helper function used as callback in sqlite method for getting rows.
		\param[in] notUsed Reserved for SQLite.
		\param[in] argc Number of rows returned.
		\param[in] argv Array of returned elements.
		\param[in] columnName Name of the column.
		\return Error code. 0 means success.
	*/
	static int getRow( void *notUsed, int argc, char** argv , char** columnName );

public:
	/**
		\brief Creates new database with the given name.
		\param[in] dbName Name of the database.
		\param[in] shouldOpen Determines if the database should be opened (allowing operations) after creation.
	*/
	Database( const QString& dbName, bool shouldOpen = true );
	/**
		\brief Closes the database.
	*/
	~Database();
	/**
		\brief Opens the database.
	*/
	void open();
	/**
		\brief Creates table for actions.
	*/
	void prepareTableForActions();
	/**
		\brief Creates table for settings.
	*/
	void prepareTableForSettings();
	/**
		\brief Clears all of the rows in the actions table (truncates table).
	*/
	void clearActions();
	/**
		\brief Clears all of the rows in the settings table (truncates table).
	*/
	void clearSettings();
	/**
		\brief Inserts action into the database.
		\param[in] date Date for the action.
		\param[in] action Action to be put into the database.
	*/
	void insertAction( QDate date, Action* action );
	/**
		\brief Inserts setting into the database.
		\param[in] key Key needed to be saved.
		\param[in] value Value of the key.
	*/
	void insertSetting( QString key, QString value );
	/**
		\return Vector of pairs in which the first element is the date on which the action exists and the second element is the action itself.
	*/
	QVector<QPair<QDate, Action*>> selectActions();

};