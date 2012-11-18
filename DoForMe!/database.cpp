#include "database.h"

QVector<QPair<QDate, Action*>> Database::m_lastSelectedActions;
QVector<QPair<int, QDate>> Database::m_lastSelectedExcludedDates;
QMap<QString, QString> Database::m_lastSelectedSettings;

int Database::getActionRow( void *notUsed, int argc, char** argv , char** columnName ) {
	// get all values from row
	int _id  = QString( argv[0] ).toInt();
	// script name
	QString _scriptName = argv[1];
	// date
	int _year  = QString( argv[2] ).left( 4 ).toInt();
	int _month = QString( argv[2] ).mid( 5, 2 ).toInt();
	int _day   = QString( argv[2] ).right( 2 ).toInt();
	// time
	int _hours   = QString( argv[3] ).left( 2 ).toInt();
	int _minutes = QString( argv[3] ).mid( 3, 2 ).toInt();
	int _seconds = QString( argv[3] ).right( 2 ).toInt();
	// xdays
	int _xdays = QString( argv[4] ).toInt();
	// days
	int _days = QString( argv[5] ).toInt();

	ActionSettings _settings;
	_settings.setHours( _hours );
	_settings.setMinutes( _minutes );
	_settings.setSeconds( _seconds );
	_settings.setIsXDays( _xdays == 0 ? false : true );
	_settings.setXDays( _xdays );
	_settings.setDaysFlags( _days );

	QVector<QDate> _excludedDates;
	// find appropriate ref ids and its excluded dates
	for( int i = 0; i < m_lastSelectedExcludedDates.size(); ++i ) {
		if( m_lastSelectedExcludedDates.at( i ).first == _id ) {
			_excludedDates.push_back( m_lastSelectedExcludedDates.at( i ).second );
		}
	}

	Action* _pNewAction = new Action( QDate( _year, _month, _day ), _settings );
	_pNewAction->setScript( ScriptsManager::getScript( _scriptName ) );
	_pNewAction->setExcludedDates( _excludedDates );
	m_lastSelectedActions.push_back( qMakePair( QDate( _year, _month, _day ), _pNewAction ) );

	return 0;
}

int Database::getExcludedDate( void *notUsed, int argc, char** argv , char** columnName ) {
	int _refId  = QString( argv[1] ).toInt();

	// date
	int _year  = QString( argv[2] ).left( 4 ).toInt();
	int _month = QString( argv[2] ).mid( 5, 2 ).toInt();
	int _day   = QString( argv[2] ).right( 2 ).toInt();

	m_lastSelectedExcludedDates.push_back( qMakePair( _refId, QDate( _year, _month, _day ) ) );

	return 0;
}

int Database::getSettingRow( void *notUsed, int argc, char** argv , char** columnName ) {
	// get all values from row
	QString _key = argv[1];
	QString _value = argv[2];

	m_lastSelectedSettings.insert( _key, _value );

	return 0;
}

Database::Database( const QString& dbName, bool shouldOpen ) : m_dbName( dbName ) {
	if( shouldOpen )
		open();
}

Database::~Database() {
	sqlite3_close( m_db );
}

void Database::open() {
	int _fail = sqlite3_open( m_dbName.toStdString().c_str(), &m_db );

	// if the function above failed, then _fail > 0
	if( _fail ) {
		QMessageBox _msg( QMessageBox::Critical, "Error", "Couldn't open database: " + QString( sqlite3_errmsg( m_db ) ),
				QMessageBox::Ok );
		_msg.exec();
		return;
	}
}

