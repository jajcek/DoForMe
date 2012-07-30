#include "script.h"

Script::Script( const QString& path ) {
	QFile _file( path );

	// open file in read mode (and text mode) 
    int _fileOpened = _file.open( QIODevice::ReadOnly | QIODevice::Text );
	if( !_fileOpened ) {
		QMessageBox _msg( QMessageBox::Critical, "Error", "Unable to open file: " + path,
						  QMessageBox::Ok );
		_msg.exec();
	}

	// remove --[[ at beginning
	_file.readLine();

	// get all information about the script
	m_strTitle = getTitleFromFile( _file );
	m_strDescription = getDescriptionFromFile( _file );
	m_strCode = getCodeFromFile( _file );
}

QString Script::getTitleFromFile( QFile& file ) {
	QString _title;

	// get title
	_title += file.readLine();
	// remove new line symbol at the end
	_title.replace( "\n", "" );

	return _title;
}

QString Script::getDescriptionFromFile( QFile& file ) {
	QString _description;

	// get description
	QString _line;
	while( ( _line = file.readLine() ) != "--]]\n" )
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

QString Script::getTitle() const {
	return m_strTitle;
}

QString Script::getDescription() const {
	return m_strDescription;
}

QString Script::getCode() const {
	return m_strCode;
}

QString Script::getPath() const {
	return m_strPath;
}