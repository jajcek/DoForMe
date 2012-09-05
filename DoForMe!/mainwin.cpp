#include <Windows.h>
#include "mainwin.h"

mainWin::mainWin(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags), m_calendar( NULL ), m_pCurrScript( NULL ), m_tray( NULL )
{
	ui.setupUi(this);

	connect( ui.actionAbout, SIGNAL( activated() ), this, SLOT( showAbout() ) );
	connect( ui.actionNew, SIGNAL( activated() ), this, SLOT( newFile() ) );
	connect( ui.actionMenuNewScript, SIGNAL( activated() ), this, SLOT( newFile() ) );
	connect( ui.actionImport, SIGNAL( activated() ), this, SLOT( importScripts() ) );
	connect( ui.actionMenuImportScripts, SIGNAL( activated() ), this, SLOT( importScripts() ) );
	connect( ui.actionSaveScript, SIGNAL( activated() ), this, SLOT( saveScript() ) );
	connect( ui.actionMenuSaveScript, SIGNAL( activated() ), this, SLOT( saveScript() ) );
	connect( ui.removeScriptButton, SIGNAL( clicked() ), this, SLOT( removeScript() ) );
	connect( ui.actionMenuRemoveScript, SIGNAL( activated() ), this, SLOT( removeScript() ) );
	connect( ui.actionParseScript, SIGNAL( activated() ), this, SLOT( parseScript() ) );
	connect( ui.actionMenuParseScript, SIGNAL( activated() ), this, SLOT( parseScript() ) );
	connect( ui.actionRun, SIGNAL( activated() ), this, SLOT( runScript() ) );
	connect( ui.actionMenuRunScript, SIGNAL( activated() ), this, SLOT( runScript() ) );
	connect( ui.actionRecord, SIGNAL( activated() ), this, SLOT( startRecording() ) );

	connect( ui.actionTray, SIGNAL( activated() ), this, SLOT( toTray() ) );
	connect( ui.scriptTextEdit, SIGNAL( textChanged() ), this, SLOT( scriptModified() ) );
	connect( ui.scriptsList, SIGNAL( currentTextChanged( const QString& ) ), this, SLOT( scriptSelected( const QString& ) ) );
	connect( ui.addActionButton, SIGNAL( clicked() ), this, SLOT( addAction() ) );
	connect( ui.actionMenuNewAction, SIGNAL( activated() ), this, SLOT( addAction() ) );
	connect( ui.editButton, SIGNAL( clicked() ), this, SLOT( editAction() ) );
	connect( ui.actionMenuEditAction, SIGNAL( activated() ), this, SLOT( editAction() ) );
	connect( ui.removeButton, SIGNAL( clicked() ), this, SLOT( removeAction() ) );
	connect( ui.actionMenuRemoveAction, SIGNAL( activated() ), this, SLOT( removeAction() ) );
	connect( ui.detachButton, SIGNAL( clicked() ), this, SLOT( detachAction() ) );
	connect( ui.actionMenuDetachAction, SIGNAL( activated() ), this, SLOT( detachAction() ) );

	connect( ui.leftButton, SIGNAL( clicked() ), this, SLOT( moveLeft() ) );
	connect( ui.actionMenuMoveLeft, SIGNAL( activated() ), this, SLOT( moveLeft() ) );
	connect( ui.upButton, SIGNAL( clicked() ), this, SLOT( moveUp() ) );
	connect( ui.actionMenuMoveUp, SIGNAL( activated() ), this, SLOT( moveUp() ) );
	connect( ui.downButton, SIGNAL( clicked() ), this, SLOT( moveDown() ) );
	connect( ui.actionMenuMoveDown, SIGNAL( activated() ), this, SLOT( moveDown() ) );
	connect( ui.rightButton, SIGNAL( clicked() ), this, SLOT( moveRight() ) );
	connect( ui.actionMenuMoveRight, SIGNAL( activated() ), this, SLOT( moveRight() ) );

	connect( ui.saveButton, SIGNAL( clicked() ), this, SLOT( saveData() ) );
	connect( ui.actionsTable, SIGNAL( itemClicked( QTableWidgetItem* ) ), this, SLOT( actionSelected( QTableWidgetItem* ) ) );

	connect( ui.actionMenuInterval, SIGNAL( activated() ), this, SLOT( showPlayerDialog() ) );
	connect( ui.actionMenuRecorder, SIGNAL( activated() ), this, SLOT( showRecorderDialog() ) );
	connect( ui.actionMenuReminder, SIGNAL( activated() ), this, SLOT( showReminderDialog() ) );

	connect( ui.mouseCmdList, SIGNAL( itemDoubleClicked( QListWidgetItem* ) ), this, SLOT( putCommand( QListWidgetItem*  ) ) );
	connect( ui.keyboardCmdList, SIGNAL( itemDoubleClicked( QListWidgetItem* ) ), this, SLOT( putCommand( QListWidgetItem*  ) ) );
	connect( ui.otherCmdList, SIGNAL( itemDoubleClicked( QListWidgetItem* ) ), this, SLOT( putCommand( QListWidgetItem*  ) ) );

	// initialize pointers to calendar tools
	CalendarTools::AddButton = ui.addActionButton;
	CalendarTools::NewMenu = ui.actionMenuNewAction;
	CalendarTools::EditButton = ui.editButton;
	CalendarTools::EditMenu = ui.actionMenuEditAction;
	CalendarTools::RemoveActionButton = ui.removeButton;
	CalendarTools::RemoveMenu = ui.actionMenuRemoveAction;
	CalendarTools::DetachActionButton = ui.detachButton;
	CalendarTools::DetachMenu = ui.actionMenuDetachAction;
	CalendarTools::UpButton = ui.upButton;
	CalendarTools::MoveUpMenu = ui.actionMenuMoveUp;
	CalendarTools::DownButton = ui.downButton;
	CalendarTools::MoveDownMenu = ui.actionMenuMoveDown;
	CalendarTools::LeftButton = ui.leftButton;
	CalendarTools::MoveLeftMenu = ui.actionMenuMoveLeft;
	CalendarTools::RightButton = ui.rightButton;
	CalendarTools::MoveRightMenu = ui.actionMenuMoveRight;
	
	// used for centering main app window
	QDesktopWidget screen;
	setGeometry( ( screen.width() - width() ) / 2, ( screen.height() - height() ) / 2, width(), height() );

	// resize width of columns for actions list (actionsTable)
	ui.actionsTable->setColumnWidth( 0, 25 );
	ui.actionsTable->sortItems( 0, Qt::AscendingOrder );

	// loading script, important: it must be called before creating ActionsCalendar
	// because the calendar loads actions from database and it needs to find pointers to
	// scripts for actions
	loadScripts( CONF::SCRIPT_DIR );

	ActionsCalendar::setList( ui.actionsTable );
	m_calendar = new ActionsCalendar( this );
	m_calendar->setGeometry( ui.actionsTable->width() + 9, height() - 250, width() - ( ui.actionsTable->width() + 9 ), 250 );
	m_calendar->show();
	
	//m_lua = new LuaEngine();
	//LuaApiEngine::setLuaEngine( m_lua );
	LuaApiEngine::initSpecialKeys();

	m_tray = new TraySystem( ":/mainWin/logo.png", this );
	initTraySystem( m_tray );
	ActionCaller::getInstance()->setTrayToUpdate( m_tray );

	// register functions used in lua's scripts for m_lua.
	initLuaApi();

	Recorder::setTextEdit( ui.scriptTextEdit );

	QAction* _mainWindowAction = new QAction( this );
	connect( _mainWindowAction, SIGNAL( triggered() ), this, SLOT( openApp() ) );
	Recorder::setMainWindowAction( _mainWindowAction );
}

