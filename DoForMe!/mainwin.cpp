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

mainWin::mainWin(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags), m_iWidth( 821 ), m_iHeight( 507 ), m_calendar( NULL ), m_lua( NULL ), m_pCurrScript( NULL )
{
	ui.setupUi(this);

	QObject::connect( ui.actionAbout, SIGNAL( activated() ), this, SLOT( showAbout() ) );
	QObject::connect( ui.actionNew, SIGNAL( activated() ), this, SLOT( newFile() ) );
	QObject::connect( ui.actionRun, SIGNAL( activated() ), this, SLOT( runAction() ) );
	QObject::connect( ui.actionSaveScript, SIGNAL( activated() ), this, SLOT( saveScript() ) );
	QObject::connect( ui.scriptTextEdit, SIGNAL( textChanged() ), this, SLOT( scriptModified() ) );
	QObject::connect( ui.scriptsList, SIGNAL( currentTextChanged( const QString& ) ), this, SLOT( scriptSelected( const QString& ) ) );
	QObject::connect( ui.addActionButton, SIGNAL( clicked() ), this, SLOT( addAction() ) );
	QObject::connect( ui.detachButton, SIGNAL( clicked() ), this, SLOT( detachAction() ) );
	QObject::connect( ui.actionsList, SIGNAL( currentRowChanged ( int ) ), this, SLOT( actionSelected( int ) ) );
	
	// used for centering main app window
	QDesktopWidget screen;
	setGeometry( ( screen.width() - m_iWidth ) / 2, ( screen.height() - m_iHeight ) / 2, m_iWidth, m_iHeight );

	ActionsCalendar::setList( ui.actionsTable );
	m_calendar = new ActionsCalendar( this );
	m_calendar->setGeometry( ui.actionsList->width() + 10, m_iHeight - 210, m_iWidth - ( ui.actionsList->width() + 10 ), 210 );
	m_calendar->show();
	
	m_lua = new LuaEngine();
	LuaApiEngine::setLuaEngine( m_lua );
	LuaApiEngine::initSpecialKeys();

	loadScripts( CONF::SCRIPT_DIR );

	// register functions used in lua's scripts for m_lua.
	initLuaApi();
	
	//hook = SetWindowsHookEx( WH_MOUSE_LL, &mouseHook, GetModuleHandle( NULL ), 0 );
}

void mainWin::loadScripts( const QString& path ) {
	QDir myDir( path );

	// define which extensions we want to look for
	QStringList _filesExt;
	_filesExt.push_back( "*" + CONF::EXT );

	// get list of files
	QStringList _fileList = myDir.entryList( _filesExt );
	
	// iterate through all files and add them into map
	while( !_fileList.empty() ) {
		QString _fileNameExt = _fileList.back();
		_fileList.pop_back();

		// create script object from the file
		try {
			Script* _pScript = new Script( path + _fileNameExt, Script::LOAD );
			if( ScriptsManager::addScript( _pScript ) ) {
				// add script title to the scripts list
				ui.scriptsList->addItem( _pScript->getFileName() );
			}
		} catch( int e ) {
			if( e == Script::FileOpenException ) {
				QMessageBox _msg( QMessageBox::Critical, "Error", "Unable to open file \"" + path + _fileNameExt + "\". The file probably doesn't exists.", QMessageBox::Ok );
				_msg.exec();
			}
		}
	}
}

void mainWin::newFile() {
	bool _ok = true;
	QString _strFileName = "";
	// try to add new script
	while( _strFileName == "" && _ok ) {
		// show input dialog for file name
		_strFileName = QInputDialog::getText( NULL, "Script file name",
			"Type file name for script (must not be empty):", QLineEdit::Normal, "", &_ok );

		if( ScriptsManager::getScript( _strFileName ) != NULL ) {
			QMessageBox _msg( QMessageBox::Critical, "Error", "The file already exists.", QMessageBox::Ok );
			_msg.exec();

			// make it empty to go through while again
			_strFileName = "";
		}
	}

	if( _ok ) {
		// create script object from the file
		try {
			Script* _pScript = new Script( CONF::SCRIPT_DIR + _strFileName, Script::CREATE );
			if( ScriptsManager::addScript( _pScript ) ) {
				// add script title to the scripts list to the title (above text edit) and clean the text area
				ui.scriptsList->addItem( _pScript->getFileName() );
				setScriptTitle( "  " + _pScript->getFileName() );
				// TODO if the area contains modified text, ask if the user wants to save it
				setCode( "" );
			}
		} catch( int e ) {
			if( e == Script::FileOpenException ) {
				QMessageBox _msg( QMessageBox::Critical, "Error", "Unable to create file \"" + CONF::SCRIPT_DIR + _strFileName + "\". Probably wrong name for file.", QMessageBox::Ok );
				_msg.exec();
			}
		}
	}
}

