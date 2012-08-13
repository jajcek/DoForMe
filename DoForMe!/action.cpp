#include "action.h"

int Action::m_actionNumber = 0;

Action::Action( Action* action ) {
	// IMPORTANT, it creates action without repetitions!
	m_pScript = action->getScript();
	m_time = action->getTime();
	m_isXDays = false;
	m_XDays = 0;
	m_days = 0;
	m_isHighlighted = action->isHighlighted();
	m_id = nextId();
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

int Action::getHours() const {
	return m_time.hour();
}

int Action::getMinutes() const {
	return m_time.minute();
}

int Action::getSeconds() const {
	return m_time.second();
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