void mainWin::loadScripts( const QString& path ) {
	qDebug( "mainWin::loadScripts()" );

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
			} else {
				delete _pScript;
			}
		} catch( int e ) {
			if( e == Script::FileOpenException ) {
				QMessageBox _msg( QMessageBox::Critical, "Error", "Unable to open file \"" + path + _fileNameExt + "\". The file probably doesn't exists.", QMessageBox::Ok );
				_msg.exec();
			}
		}
	}

	// select first script n the list
	ui.scriptsList->setCurrentRow( 0 );
}

QString mainWin::getCode() const {
	qDebug( "mainWin::getCode()" );

	return ui.scriptTextEdit->toPlainText();
}

void mainWin::setCode( const QString& code ) {
	qDebug( "mainWin::setCode()" );

	ui.scriptTextEdit->blockSignals( true );
	ui.scriptTextEdit->setFont( QFont( "Courier New", 8 ) );
	ui.scriptTextEdit->setPlainText( code );
	ui.scriptTextEdit->blockSignals( false );
}

void mainWin::setScriptTitle( QString title ) {
	qDebug( "mainWin::setScriptTitle()" );

	ui.scriptTitle->setText( "  " + title );
}

void mainWin::timerEvent( QTimerEvent* e ) {
	qDebug( "reset in timerEvent" );

	m_calendar->update();
	m_calendar->setFocus();
	ActionCaller::getInstance()->setActions( m_calendar->getActionsForDate( QDate::currentDate() ) );
	m_updater.start( calcTimeForNewDay(), this );
}

