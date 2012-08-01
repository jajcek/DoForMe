#include "script.h"

int Script::FileOpenException = 0;
int Script::InvalidFileException = 1;

Script::Script( const QString& path ) {
	QFile _file( path );

	// open file in read mode (and text mode) 
    int _fileOpened = _file.open( QIODevice::ReadOnly | QIODevice::Text );
	if( !_fileOpened ) {
		throw FileOpenException;
	}

	// remove --[[ at beginning, if the --[[ doesn't exists return failure (wrong file structure)
	if( _file.readLine() != "--[[\n" ) {
		throw InvalidFileException;
	}

	// get all information about the script
	m_strTitle = getTitleFromFile( _file );
	// it is needed to have non-empty title (because we have to add it to the scripts list)
	if( m_strTitle == "" )
		throw InvalidFileException;
	m_strDescription = getDescriptionFromFile( _file );
	m_strCode = getCodeFromFile( _file );
	m_strPath = path;
}

Script::Script( const QString& title, const QString& path, const QString& description, const QString& code ) :
		m_strTitle( title ), m_strDescription( description ), m_strCode( code ), m_strPath( path ) {}

void Script::execute() {

}

QString Script::getTitleFromFile( QFile& file ) {
	QString _title;

	// get title
	_title += file.readLine();
	// remove new line symbol at the end
	_title.replace( "\n", "" );

	// if it occurs it means the the --[[ --]] is empty and we need title to add script
	if( _title == "--]]" )
		throw InvalidFileException;

	return _title;
}

QString Script::getDescriptionFromFile( QFile& file ) {
	QString _description;

	// get description
	QString _line;
	while( ( ( _line = file.readLine() ) != "--]]\n" ) && !file.atEnd() )
		_description += _line;

	// remove new line symbol at the end (we cannot use replace method,
	// because the text is taken from text box where user is allowed to
	// write new line symbols and it wil remove all the symbols)
	_description = _description.left( _description.size() - 1 );

	return _description;
}

QString Script::getCodeFromFile( QFile& file ) {
	QString _code;

	// get code (rest of the file)
	while( !file.atEnd() ) {
		_code = file.readLine();
	}

	return _code;
}

void Script::setTitle( QString title ) {
	m_strTitle = title;
}

QString Script::getTitle() const {
	return m_strTitle;
}

void Script::setDescription( QString description ) {
	m_strDescription = description;
}

QString Script::getDescription() const {
	return m_strDescription;
}

void Script::setCode( QString code ) {
	m_strCode = code;
}

QString Script::getCode() const {
	return m_strCode;
}

void Script::setPath( QString path ) {
	m_strPath = path;
}

QString Script::getPath() const {
	return m_strPath;
}