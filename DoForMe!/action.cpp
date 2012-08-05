#include "action.h"

Action::Action( Script* pScript, QDate date, QTime time ) : m_pScript( pScript ), m_date( date ), m_time( time ) {}

void Action::setScript( Script* pScript ) {
	m_pScript = pScript;
}

Script* Action::getScript() const {
	return m_pScript;
}

void Action::setDate( QDate date ) {
	m_date = date;
}

QDate Action::getDate() const {
	return m_date;
}

void Action::setTime( QTime time ) {
	m_time = time;
}

QTime Action::getTime() const {
	return m_time;
}