void mainWin::newFile() {
	qDebug( "mainWin::newFile()" );

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
			Script* _pScript = new Script( CONF::SCRIPT_DIR + _strFileName + CONF::EXT, Script::CREATE );
			if( ScriptsManager::addScript( _pScript ) ) {
				// add script title to the scripts list to the title and clean the text area
				ui.scriptsList->addItem( _pScript->getFileName() );
				ui.scriptsList->setCurrentRow( ui.scriptsList->count() - 1 );
				setScriptTitle( _pScript->getFileName() );
				// TODO if the area contains modified text, ask if the user wants to save it
				setCode( "" );
			}
		} catch( int e ) {
			if( e == Script::FileOpenException ) {
				QMessageBox _msg( QMessageBox::Critical, "Error", "Unable to create file \"" + CONF::SCRIPT_DIR + _strFileName + CONF::EXT + "\". Probably wrong name for file.", QMessageBox::Ok );
				_msg.exec();
			}
		}
	}
}

void mainWin::importScripts() {
	qDebug( "mainWin::importScripts()" );

	// show file dialog to select files to import
	QStringList _files = QFileDialog::getOpenFileNames( this, "Import scripts", "C:/", QString( "Scripts (*" ) + CONF::EXT + ")" );

	// copy the files into the "scripts" directory
	int _filesNumber = _files.size();
	for( int i = 0; i < _filesNumber; ++i ) {
		QString _strFile = _files.at( i );
		QFileInfo _fileInfo( _strFile );
		QFile::copy( _strFile, "scripts/" + _fileInfo.fileName() );
	}

	loadScripts( CONF::SCRIPT_DIR );
}

void mainWin::saveScript() {
	qDebug( "mainWin::saveScript()" );

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
	} else {
		m_pCurrScript->setModified( false );
		ui.actionSaveScript->setEnabled( false );
		ui.actionMenuSaveScript->setEnabled( false );
	}
}

void mainWin::toTray() {
	qDebug( "mainWin::toTray" );

	LuaEngine::getInstance()->reset();

	// put current actions to the icon tray context menu
	ActionCaller::getInstance()->setActions( m_calendar->getActionsForDate( QDate::currentDate() ) );

	// calculate how much time if left to next day
	m_updater.start( calcTimeForNewDay(), this );

	// show tray icon
	m_tray->show();

	// hide app window
	hide();
}

void mainWin::parseScript() {
	runScript( true );

	// validateLastLoad and validateLastParse returns non-zero value if an error occured
	if( !LuaEngine::getInstance()->validateLastLoad() && !LuaEngine::getInstance()->validateLastParse() ) {
		QMessageBox _msg( QMessageBox::Information, "Parsing", "The script is correct." );
		_msg.exec();
	}
}

