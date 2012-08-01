#include "script.h"

int Script::FileOpenException = 0;
int Script::LOAD = 1;
int Script::CREATE = 2;

Script::Script( const QString& path, int iMode ) {
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

QString Script::getCode() const {
	return m_strCode;
}

QString Script::getPath() const {
	return m_strPath;
}

QString Script::getFileName() const {
	QFileInfo _fileInfo( m_strPath );
	return _fileInfo.fileName();
}