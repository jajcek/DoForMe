#include "action.h"

Action::Action() : m_path( "" ), m_fileName( "" ), m_code( "" ), m_bModified( false ) {}

Action::~Action() {}

void Action::setPath( QString path ) {
	m_path = path;
}

QString Action::getPath() const {
	return m_path;
}

void Action::setFileName( QString fileName ) {
	m_fileName = fileName;
}

QString Action::getFileName() const {
	return m_fileName;
}

void Action::setCode( QString code ) {
	m_code = code;
}

QString Action::getCode() const {
	return m_code;
}

void Action::setTime( QTime time ) {
	m_time = time;
}

QTime Action::getTime() const {
	return m_time;
}

void Action::setModified( bool changed ) {
	m_bModified = changed;
}

bool Action::isModified() const {
	return m_bModified;
}