void Database::prepareTableForActions() {
	char* _errMsg = NULL;
	int _res = 0;
	_res = sqlite3_exec( m_db, "CREATE TABLE IF NOT EXISTS Actions ( id INTEGER PRIMARY KEY,   \
																	 scriptName TEXT NOT NULL, \
																	 date TEXT,                \
																	 time TEXT,                \
																	 xdays INTEGER,            \
																	 days TINYINT );", NULL, NULL, &_errMsg );
	if( _res != SQLITE_OK ) {
		QMessageBox _msg( QMessageBox::Critical, "Error", "SQL error: " + QString( _errMsg ),
				QMessageBox::Ok );
		_msg.exec();
		sqlite3_free( _errMsg );
	}

	_res = sqlite3_exec( m_db, "CREATE TABLE IF NOT EXISTS ExcludedDates ( id INTEGER PRIMARY KEY,   \
																	 refId INTEGER NOT NULL, \
																	 time TIME );", NULL, NULL, &_errMsg );
	if( _res != SQLITE_OK ) {
		QMessageBox _msg( QMessageBox::Critical, "Error", "SQL error: " + QString( _errMsg ),
				QMessageBox::Ok );
		_msg.exec();
		sqlite3_free( _errMsg );
	}

	clearActions();
}

void Database::prepareTableForSettings() {
	char* _errMsg = NULL;
	int _res = 0;
	_res = sqlite3_exec( m_db, "CREATE TABLE IF NOT EXISTS Settings ( id INTEGER PRIMARY KEY,   \
																	  key TEXT NOT NULL, \
																	  value TEXT NOT NULL );", NULL, NULL, &_errMsg );
	if( _res != SQLITE_OK ) {
		QMessageBox _msg( QMessageBox::Critical, "Error", "SQL error: " + QString( _errMsg ),
				QMessageBox::Ok );
		_msg.exec();
		sqlite3_free( _errMsg );
	}

	clearSettings();
}

void Database::clearActions() {
	char* _errMsg = NULL;

	// truncate table (in sqlite there's no TRUNCATE keyword)
	int _res = sqlite3_exec( m_db, "DELETE FROM Actions;", NULL, NULL, &_errMsg );
	if( _res != SQLITE_OK ) {
		QMessageBox _msg( QMessageBox::Critical, "Error", "SQL error: " + QString( _errMsg ),
				QMessageBox::Ok );
		_msg.exec();
		sqlite3_free( _errMsg );
	}

	// truncate table (in sqlite there's no TRUNCATE keyword)
	_res = sqlite3_exec( m_db, "DELETE FROM ExcludedDates;", NULL, NULL, &_errMsg );
	if( _res != SQLITE_OK ) {
		QMessageBox _msg( QMessageBox::Critical, "Error", "SQL error: " + QString( _errMsg ),
				QMessageBox::Ok );
		_msg.exec();
		sqlite3_free( _errMsg );
	}
}

void Database::clearSettings() {
	char* _errMsg = NULL;

	// truncate table (in sqlite there's no TRUNCATE keyword)
	int _res = sqlite3_exec( m_db, "DELETE FROM Settings;", NULL, NULL, &_errMsg );
	if( _res != SQLITE_OK ) {
		QMessageBox _msg( QMessageBox::Critical, "Error", "SQL error: " + QString( _errMsg ),
				QMessageBox::Ok );
		_msg.exec();
		sqlite3_free( _errMsg );
	}
}

