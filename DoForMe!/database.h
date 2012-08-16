#pragma once

#include <qstring.h>
#include <qmessagebox.h>
#include <qdatetime.h>
#include "sqlite3.h"
#include "action.h"
#include "scripts_manager.h"
#include "action_settings.h"

class Database {
private:
	const QString m_dbName;
	sqlite3* m_db;
	static QVector<QPair<QDate, Action*>> m_lastSelectedActions;

private:
	static int getRow( void *notUsed, int argc, char** argv , char** columnName );

public:
	Database( const QString& dbName, bool shouldOpen = true );
	~Database();

	void open();
	void prepareTableForActions();
	void clearContents();
	void insertAction( QDate date, Action* action );
	QVector<QPair<QDate, Action*>> selectActions();

};