void mainWin::runScript( bool onlyParse ) {
	qDebug( "mainWin::runScript()" );

	if( m_pCurrScript == NULL ) return;

	// load and parse script (from text field) by checking its correctness
	LuaEngine::getInstance()->reset();
	switch( LuaEngine::getInstance()->loadScript( getCode().toStdString().c_str(), LuaEngine::BUFFER ) ) {
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
			switch( LuaEngine::getInstance()->parseScript() ) {
				case LUA_ERRRUN: {
					// get text error returned by lua_pcall function (from lua's library)
					QString _error = LuaEngine::getInstance()->getTextError();

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

	if( onlyParse == false ) {
		// start script (by taking commands from the lua's stack one by one)
		// the stack is in the LuaEngine class
		LuaEngine::getInstance()->start();
	}
}

void mainWin::startRecording() {
	if( !m_pCurrScript ) {
		QMessageBox _msg( QMessageBox::Information, "Information",
						  "Create a new script file or select an existing one before recording anything." );
		_msg.exec();
		return;
	}

	if( RecorderSettings::getInstance()->isTrayOn() )
		hide();
	Recorder::startRecording();
}

void mainWin::removeScript() {
	qDebug( "mainWin::removeScript()" );

	if( m_calendar->isScriptUsed( m_pCurrScript ) ) {
		QString _text = QString( "The script is being used in the actions. If you remove the script " ) +
								 "you will remove the actions which use the script. Do you want to continue?";
		QMessageBox _msg( QMessageBox::Information, "Information", _text, QMessageBox::Yes | QMessageBox::No );
		switch( _msg.exec() ) {
			case QMessageBox::Yes:
				m_calendar->removeActionsUsingScript( m_pCurrScript );
				break;
			case QMessageBox::No:
				return;
		}
	}

	// remove the script file
	QString _scriptName = m_pCurrScript->getFileName();
	QFile::remove( CONF::SCRIPT_DIR + _scriptName + CONF::EXT );

	// remove the script from the scripts manager
	ScriptsManager::removeScript( _scriptName );

	m_pCurrScript = NULL;

	// remove the script from the scripts list
	int _rowSelected = ui.scriptsList->currentRow();
	delete ui.scriptsList->item( _rowSelected );

	// if there are no more scripts on the list change the text areas and disable buttons
	if( ui.scriptsList->count() == 0 ) {
		setScriptTitle( "New script" );
		setCode( "" );

		// disable buttons/menus after removing last script
		ui.removeScriptButton->setEnabled( false );
		ui.actionMenuRemoveScript->setEnabled( false );
		ui.actionMenuRunScript->setEnabled( false );
		ui.actionRun->setEnabled( false );
		ui.actionParseScript->setEnabled( false );
		ui.actionMenuParseScript->setEnabled( false );
	}
}

void mainWin::scriptSelected( const QString& scriptTitle ) {
	qDebug( "mainWin::scriptSelected()" );

	// if the script is modified we want to inform about saving it
	if( m_pCurrScript ) {
		if( m_pCurrScript->isModified() ) {
			QMessageBox _msg( QMessageBox::Information, "Information", "The script has been modified. Do you want to keep changes?",
							  QMessageBox::Yes | QMessageBox::No );
			switch( _msg.exec() ) {
				case QMessageBox::Yes:
					m_pCurrScript->setCode( getCode() );
					ScriptsManager::saveToFile( m_pCurrScript->getFileName() );
				case QMessageBox::No:
					m_pCurrScript->setModified( false );
					break;
			}
		}
	}

	// find the appropriate script
	m_pCurrScript = ScriptsManager::getScript( scriptTitle );
	if( m_pCurrScript ) {
		// enable buttons/menus after selecting script
		ui.removeScriptButton->setEnabled( true );
		ui.actionMenuRemoveScript->setEnabled( true );
		ui.actionMenuRunScript->setEnabled( true );
		ui.actionRun->setEnabled( true );
		ui.actionParseScript->setEnabled( true );
		ui.actionMenuParseScript->setEnabled( true );

		// put script code to the text edit
		setCode( m_pCurrScript->getCode() );

		// set title above the text edit
		setScriptTitle( m_pCurrScript->getFileName() );
	}
}

void mainWin::scriptModified() {
	qDebug( "mainWin::scriptModified()" );

	if( m_pCurrScript ) {
		if( !m_pCurrScript->isModified() ) {
			// set script title with '*' symbol, because it's been modified
			// it is invoked when text changes in the code (in text box)
			setScriptTitle( m_pCurrScript->getFileName() + "*" );

			// we changed the script so we have to set its state
			m_pCurrScript->setModified( true );

			// enable button for saving
			ui.actionSaveScript->setEnabled( true );
			ui.actionMenuSaveScript->setEnabled( true );
		}
	}
}

void mainWin::addAction() {
	qDebug( "mainWin::addAction" );

	// inform user that the date is in the past and ask him if he still wants to add the action
	if( !checkDateCorrectness( m_calendar->getSelectedDate() ) ) {
		QMessageBox _msg( QMessageBox::Information, "Information", "The date is from the past. Do you still want to add the action?",
			QMessageBox::Yes | QMessageBox::No );
		if( _msg.exec() == QMessageBox::No )
			return;
	}

	// show action settings dialog
	ActionSettings _actionSettings( m_calendar->getSelectedDate() );
	_actionSettings.setScripts( ScriptsManager::getScriptsList() );
	int _iResult = _actionSettings.exec();
	
	// if a user clicked apply
	if( _iResult ) {
		if( m_calendar->getCurrentAction() )
			m_calendar->getCurrentAction()->setHighlight( false );
		// create new action and add it to calendar as well as highlight it
		// and refresh calendar to repaint cells
		Action* _newAction = new Action( m_calendar->getSelectedDate(), _actionSettings );
		m_calendar->addAction( m_calendar->getSelectedDate(), _newAction );
		_newAction->setHighlight( true );
		m_calendar->refreshRepetitions();
		m_calendar->setCurrentAction( _newAction );
	}
}

void mainWin::showAbout() {
	qDebug( "mainWin::showAbout()" );

	// show 'about' dialog as a modal window
	// the window and its controls has been designed using QtDesigner (about.ui in the project)
	// only background (gradient) for the logo on the left is created by code
	AboutDialog _about;
	_about.exec();
}

void mainWin::actionSelected( QTableWidgetItem* item ) {
	qDebug( "mainWin::actionSelected()" );

	// set highlights off to the old selected action
	Action* _pAction = m_calendar->getCurrentAction();
	if( _pAction )
		_pAction->setHighlight( false );

	int _actionId = ui.actionsTable->item( ui.actionsTable->currentRow(), 0 )->text().toInt() - 1;
	_pAction = m_calendar->getActionById( _actionId );
	if( _pAction ) {
		m_calendar->setCurrentAction( _pAction );
	}

	m_calendar->update();
	// QCalendarWidget needs focus to be fully updated...
	m_calendar->setFocus();
}

void mainWin::detachAction() {
	qDebug( "mainWin::detachAction()" );

	m_calendar->detachCurrentAction();
}

void mainWin::removeAction() {
	qDebug( "mainWin::removeAction()" );

	// not needed anymore, we diable the button when there is no action selected
	//if( !m_calendar->getCurrentAction() ) return;

	if( m_calendar->getCurrentAction()->isXDays() || m_calendar->getCurrentAction()->getDays() ) {
		QMessageBox _msg( QMessageBox::Information, "Information", "Do you want to remove all repetitions?",
			QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel );
		switch( _msg.exec() ) {
			case QMessageBox::Yes:
				m_calendar->removeCurrentActions();
				break;
			case QMessageBox::No:
				m_calendar->removeCurrentAction();
				break;
		}
	} else {
		m_calendar->removeCurrentActions();
	}
}

void mainWin::editAction() {
	qDebug( "mainWin::editAction()" );

	Action* _pAction = m_calendar->getCurrentAction();
	if( !_pAction ) return;

	ActionSettings _actionSettings( m_calendar->getSelectedDate() );
	_actionSettings.setScripts( ScriptsManager::getScriptsList() );
	// set current values for action
	_actionSettings.selectScript( _pAction->getScript()->getFileName() );
	_actionSettings.setHours( _pAction->getHours() );
	_actionSettings.setMinutes( _pAction->getMinutes() );
	_actionSettings.setSeconds( _pAction->getSeconds() );
	_actionSettings.setIsXDays( _pAction->isXDays() );
	_actionSettings.setXDays( _pAction->getXDays() );
	_actionSettings.setDaysFlags( _pAction->getDays() );
	int _iResult = _actionSettings.exec();

	// if a user clicked apply
	if( _iResult ) {
		_pAction->setSetting( _actionSettings );
	}

	// to reselect it after refreshRepetitions (because it will unselect it it there are > 1 action in that day)
	int _id = _pAction->getId();

	m_calendar->refreshRepetitions();

	m_calendar->setCurrentAction( m_calendar->getActionById( _id ) );
}

void mainWin::saveData() {
	qDebug( "mainWin::saveData()" );

	m_calendar->saveData();
}

void mainWin::moveUp() {
	qDebug( "mainWin::moveUp()" );

	m_calendar->moveCurrAction( ActionsCalendar::UP );
}

void mainWin::moveDown() {
	qDebug( "mainWin::moveDown()" );

	m_calendar->moveCurrAction( ActionsCalendar::DOWN );
}

void mainWin::moveLeft() {
	qDebug( "mainWin::moveLeft()" );

	m_calendar->moveCurrAction( ActionsCalendar::LEFT );
}

void mainWin::moveRight() {
	qDebug( "mainWin::moveRight()" );

	m_calendar->moveCurrAction( ActionsCalendar::RIGHT );
}

void mainWin::openApp() {
	show();
	m_tray->hide();
}

void mainWin::quitApp() {
	m_tray->hide();
	close();
}

void mainWin::showPlayerDialog() {
	qDebug( "mainWin::showPlayerDialog" );

	PlayerSettings::getInstance()->exec();
}

void mainWin::showRecorderDialog() {
	qDebug( "mainWin::showRecorderDialog" );

	RecorderSettings::getInstance()->exec();
}

void mainWin::showReminderDialog() {
	qDebug( "mainWin::showReminderDialog" );

	ReminderDialog::getInstance()->exec();
}

void mainWin::putCommand( QListWidgetItem* item ) {
	qDebug( "mainWin::putCommand" );

	QTextCursor _cursor( ui.scriptTextEdit->textCursor() );
	QString _cmd = "";
	// if the string starts with "{" we need to get only the {X} part, otherwise get whole string
	if( item->text().startsWith( "{" ) ) {
		int _2ndBracketPos = item->text().indexOf( "}" );
		_cmd = item->text().left( _2ndBracketPos + 1 );
	} else {
		_cmd = item->text() + "\n";
	}
	_cursor.insertText( _cmd );
}

void mainWin::initTraySystem( TraySystem* tray ) {
	QAction* _openAction = new QAction( "Open", this );
	connect( _openAction, SIGNAL( triggered() ), this, SLOT( openApp() ) );

	QAction* _exitAction = new QAction( "Exit", this );
	connect( _exitAction, SIGNAL( triggered() ), this, SLOT( quitApp() ) );

	tray->addQAction( _openAction );
	tray->addQAction( _exitAction );
}

void mainWin::initLuaApi() {
	qDebug( "mainWin::initLuaApi()" );

	LuaEngine::getInstance()->registerFunction( "setInterval", LuaApiEngine::prepareSetInterval );
	LuaEngine::getInstance()->registerFunction( "sleep", LuaApiEngine::prepareSleep );

	// we can make static function leftDown() without any argument instead of function with std::stack<int> argument with no elements and then
	// cast it to the appropriate type:
	LuaEngine::getInstance()->registerFunction( "leftDown", LuaApiEngine::prepareLeftDown );
	LuaEngine::getInstance()->registerFunction( "rightDown", LuaApiEngine::prepareRightDown );
	LuaEngine::getInstance()->registerFunction( "middleDown", LuaApiEngine::prepareMiddleDown );
	LuaEngine::getInstance()->registerFunction( "leftDownAt", LuaApiEngine::prepareLeftDownAt );
	LuaEngine::getInstance()->registerFunction( "rightDownAt", LuaApiEngine::prepareRightDownAt );
	LuaEngine::getInstance()->registerFunction( "middleDownAt", LuaApiEngine::prepareMiddleDownAt );

	LuaEngine::getInstance()->registerFunction( "leftUp", LuaApiEngine::prepareLeftUp );
	LuaEngine::getInstance()->registerFunction( "rightUp", LuaApiEngine::prepareRightUp );
	LuaEngine::getInstance()->registerFunction( "middleUp", LuaApiEngine::prepareMiddleUp );
	LuaEngine::getInstance()->registerFunction( "leftUpAt", LuaApiEngine::prepareLeftUpAt );
	LuaEngine::getInstance()->registerFunction( "rightUpAt", LuaApiEngine::prepareRightUpAt );
	LuaEngine::getInstance()->registerFunction( "middleUpAt", LuaApiEngine::prepareMiddleUpAt );
	
	LuaEngine::getInstance()->registerFunction( "leftClick", LuaApiEngine::prepareLeftClick );
	LuaEngine::getInstance()->registerFunction( "rightClick", LuaApiEngine::prepareRightClick );
	LuaEngine::getInstance()->registerFunction( "middleClick", LuaApiEngine::prepareMiddleClick );
	LuaEngine::getInstance()->registerFunction( "leftClickAt", LuaApiEngine::prepareLeftClickAt );
	LuaEngine::getInstance()->registerFunction( "rightClickAt", LuaApiEngine::prepareRightClickAt );
	LuaEngine::getInstance()->registerFunction( "middleClickAt", LuaApiEngine::prepareMiddleClickAt );

	LuaEngine::getInstance()->registerFunction( "leftDoubleClick", LuaApiEngine::prepareLeftDoubleClick );
	LuaEngine::getInstance()->registerFunction( "leftDoubleClickAt", LuaApiEngine::prepareLeftDoubleClickAt );

	LuaEngine::getInstance()->registerFunction( "moveTo", LuaApiEngine::prepareMoveTo );

	LuaEngine::getInstance()->registerFunction( "sendText", LuaApiEngine::prepareSendText );
}

QString mainWin::getFuncName( QString textError ) {
	// in lua 5.1 the string has form like "[string "?"]:1: attempt to call global 'FunctionName' (a nil value)"
	// we need to find first and last occurence of '
	int _iBegin = textError.indexOf( "'" ) + 1;
	int _iEnd = textError.lastIndexOf( "'" );
	return textError.mid( _iBegin, _iEnd - _iBegin );
}

bool mainWin::checkDateCorrectness( QDate date ) {
	QDate _currentDate = QDate::currentDate();
	if( date < _currentDate ) {
		return false;
	}
	
	return true;
}

int mainWin::calcTimeForNewDay() const {
	QTime _currTime = QTime::currentTime();
	int _milliseconds = _currTime.msecsTo( QTime( 23, 59, 59, 999 ) ) + 1;
	return _milliseconds;
}

void mainWin::closeEvent( QCloseEvent* e ) {
	if( m_pCurrScript && m_pCurrScript->isModified() ) {
		QMessageBox _msg( QMessageBox::Information, "Information", "The script hasn't been saved. Do you want to save it before closing?",
			QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel );
		switch( _msg.exec() ) {
			case QMessageBox::Yes:
				m_pCurrScript->setCode( getCode() );
				ScriptsManager::saveToFile( m_pCurrScript->getFileName() );
				break;
			case QMessageBox::No:
				break;
			case QMessageBox::Cancel:
				e->ignore();
				return;
		}
	}

	e->accept();

	mainWin::~mainWin();

	exit( 0 );
}

void mainWin::resizeEvent( QResizeEvent* e ) {
	qDebug( "mainWin::resizeEvent" );

	int _newWidthForTextEdit = width() - ui.scriptsList->width() - 9 - ui.functionsToolBox->width();
	int _newHeightForTextEdit = height() - m_calendar->height() - 55 - 2 * ui.scriptTitle->height();
	int _newHeightForFunctionsList = _newHeightForTextEdit + 24;
	ui.scriptTextEdit->resize( _newWidthForTextEdit, _newHeightForTextEdit );
	ui.scriptsList->resize( ui.scriptsList->width(), _newHeightForTextEdit );
	ui.functionsToolBox->move( width() - ui.functionsToolBox->width(), ui.functionsToolBox->y() );
	ui.functionsToolBox->resize( ui.functionsToolBox->width(), _newHeightForFunctionsList );
	ui.scriptTitle->resize( _newWidthForTextEdit, ui.scriptTitle->height() );
	m_calendar->move( ui.actionsTable->width() + 9, height() - 250 );
	m_calendar->resize( width() - ( ui.actionsTable->width() + 9 ), 250 );
	ui.calendarToolsFrame->move( ui.calendarToolsFrame->x(), m_calendar->y() - 69 );
	ui.calendarToolsFrame->resize( m_calendar->width(), ui.calendarToolsFrame->height() );
	ui.saveButton->move( width() - 4 * ui.saveOnCloseCheck->width() - 5, ui.saveButton->y() );
	ui.saveOnCloseCheck->move( width() - 3 * ui.saveOnCloseCheck->width() - 10, ui.saveOnCloseCheck->y() );
	ui.actionsLabel->move( 0, ui.calendarToolsFrame->y() );
	ui.actionsTable->move( 0, ui.calendarToolsFrame->y() + ui.calendarToolsFrame->height() );
	int _heightForCmdLists = ui.functionsToolBox->height() - 60;
	int _widthForCmdLists = ui.mouseCmdList->width();
	ui.mouseCmdList->resize( _widthForCmdLists, _heightForCmdLists );
	ui.keyboardCmdList->resize( _widthForCmdLists, _heightForCmdLists );
	ui.otherCmdList->resize( _widthForCmdLists, _heightForCmdLists );
}

mainWin::~mainWin() {
	if( ui.saveOnCloseCheck->isChecked() )
		saveData();
	ScriptsManager::removeScripts();
	delete m_calendar;
	delete LuaEngine::getInstance();
}
