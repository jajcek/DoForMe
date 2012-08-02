#include "scripts_manager.h"


QMap<QString, Script*> ScriptsManager::m_scripts;

void ScriptsManager::removeScripts() {
	// cleaning up memory
	QMapIterator<QString, Script*> it( m_scripts );
	while( it.hasNext() ) {
		delete it.next().value();
	}
}

bool ScriptsManager::addScript( Script* script ) {
	QString _scriptName = script->getFileName();

	if( m_scripts.find( _scriptName ) == m_scripts.end() ) {
		m_scripts[_scriptName] = script;

		return true;
	}
	
	return false;
}

void ScriptsManager::saveToFile( const Script* pScript ) {
	QFile _file( pScript->getPath() );
	QDir _dir;

	// check if "scripts" folder exists
	int _dirExists = _dir.exists( "scripts" );
	// if not, create it
	if( !_dirExists )
		_dir.mkdir( "scripts" );

	// open file in write mode (and text mode) 
    int _fileOpened = _file.open( QIODevice::WriteOnly | QIODevice::Text );
	if( !_fileOpened ) {
		QMessageBox _msg( QMessageBox::Critical, "Error", "Unable to create file.",
						  QMessageBox::Ok );
		_msg.exec();
	}
	
	// write the code to the file
	QString _toWrite = pScript->getCode();
	_file.write( _toWrite.toStdString().c_str() );
 
    // optional, as QFile destructor will already do it
    _file.close(); 
}

Script* ScriptsManager::getScript( const QString scriptTitle ) {
	QMap<QString, Script*>::Iterator _pScript = m_scripts.find( scriptTitle );

	if( _pScript != m_scripts.end() )
		return _pScript.value();
	else
		return NULL;
}