#include "action.h"

Action::Action() : m_path( "" ), m_code( "" ) {}

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