#include "scripts_manager.h"


QMap<QString, Script*> ScriptsManager::m_scripts;

void ScriptsManager::removeScript( QString name ) {
	delete m_scripts.find( name ).value();
	m_scripts.remove( name );
}

void ScriptsManager::removeScripts() {
	// cleaning up memory
	QMapIterator<QString, Script*> it( m_scripts );
	while( it.hasNext() ) {
		delete it.next().value();
	}
}

bool ScriptsManager::addScript( Script* script ) {
	QString _scriptName = script->getFileName();

	if( !m_scripts.contains( _scriptName ) ) {
		m_scripts[_scriptName] = script;

		return true;
	}
	
	return false;
}

bool ScriptsManager::saveToFile( const QString& scriptName ) {
	QMap<QString, Script*>::Iterator _pScriptIterator = m_scripts.find( scriptName );

	// script with the given title doesn't exists
	if( _pScriptIterator == m_scripts.end() )
		return false;

	Script* _pScript = _pScriptIterator.value();

	QFile _file( _pScript->getPath() );
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
		return false;
	}
	
	// write the code to the file
	QString _toWrite = _pScript->getCode();
	_file.write( _toWrite.toStdString().c_str() );
 
    // optional, as QFile destructor will already do it
    _file.close(); 

	return true;
}

Script* ScriptsManager::getScript( const QString& scriptName ) {
	auto _pScript = m_scripts.find( scriptName );

	if( _pScript != m_scripts.end() )
		return _pScript.value();
	else
		return NULL;
}

QStringList ScriptsManager::getScriptsList() {
	QStringList _scripts;

	QMapIterator<QString, Script*> _scriptsIt( m_scripts );

	while( _scriptsIt.hasNext() ) {
		_scriptsIt.next();
		_scripts.push_back( _scriptsIt.key() );
	}

	return _scripts;
}