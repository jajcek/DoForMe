#include <Windows.h>
#include "mainwin.h"

HHOOK hook;


LRESULT CALLBACK mouseHook(int code, WPARAM wParam, LPARAM lParam)
{
     if(code < 0) return CallNextHookEx(hook, code, wParam, lParam);   
 
     if(wParam == WM_LBUTTONDOWN) {
		qDebug( "\nklik!" );
	 }
 
     return CallNextHookEx (0, code, wParam, lParam);
}

QString mainWin::APP_NAME = "DoForMe!";

mainWin::mainWin(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags), m_iWidth( 821 ), m_iHeight( 507 ), m_calendar( NULL ), m_lua( NULL ), m_currAction( NULL )
{
	ui.setupUi(this);

	QObject::connect( ui.actionAbout, SIGNAL( activated() ), this, SLOT( showAbout() ) );
	QObject::connect( ui.actionNew, SIGNAL( activated() ), this, SLOT( newFile() ) );
	QObject::connect( ui.actionRun, SIGNAL( activated() ), this, SLOT( runAction() ) );
	QObject::connect( ui.actionSave_action, SIGNAL( activated() ), this, SLOT( saveAction() ) );
	QObject::connect( ui.actionSave_action_as, SIGNAL( activated() ), this, SLOT( saveAsAction() ) );
	//QObject::connect( ui.addActionButton, SIGNAL( clicked() ), this, SLOT( addAction() ) );
	QObject::connect( ui.scriptTextEdit, SIGNAL( textChanged() ), this, SLOT( scriptModified() ) );
	
	// used for centering main app window
	QDesktopWidget screen;
	setGeometry( ( screen.width() - m_iWidth ) / 2, ( screen.height() - m_iHeight ) / 2, m_iWidth, m_iHeight );

	DetailedCalendar::setList( ui.actionsList );
	m_calendar = new DetailedCalendar( this );
	m_calendar->setGeometry( ui.actionsList->width() + 10, m_iHeight - 210, m_iWidth - ( ui.actionsList->width() + 10 ), 210 );
	m_calendar->show();
	
	m_lua = new LuaEngine();
	LuaApiEngine::setLuaEngine( m_lua );
	LuaApiEngine::initSpecialKeys();

	loadScripts( NewFile::DIR );

	// register functions used in lua's scripts for m_lua.
	initLuaApi();
	
	//hook = SetWindowsHookEx( WH_MOUSE_LL, &mouseHook, GetModuleHandle( NULL ), 0 );
}

void mainWin::loadScripts( const QString& path ) {
	QDir myDir( path );

	// define which extensions we want to look for
	QStringList _filesExt;
	_filesExt.push_back( "*.apc" );

	// get list of files
	QStringList _fileList = myDir.entryList( _filesExt );
	
	// iterate through all files and add them into map
	while( !_fileList.empty() ) {
		QString _fileName = _fileList.back();
		_fileList.pop_back();

		// create script object from the file
		try {
			Script* _pScript = new Script( path + _fileName );
			if( ScriptsManager::addScript( _pScript, true ) ) {
				// add script title to the scripts list
				ui.scriptsList->addItem( _pScript->getTitle() );
			}
		} catch( int e ) {
			if( e == Script::FileOpenException ) {
				QMessageBox _msg( QMessageBox::Critical, "Error", "Unable to open file \"" + path + _fileName + "\"", QMessageBox::Ok );
				_msg.exec();
			} else if( e == Script::InvalidFileException ) {
				QMessageBox _msg( QMessageBox::Critical, "Error", "Structure of the file \"" + path + _fileName + "\" is broken. Did you edit scripts manually?", QMessageBox::Ok );
				_msg.exec();
			}
		}
	}
}

void mainWin::newFile() {
	NewFile _newScript;
	
	// get value indicating which button has been pressed
	int _iResult = _newScript.exec();
	if( _iResult == QDialog::Accepted ) {
		// get all needed data about the newly created script
		QString _strTitle = _newScript.getTitle();
		QString _strFileName = _newScript.getFileName();
		QString _strDescription = _newScript.getDescription();

		// add title and description to the code as comments in lua
		ui.scriptTitle->setText( "  " + _strTitle );
		//setCode( "--[[\n" + _strTitle + "\n" + _strDescription + "\n--]]\n" );

		// add the script to the scripts list
		ui.scriptsList->addItem( _strTitle );

		ScriptsManager::addScript( new Script( _strTitle, NewFile::DIR + _strFileName, _strDescription ) );
		ScriptsManager::saveToFile( _strTitle );
	}
}

