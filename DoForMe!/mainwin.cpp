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
	: QMainWindow(parent, flags), m_iWidth( 700 ), m_iHeight( 480 ), m_calendar( NULL ), m_lua( NULL )
{
	ui.setupUi(this);

	QObject::connect( ui.actionAbout, SIGNAL( activated() ), this, SLOT( showAbout() ) );
	QObject::connect( ui.browseScriptButton, SIGNAL( clicked() ), this, SLOT( browseScript() ) );
	QObject::connect( ui.runButton, SIGNAL( clicked() ), this, SLOT( runAction() ) );
	QObject::connect( ui.saveButton, SIGNAL( clicked() ), this, SLOT( saveAction() ) );
	QObject::connect( ui.saveAsButton, SIGNAL( clicked() ), this, SLOT( saveAsAction() ) );
	QObject::connect( ui.scriptTextEdit, SIGNAL( textChanged() ), this, SLOT( scriptModified() ) );
	
	// used for centering main app window
	QDesktopWidget screen;
	setGeometry( ( screen.width() - m_iWidth ) / 2, ( screen.height() - m_iHeight ) / 2, m_iWidth, m_iHeight );

	m_calendar = new DetailedCalendar( this );
	m_calendar->setGeometry( 0, m_iHeight - 211, m_iWidth, 211 );
	m_calendar->setGridVisible( true );
	m_calendar->setFirstDayOfWeek( Qt::Monday );
	m_calendar->setLocale( QLocale( "English, United States" ) );
	m_calendar->show();
	
	m_lua = new LuaEngine();
	LuaApiEngine::setLuaEngine( m_lua );
	LuaApiEngine::initSpecialKeys();

	// register functions used in lua's scripts for m_lua.
	initLuaApi();

	m_currAction = new Action();
	
	//hook = SetWindowsHookEx( WH_MOUSE_LL, &mouseHook, GetModuleHandle( NULL ), 0 );
}

void mainWin::browseScript() {
	// get full path to the selected file by showing a modal open file window
	QString _fullPath = QFileDialog::getOpenFileName( this, "Open script file...", "", "Scripts (*.apc);;All files (*.*)" );

	// if the user didn't canceled it means that the path has been taken
	if( _fullPath != "" ) {
		// set the path in the edit (next to browse button)
		ui.scriptPathEdit->setText( _fullPath );

		// load content of the file to memory
		QFile _scriptFile( _fullPath );
		if( !_scriptFile.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
			QMessageBox _msg( QMessageBox::Critical, "Script loading error.", "Error occured while loading the script." );
			_msg.exec();
		} else {
			QString _fileContent;
			while( !_scriptFile.atEnd() )
				_fileContent += _scriptFile.readLine();

			// load code from the memory to the text box
			ui.scriptTextEdit->setText( _fileContent );

			m_currAction->setPath( _fullPath );

			// and to the action object
			m_currAction->setCode( _fileContent );

			QFileInfo _pathInfo( _fullPath );
			QString _fileName( _pathInfo.fileName() );

			setWindowTitle( APP_NAME + " - " + _fileName );

			m_currAction->setFileName( _fileName );
		}
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
					// we need to copy the stack created in the LuaApiEngine to the luaEngine
					//m_lua->copyData( LuaApiEngine::getCommandsStack(), LuaApiEngine::getArgsStack() ); 
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
		// the script exists as a file, we need to update it
		// update code for current action
		m_currAction->setCode( ui.scriptTextEdit->toPlainText() );

		// set window title without '*' symbol, because it's been saved
		setWindowTitle( APP_NAME + " - " + m_currAction->getFileName() );
	}
}

void mainWin::saveAsAction() {
	// get full path of a file which we will be saving to
	QString _fullPath = QFileDialog::getSaveFileName( this, "Save script...", "", "Scripts (*.apc);;All files (*.*)" );

	// if a user didn't click 'cancel', otherwise _fullPath is equal to ""
	if( _fullPath != "" ) {
		// set the path in the edit (next to browse button)
		ui.scriptPathEdit->setText( _fullPath );

		// set the path and code in the currently selected action object
		m_currAction->setPath( _fullPath );
		m_currAction->setCode( ui.scriptTextEdit->toPlainText() );

		// set window title without '*' symbol, because it's been saved
		setWindowTitle( APP_NAME + " - " + m_currAction->getFileName() );
	}
}

void mainWin::scriptModified() {
	// set window title with '*' symbol, because it's been modified
	setWindowTitle( APP_NAME + " - " + m_currAction->getFileName() + "*" );
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

QString mainWin::getFuncName( QString textError ) {
	// in lua 5.1 the string has form like "[string "?"]:1: attempt to call global 'FunctionName' (a nil value)"
	// we need to find first and last occurence of '
	int _iBegin = textError.indexOf( "'" ) + 1;
	int _iEnd = textError.lastIndexOf( "'" );
	return textError.mid( _iBegin, _iEnd - _iBegin );
}

mainWin::~mainWin()
{
	delete m_calendar;
	delete m_lua;
	delete m_currAction;
	//UnhookWindowsHookEx( hook );
}