void Database::insertAction( QDate date, Action* action ) {
	char* _errMsg = NULL;

	// make the month/day numbers as 2-digits
	QString _strMonth = QString::number( date.month() );
	QString _strMonthMM = _strMonth.length() == 1 ? "0" + _strMonth : _strMonth;
	QString _strDay = QString::number( date.day() );
	QString _strDayDD = _strDay.length() == 1 ? "0" + _strDay : _strDay;
	QString _XDays = action->isXDays() ? QString::number( action->getXDays() ) : QString::number( 0 );

	// prepare the query
	QString _query = QString( "INSERT INTO Actions VALUES( " ) +
					"NULL, " +
					"'" + action->getScript()->getFileName() + "', " +
					"'" + QString::number( date.year() ) + "-" + _strMonthMM + "-" + _strDayDD + "', " +
					"'" + action->getHoursHH() + ":" + action->getMinutesMM() + ":" + action->getSecondsSS() + "', " +
					_XDays + ", " +
					QString::number( action->getDays()  ) + " );";

	//qDebug( "query: %d", sqlite3_last_insert_rowid( m_db ) );
	int _res = sqlite3_exec( m_db, _query.toStdString().c_str(), NULL, NULL, &_errMsg );
	if( _res != SQLITE_OK ) {
		QMessageBox _msg( QMessageBox::Critical, "Error", "SQL error: " + QString( _errMsg ),
				QMessageBox::Ok );
		_msg.exec();
		sqlite3_free( _errMsg );
	}

	int _lastId = sqlite3_last_insert_rowid( m_db );

	// create string which will be put into database in form of "date|date|date|..."
	QString _excludedDates = "";
	int _excludedDatesNumber = action->getExcludedDates().size();
	for( int i = 0; i < _excludedDatesNumber; ++i ) {
		QDate _date = action->getExcludedDates().at( i );
		QString _Year    = QString::number( _date.year() );
		QString _MonthMM = _date.month() < 10 ? "0" + QString::number( _date.month() ) : QString::number( _date.month() );
		QString _DayDD   = _date.day() < 10 ? "0" + QString::number( _date.day() ) : QString::number( _date.day() );
		_excludedDates += _Year + "-" + _MonthMM + "-" + _DayDD;

		// prepare the query
		QString _queryED = QString( "INSERT INTO ExcludedDates VALUES( " ) +
						"NULL, " +
						QString::number( _lastId ) + ", " +
						"'" + _excludedDates + "' );";

		//qDebug( "query: %s", _queryED.toStdString().c_str() );
		int _res = sqlite3_exec( m_db, _queryED.toStdString().c_str(), NULL, NULL, &_errMsg );
		if( _res != SQLITE_OK ) {
			QMessageBox _msg( QMessageBox::Critical, "Error", "SQL error: " + QString( _errMsg ),
					QMessageBox::Ok );
			_msg.exec();
			sqlite3_free( _errMsg );
		}
	}
}

void Database::insertSetting( QString key, QString value ) {
	char* _errMsg = NULL;

	// prepare the query
	QString _query = QString( "INSERT INTO Settings VALUES( " ) +
					"NULL, " +
					"'" + key + "', " +
					"'" + value + "' );";

	//qDebug( "query: %s", _query.toStdString().c_str() );
	int _res = sqlite3_exec( m_db, _query.toStdString().c_str(), NULL, NULL, &_errMsg );
	if( _res != SQLITE_OK ) {
		QMessageBox _msg( QMessageBox::Critical, "Error", "SQL error: " + QString( _errMsg ),
				QMessageBox::Ok );
		_msg.exec();
		sqlite3_free( _errMsg );
	}
}

QVector<QPair<QDate, Action*>> Database::selectActions() {
	char* _errMsg = NULL;

	// free memory from last selected actions
	int _actionsNumber = m_lastSelectedActions.size();
	for( int i = 0; i < _actionsNumber; ++i ) {
		delete m_lastSelectedActions.at( i ).second;
	}
	m_lastSelectedActions.clear();
	m_lastSelectedExcludedDates.clear();
	
	sqlite3_exec( m_db, "SELECT * FROM ExcludedDates;", getExcludedDate, NULL, &_errMsg );

	// select new actions (if the table doesn't exists
	// the returned m_lastSelectedActions will be empty)
	sqlite3_exec( m_db, "SELECT * FROM Actions;", getActionRow, NULL, &_errMsg );

	return m_lastSelectedActions;
}

QMap<QString, QString> Database::selectSettings() {
	char* _errMsg = NULL;

	// clear content of the last selected settings
	m_lastSelectedSettings.clear();
	
	// select new actions (if the table doesn't exists
	// the returned m_lastSelectedSettings will be empty)
	sqlite3_exec( m_db, "SELECT * FROM Settings;", getSettingRow, NULL, &_errMsg );

	return m_lastSelectedSettings;
}