void mainWin::runAction() {
	// load and parse script (from text field, the bigger one) by checking its correctness
	switch( m_lua->loadScript( ui.scriptTextEdit->toPlainText().toStdString().c_str(), LuaEngine::BUFFER ) ) {
		case LUA_ERRSYNTAX: {
			QMessageBox _msg( QMessageBox::Critical, "Error", "Syntax error in the script." );
			_msg.exec();
			break;
		}
		case LUA_ERRMEM: {
			QMessageBox _msg( QMessageBox::Critical, "Error", "Memory allocation error." );
			_msg.exec();
			break;
		}
		case 0: { // everything went ok
			// parse script and put api functions onto its lua's engine stack
			switch( m_lua->parseScript() ) {
				case LUA_ERRRUN: {
					// get text error returned by lua_pcall function (from lua's library)
					QString _error = m_lua->getTextError();

					// get function name that occured the error
					QString _funcName = getFuncName( _error );

					// and show the info about it
					QMessageBox _msg( QMessageBox::Critical, "Error", "The function '" + _funcName + "' doesn't exists in the API." );
					_msg.exec();
					break;
				}
				case LUA_ERRMEM: {
					QMessageBox _msg( QMessageBox::Critical, "Error", "Memory error." );
					_msg.exec();
					break;
				}
				// not needed, we don't use 'error handling function' utility from lua's library
				/*case LUA_ERRERR: {
					QMessageBox _msg( QMessageBox::Critical, "Error", "Error while handling 'error function'." );
					_msg.exec();
					break;
				}*/
				case 0: // everything went ok
					break;
			}
		}
	}

	// start script (by taking commands from the lua's stack one by one)
	// the stack is in the m_lua object's class (LuaEngine)
	m_lua->start();
}

void mainWin::saveAction() {
	// get path to the current action (script) file (we need it to prepare saving)
	QString _path = m_currAction->getPath();

	// if it has no path (= "") to file, it means it is not saved yet
	// so we have to show save dialog to the user (it is done in saveAsAction())
	if( _path == "" ) {
		saveAsAction();
	} else {
		// get current code from the text box
		QString _strCode = ui.scriptTextEdit->toPlainText();

		// the script exists as a file, we need to update it
		// update code for current action
		m_currAction->setCode( _strCode );

		// save also to file
		//saveToFile( _path, _strCode );

		// set window title without '*' symbol, because it's been saved
		setWindowTitle( APP_NAME + " - " + m_currAction->getFileName() );

		// we saved the script so we make the status changed to false
		m_currAction->setModified( false );
	}
}

void mainWin::saveAsAction() {
	// get full path of a file which we will be saving to
	QString _fullPath = QFileDialog::getSaveFileName( this, "Save script...", "", "Scripts (*.apc);;All files (*.*)" );

	// if a user didn't click 'cancel', otherwise _fullPath is equal to ""
	if( _fullPath != "" ) {
		// set the path in the edit (next to browse button)
		//ui.scriptPathEdit->setText( _fullPath );

		// set the path and code in the currently selected action object
		m_currAction->setPath( _fullPath );

		// we set path already, so we can execute save action (instead of save as...)
		saveAction();
	}
}

void mainWin::addAction() {
	bool _bShouldAdd = true;
	qDebug( "%d", m_currAction );
	if( !m_currAction ) {
		QMessageBox _msg( QMessageBox::Information, "Information", "You have to save the script before adding it.",
						  QMessageBox::Ok | QMessageBox::Cancel );
		_msg.exec();
		// which button of the message box has been clicked
		switch( 0 ) {
			case QMessageBox::Ok:
				saveAsAction();
				break;
			case QMessageBox::Cancel:
				_bShouldAdd = false;
		}
	} else if( m_currAction->isModified() ) {
		QMessageBox _msg( QMessageBox::Information, "Information", "The script has been modified. If you choose 'Don't save' the old script will be loaded and you will loose the current script.",
						  QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel );

		// which button of the message box has been clicked
		switch( _msg.exec() ) {
			case QMessageBox::Save:
				saveAction();
				break;
			case QMessageBox::Discard:
				// set previously saved code to the text box
				ui.scriptTextEdit->setText( m_currAction->getCode() );

				// set window title without '*' symbol, because it's been saved
				setWindowTitle( APP_NAME + " - " + m_currAction->getFileName() );

				// we saved the script so we make the status changed to false
				m_currAction->setModified( false );

				break;
			case QMessageBox::Cancel:
				_bShouldAdd = false;
		}
	}

	if( _bShouldAdd ) {
		if( m_currAction->getPath() != "" ) {
			m_calendar->addAction( m_calendar->getSelectedDate(),  m_currAction );

			// gather all information for the action from every field
			getDataForAction();

			// create tiem string to for action list
			QString _hour = QString::number( ui.hourSpin->value() );
			QString _min  = QString::number( ui.minSpin->value() );
			QString _sec  = QString::number( ui.secSpin->value() );

			QString _strTime = _hour + ":" + _min + ":" + _sec;

			// add action to the actions' list (because the list updates only when clicking on calendar)
			ui.actionsList->addItem( _strTime + " " + m_currAction->getFileName() );
		}
	}
}

