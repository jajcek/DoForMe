#include "action.h"

Action::Action( Script* pScript, const ActionSettings& settings ) : m_pScript( pScript ) {
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

int Action::getHours() const {
	return m_time.hour();
}

int Action::getMinutes() const {
	return m_time.minute();
}

int Action::getSeconds() const {
	return m_time.second();
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