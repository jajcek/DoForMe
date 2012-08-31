#include "script.h"

const int Script::FileOpenException = 0;
const int Script::LOAD = 1;
const int Script::CREATE = 2;

Script::Script( const QString& path, int iMode ) : m_strCode( "" ), m_strPath( "" ), m_bModified( false ) {
	QFile _file( path );

	// open file in read mode (and text mode) 
    int _fileOpened = 0;
	if( iMode == LOAD )
		_fileOpened = _file.open( QIODevice::ReadOnly | QIODevice::Text );
	else
		_fileOpened = _file.open( QIODevice::WriteOnly | QIODevice::Text );

	if( !_fileOpened ) {
		throw FileOpenException;
	}

	// get all information about the script
	m_strCode = getCodeFromFile( _file );
	m_strPath = path;
}

QString Script::getCodeFromFile( QFile& file ) {
	QString _code;

	while( !file.atEnd() ) {
		_code += file.readLine();
	}

	return _code;
}

void Script::setCode( const QString& code ) {
	m_strCode = code;
}

QString Script::getCode() const {
	return m_strCode;
}

QString Script::getPath() const {
	return m_strPath;
}

QString Script::getFileName() const {
	QFileInfo _fileInfo( m_strPath );
	return _fileInfo.fileName().left( _fileInfo.fileName().length() - 4 );
}

void Script::setModified( bool isModified ) {
	m_bModified = isModified;
}

bool Script::isModified() const {
	return m_bModified;
}