void mainWin::scriptModified() {
	if( m_currAction ) {
		// set window title with '*' symbol, because it's been modified
		// it is invoked when text changes in the code (in text box)
		setWindowTitle( APP_NAME + " - " + m_currAction->getFileName() + "*" );

		// we changed the script so we have to set its state
		m_currAction->setModified( true );
	}
}

void mainWin::showAbout() {
	// show 'about' dialog as a modal window
	// the window and its controls has been designed using QtDesigner (about.ui in the project)
	// only background (gradient) for the logo on the left is created by code
	AboutDialog _about;
	_about.exec();
}

void mainWin::initLuaApi() {
	m_lua->registerFunction( "sleep", LuaApiEngine::prepareSleep );

	// we can make static function leftDown() without any argument instead of function with std::stack<int> argument with no elements and then
	// cast it to the appropriate type:
	m_lua->registerFunction( "leftDown", LuaApiEngine::prepareLeftDown );
	m_lua->registerFunction( "rightDown", LuaApiEngine::prepareRightDown );
	m_lua->registerFunction( "middleDown", LuaApiEngine::prepareMiddleDown );
	m_lua->registerFunction( "leftDownAt", LuaApiEngine::prepareLeftDownAt );
	m_lua->registerFunction( "rightDownAt", LuaApiEngine::prepareRightDownAt );
	m_lua->registerFunction( "middleDownAt", LuaApiEngine::prepareMiddleDownAt );

	m_lua->registerFunction( "leftUp", LuaApiEngine::prepareLeftUp );
	m_lua->registerFunction( "rightUp", LuaApiEngine::prepareRightUp );
	m_lua->registerFunction( "middleUp", LuaApiEngine::prepareMiddleUp );
	m_lua->registerFunction( "leftUpAt", LuaApiEngine::prepareLeftUpAt );
	m_lua->registerFunction( "rightUpAt", LuaApiEngine::prepareRightUpAt );
	m_lua->registerFunction( "middleUpAt", LuaApiEngine::prepareMiddleUpAt );
	
	m_lua->registerFunction( "leftClick", LuaApiEngine::prepareLeftClick );
	m_lua->registerFunction( "rightClick", LuaApiEngine::prepareRightClick );
	m_lua->registerFunction( "middleClick", LuaApiEngine::prepareMiddleClick );
	m_lua->registerFunction( "leftClickAt", LuaApiEngine::prepareLeftClickAt );
	m_lua->registerFunction( "rightClickAt", LuaApiEngine::prepareRightClickAt );
	m_lua->registerFunction( "middleClickAt", LuaApiEngine::prepareMiddleClickAt );

	m_lua->registerFunction( "leftDoubleClick", LuaApiEngine::prepareLeftDoubleClick );
	m_lua->registerFunction( "leftDoubleClickAt", LuaApiEngine::prepareLeftDoubleClickAt );

	m_lua->registerFunction( "moveTo", LuaApiEngine::prepareMoveTo );

	m_lua->registerFunction( "sendText", LuaApiEngine::prepareSendText );
}

void mainWin::getDataForAction() {
	// set time
	QTime _time = QTime( ui.hourSpin->value(), ui.minSpin->value(), ui.secSpin->value() );
	m_currAction->setTime( _time );


}

QString mainWin::getFuncName( QString textError ) {
	// in lua 5.1 the string has form like "[string "?"]:1: attempt to call global 'FunctionName' (a nil value)"
	// we need to find first and last occurence of '
	int _iBegin = textError.indexOf( "'" ) + 1;
	int _iEnd = textError.lastIndexOf( "'" );
	return textError.mid( _iBegin, _iEnd - _iBegin );
}

void mainWin::setCode( const QString& code ) {
	ui.scriptTextEdit->setFont( QFont( "Courier New", 8 ) );
	ui.scriptTextEdit->setText( code );
}

mainWin::~mainWin()
{
	ScriptsManager::removeScripts();
	delete m_calendar;
	delete m_lua;
	delete m_currAction;
	//UnhookWindowsHookEx( hook );
}
