#include "database.h"

QVector<QPair<QDate, Action*>> Database::m_lastSelectedActions;

int Database::getRow( void *notUsed, int argc, char** argv , char** columnName ) {
	// get all values from row
	// script name
	QString _scriptName = argv[1];
	// date
	int _year  = QString( argv[2] ).left( 4 ).toInt();
	int _month = QString( argv[2] ).mid( 5, 2 ).toInt();
	int _day   = QString( argv[2] ).right( 2 ).toInt();
	// excluded dates
	QVector<QDate> _excludedDate;
	QStringList _excludedDates = QString( argv[3] ).split( "|" );
	for( int i = 0; i < _excludedDates.size(); ++i ) {
		int _yearExcl  = _excludedDates.at( i ).left( 4 ).toInt();
		int _monthExcl = _excludedDates.at( i ).mid( 5, 2 ).toInt();
		int _dayExcl   = _excludedDates.at( i ).right( 2 ).toInt();
		_excludedDate.push_back( QDate( _yearExcl, _monthExcl, _dayExcl ) );
	}
	// time
	int _hours   = QString( argv[4] ).left( 2 ).toInt();
	int _minutes = QString( argv[4] ).mid( 3, 2 ).toInt();
	int _seconds = QString( argv[4] ).right( 2 ).toInt();
	// xdays
	int _xdays = QString( argv[5] ).toInt();
	// days
	int _days = QString( argv[6] ).toInt();

	ActionSettings _settings;
	_settings.setHours( _hours );
	_settings.setMinutes( _minutes );
	_settings.setSeconds( _seconds );
	_settings.setIsXDays( _xdays == 0 ? false : true );
	_settings.setXDays( _xdays );
	_settings.setDaysFlags( _days );

	Action* _pNewAction = new Action( ScriptsManager::getScript( _scriptName ), _settings );
	_pNewAction->setExcludedDates( _excludedDate );
	m_lastSelectedActions.push_back( qMakePair( QDate( _year, _month, _day ), _pNewAction ) );

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
																	 excludedDates TEXT,       \
																	 time TEXT,                \
																	 xdays INTEGER,            \
																	 days INTEGER );", NULL, NULL, &_errMsg );
	if( _res != SQLITE_OK ) {
		QMessageBox _msg( QMessageBox::Critical, "Error", "SQL error: " + QString( _errMsg ),
				QMessageBox::Ok );
		_msg.exec();
		sqlite3_free( _errMsg );
	}

	clearContents();
}

void Database::clearContents() {
	char* _errMsg = NULL;

	// truncate table (in sqlite there's no TRUNCATE keyword)
	int _res = sqlite3_exec( m_db, "DELETE FROM Actions;", NULL, NULL, &_errMsg );
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
	
	QString _excludedDates = "";
	int _excludedDatesNumber = action->getExcludedDates().size();
	for( int i = 0; i < _excludedDatesNumber; ++i ) {
		QDate _date = action->getExcludedDates().at( i );
		QString _strYear    = QString::number( _date.year() );
		QString _strMonthMM = _date.month() < 10 ? "0" + QString::number( _date.month() ) : QString::number( _date.month() );
		QString _strDayDD   = _date.day() < 10 ? "0" + QString::number( _date.day() ) : QString::number( _date.day() );
		_excludedDates += ( _excludedDates.isEmpty() ? "" : "|" ) + _strYear + "-" + _strMonthMM + "-" + _strDayDD;
	}

	QString _query = QString( "INSERT INTO Actions VALUES( " ) +
					"NULL, " +
					"'" + action->getScript()->getFileName() + "', " +
					"'" + QString::number( date.year() ) + "-" + _strMonthMM + "-" + _strDayDD + "', " +
					"'" + _excludedDates + "', " +
					"'" + action->getHoursHH() + ":" + action->getMinutesMM() + ":" + action->getSecondsSS() + "', " +
					_XDays + ", " +
					QString::number( action->getDays()  ) + " );";

	qDebug( "query: %s", _query.toStdString().c_str() );
	int _res = sqlite3_exec( m_db, _query.toStdString().c_str(), NULL, NULL, &_errMsg );
	if( _res != SQLITE_OK ) {
		QMessageBox _msg( QMessageBox::Critical, "Error", "SQL error: " + QString( _errMsg ),
				QMessageBox::Ok );
		_msg.exec();
		sqlite3_free( _errMsg );
	}
}

QVector<QPair<QDate, Action*>>  Database::selectActions() {
	char* _errMsg = NULL;

	// free memory from last selected actions
	int _actionsNumber = m_lastSelectedActions.size();
	for( int i = 0; i < _actionsNumber; ++i ) {
		//delete m_lastSelectedActions.at( i );
	}
	m_lastSelectedActions.clear();
	
	// select new actions
	sqlite3_exec( m_db, "SELECT * FROM Actions;", getRow, NULL, &_errMsg );

	// on _errMsg above there is used malloc() so we need to free the memory
	sqlite3_free( _errMsg );

	return m_lastSelectedActions;
}