#include "action.h"

int Action::m_actionNumber = 0;

Action::Action( Action* pAction ) : m_pScript( pAction->getScript() ), m_time( pAction->getTime() ), m_isXDays( false ), m_XDays( 0 ),
									m_days( 0 ), m_isHighlighted( pAction->isHighlighted() ), m_id( nextId() ) {
	// IMPORTANT, it creates action without repetitions!
}

Action::Action( Script* pScript, const ActionSettings& settings ) : m_pScript( pScript ), m_isHighlighted( false ), m_id( nextId() ) {
	setSetting( settings );
}

void Action::setSetting( const ActionSettings& settings ) {
	m_time = QTime( settings.getHours(), settings.getMinutes(), settings.getSeconds() );
	m_isXDays = settings.isXDays();
	m_XDays = settings.getXDays();
	m_days = settings.getDays();
}

void Action::setScript( Script* pScript ) {
	m_pScript = pScript;
}

Script* Action::getScript() const {
	return m_pScript;
}

void Action::excludeDate( QDate date ) {
	m_excludedDates.push_back( date );
}

bool Action::isExcluded( QDate date ) const {
	return m_excludedDates.contains( date );
}

void Action::setExcludedDates( QVector<QDate> excludedDates ) {
	m_excludedDates = excludedDates;
}

QVector<QDate> Action::getExcludedDates() const {
	return m_excludedDates;
}

int Action::getHours() const {
	return m_time.hour();
}

int Action::getMinutes() const {
	return m_time.minute();
}

int Action::getSeconds() const {
	return m_time.second();
}

QString Action::getHoursHH() const {
	int _hour = m_time.hour();
	QString _strHour = QString::number( _hour );

	if( _hour < 10 ) {
		_strHour = "0" + _strHour;
	}

	return _strHour;
}

QString Action::getMinutesMM() const {
	int _minute = m_time.minute();
	QString _strMinute = QString::number( _minute );

	if( _minute < 10 ) {
		_strMinute = "0" + _strMinute;
	}

	return _strMinute;
}

QString Action::getSecondsSS() const {
	int _second = m_time.second();
	QString _strSecond = QString::number( _second );

	if( _second < 10 ) {
		_strSecond = "0" + _strSecond;
	}

	return _strSecond;
}

QTime Action::getTime() const {
	return m_time;
}

bool Action::isXDays() const {
	return m_isXDays;
}

int Action::getXDays() const {
	return m_XDays;
}

int Action::getDays() const {
	return m_days;
}

void Action::setHighlight( bool state ) {
	m_isHighlighted = state;
}

bool Action::isHighlighted() const {
	return m_isHighlighted;
}

void Action::setId( int id ) {
	m_id = id;
}

int Action::getId() const {
	return m_id;
}

int Action::nextId() {
	return m_actionNumber++;
}