void mainWin::runAction() {
	if( m_pCurrScript == NULL ) return;

	// load and parse script (from text field) by checking its correctness
	switch( m_lua->loadScript( m_pCurrScript->getCode().toStdString().c_str(), LuaEngine::BUFFER ) ) {
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
					QMessageBox _msg( QMessageBox::Critical, "Error", "Memory allocation error." );
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

void mainWin::saveScript() {
	if( !m_pCurrScript ) return;
	if( !m_pCurrScript->isModified() ) return;

	// set new code for the currently selected script
	m_pCurrScript->setCode( ui.scriptTextEdit->toPlainText() );

	// make title without '*' symbol
	setScriptTitle( m_pCurrScript->getFileName() );

	// save the script to the file
	if( !ScriptsManager::saveToFile( m_pCurrScript->getFileName() ) ) {
		QMessageBox _msg( QMessageBox::Critical, "Error", "Unexpected error. The script wasn't saved." );
		_msg.exec();
	}
}

void mainWin::saveAction() {
	
}

void mainWin::scriptSelected( const QString& scriptTitle ) {
	// find the appropriate script
	m_pCurrScript = ScriptsManager::getScript( scriptTitle );

	// put script code to the text edit
	setCode( m_pCurrScript->getCode() );

	// set title above the text edit
	setScriptTitle( m_pCurrScript->getFileName() );
}

void mainWin::scriptModified() {
	if( m_pCurrScript ) {
		// set script title with '*' symbol, because it's been modified
		// it is invoked when text changes in the code (in text box)
		setScriptTitle( m_pCurrScript->getFileName() + "*" );

		// we changed the script so we have to set its state
		m_pCurrScript->setModified( true );
	}
}

void mainWin::addAction() {
	// if the script hasn't been selected
	if( !m_pCurrScript ) {
		QMessageBox _msg( QMessageBox::Information, "Information", "The script hasn't been selected.", QMessageBox::Ok );
		_msg.exec();
		return;
	}

	// inform user that the date is a past and ask him if he still wants to add teh action
	if( !checkDateCorrectness( m_calendar->getSelectedDate() ) ) {
		QMessageBox _msg( QMessageBox::Information, "Information", "The date is from the past. Do you still want to add the action?",
			QMessageBox::Yes | QMessageBox::No );
		if( _msg.exec() == QMessageBox::No )
			return;
	}

	ActionSettings _actionSettings( m_calendar->getSelectedDate(), ui.actionsTable );
	int _iResult = _actionSettings.exec();
	
	// if a user clicked cancel
	if( !_iResult ) return;

	// create new action and add it to calendar
	Action* _newAction = new Action( m_pCurrScript, _actionSettings );
	m_calendar->addAction( m_calendar->getSelectedDate(), _newAction );
}

void mainWin::showAbout() {
	// show 'about' dialog as a modal window
	// the window and its controls has been designed using QtDesigner (about.ui in the project)
	// only background (gradient) for the logo on the left is created by code
	AboutDialog _about;
	_about.exec();
}

void mainWin::actionSelected( int index ) {
	if( index == -1 ) return;

	// set highlights off to the old selected action
	Action* _pAction = m_calendar->getCurrentAction();
	if( _pAction )
		_pAction->setHighlight( false );

	_pAction = m_calendar->getAction( index );
	if( _pAction ) {
		m_calendar->setCurrentAction( _pAction );
		_pAction->setHighlight( true );
	}

	m_calendar->update();
	// QCalendarWidget needs focus to be fully updated...
	m_calendar->setFocus();
}

void mainWin::detachAction() {
	Action* _pAction = m_calendar->getCurrentAction();
	if( !_pAction ) return;

	_pAction->setHighlight( false );

	// exclude date from the action
	_pAction->excludeDate( m_calendar->getSelectedDate() );

	// create new action and add it to calendar
	Action* _newAction = new Action( _pAction );
	_newAction->setHighlight( true );
	m_calendar->addAction( m_calendar->getSelectedDate(), _newAction );
	m_calendar->setCurrentAction( _newAction );
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
	//QTime _time = QTime( ui.hourSpin->value(), ui.minSpin->value(), ui.secSpin->value() );
	//m_pCurrAction->setTime( _time );


}

QString mainWin::getFuncName( QString textError ) {
	// in lua 5.1 the string has form like "[string "?"]:1: attempt to call global 'FunctionName' (a nil value)"
	// we need to find first and last occurence of '
	int _iBegin = textError.indexOf( "'" ) + 1;
	int _iEnd = textError.lastIndexOf( "'" );
	return textError.mid( _iBegin, _iEnd - _iBegin );
}

void mainWin::setScriptTitle( QString title ) {
	ui.scriptTitle->setText( "  " + title );
}

void mainWin::setCode( const QString& code ) {
	ui.scriptTextEdit->setFont( QFont( "Courier New", 8 ) );
	ui.scriptTextEdit->setText( code );
}

bool mainWin::checkDateCorrectness( QDate date ) {
	QDate _currentDate = QDate::currentDate();
	if( date < _currentDate ) {
		return false;
	}
	
	return true;
}

mainWin::~mainWin()
{
	ScriptsManager::removeScripts();
	delete m_calendar;
	delete m_lua;
	//UnhookWindowsHookEx( hook );
}
