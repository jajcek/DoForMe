#include "scripts_manager.h"


QMap<QString, Script*> ScriptsManager::m_scripts;

void ScriptsManager::removeScripts() {
	// cleaning up memory
	QMapIterator<QString, Script*> it( m_scripts );
	while( it.hasNext() ) {
		delete it.next().value();
	}
}

bool ScriptsManager::attemptToAddScript( Script* script ) {
	QString _scriptTitle = script->getTitle();

	if( m_scripts.find( _scriptTitle ) == m_scripts.end() ) {
		m_scripts[_scriptTitle] = script;

		return true;
	}
	
	return false;
}

bool ScriptsManager::addScript( Script* script, bool showInput ) {
	if( showInput ) {
		bool _ok = true;
		// try to add new script
		while( !ScriptsManager::attemptToAddScript( script ) && _ok ) {
			// script with the given title alread exists, show input dialog to rename it
			QString _strNewTitle = QInputDialog::getText( NULL, "Script title",
					"Script with the title \"" + script->getTitle() + "\" from \"" + script->getPath() + "\" already exists, change the title:",
					QLineEdit::Normal, "", &_ok );

			// if user accepted, set new title
			if( _ok && !_strNewTitle.isEmpty() ) {
				script->setTitle( _strNewTitle );
			}
		}

		// the user pressed cancel, show info that the script wasn't loaded
		if( !_ok ) {
			QMessageBox _msg( QMessageBox::Critical, "Error",
				"Script with the \"" + script->getTitle() + "\" title already exists. The script from \"" + script->getPath() + "\" wasn't loaded.",
							QMessageBox::Ok );
			_msg.exec();
		} else {
			return true;
		}
		return false;
	} else {
		return attemptToAddScript( script );
	}
}

void ScriptsManager::saveToFile( const QString& title ) {
	Script* _pScript = m_scripts.find( title ).value();
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
	}
	
	// write the code to the file
	QString toWrite;
	if( _pScript->getDescription() == "" )
		toWrite = "--[[\n" + _pScript->getTitle() + "\n--]]\n" + _pScript->getCode();
	else
		toWrite = "--[[\n" + _pScript->getTitle() + "\n" + _pScript->getDescription() + "\n--]]\n" + _pScript->getCode();
	_file.write( toWrite.toStdString().c_str() );
 
    // optional, as QFile destructor will already do it
    _file.close(); 
}

Script* ScriptsManager::getScript( const QString scriptTitle ) {
	return m_scripts.find( scriptTitle ).value();
}