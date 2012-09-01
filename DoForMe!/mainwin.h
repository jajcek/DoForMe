#pragma once

#include <QFile>
#include <QApplication>
#include <QLabel>
#include <QString>
#include <QTextStream>
#include <qdesktopwidget.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qformlayout.h>
#include <qsystemtrayicon.h>
#include <qevent.h>
#include "ui_mainwin.h"
#include "lua_api.h"
#include "lua_engine.h"
#include "calendar.h"
#include "about_dialog.h"
#include "action.h"
#include "new_file.h"
#include "script.h"
#include "scripts_manager.h"
#include "conf.h"
#include "action_settings.h"
#include "calendar_tools.h"
#include "tray_system.h"
#include "action_caller.h"

/**
	\class mainWin mainwin.h "mainwin.h"
	\brief Main class for window and its controls.
	\author Jacek Topolski
	\version 1.0
	\date 28.07.2012
*/
class mainWin : public QMainWindow
{
	Q_OBJECT

private:
	/**
		\brief Object containing all controls of the window.
	*/
	Ui::mainWinClass ui;
	/**
		\brief Pointer to the calendar object.
	*/
	ActionsCalendar* m_calendar;
	/**
		\brief Pointer to the currently selected script.
	*/
	Script* m_pCurrScript;
	/**
		\brief Pointer to the tray icon system.
	*/
	TraySystem* m_tray;
	/**
		\brief Timer which is used to update calendar, action caller and context menu of the tray system.
	*/
	QBasicTimer m_updater;

public:
	/**
		\brief Creates the main window, connects signals to slots and initializes the most important objects.
	*/
	mainWin(QWidget *parent = 0, Qt::WFlags flags = 0);
	/**
		\brief Frees memory of the calendar, scripts and lua engine.
	*/
	~mainWin();
	/**
		\brief Loads script from the given path and puts the into the scripts list.
		\param[in] path Path for the directory with the scripts.
	*/
	void loadScripts( const QString& path );
	/**
		\return Code from the text box.
	*/
	QString getCode() const;
	/**
		\brief Sets code to the text box.
		\details The method set the text with changed font family. Also it blocks signals
		at the beginning and unblock them at the end of the method to not emit textChanged() signal.
		\param[in] code Code to set.
	*/
	void setCode( const QString& code );
	/**
		\brief Sets title for the script (only above the text box with its code).
		\param[in] title Text for title.
	*/
	void setScriptTitle( QString title );
	/**
		\brief Method called by the timer fo updating elements. See mainWin::m_updater for more details.
	*/
	void timerEvent( QTimerEvent* e );

public slots:
	/**
		\brief Method invoked during creating new script file.
	*/
	void newFile();
	/**
		\brief Method invoked during importing scripts.
	*/
	void importScripts();
	/**
		\brief Method invoked during sacing script.
	*/
	void saveScript();
	/**
		\brief Method invoked when the program is 'sent' to tray.
	*/
	void toTray();
	/**
		\brief Method invoked during parsing the script code.
	*/
	void parseScript();
	/**
		\brief Runs script code from the text box.
		\param[in] onlyParse If set to true, the method only parses the script to check its correctness,
		otherwise it also tries to run the script. Use the mainWin::parseScript method if you want to only parse the script.
	*/
	void runScript( bool onlyParse = false );
	/**
		\brief Method invoked during removing a script from the list (the script is removed from the HD as well).
	*/
	void removeScript();
	/**
		\brief Method invoked during selecting a script on the scripts list.
		\param[in] scriptTitle Text of the selected script (not the code).
	*/
	void scriptSelected( const QString& scriptTitle );
	/**
		\brief Method invoked during modifying code of the selected script.
	*/
	void scriptModified();
	/**
		\brief Method invoked during clicking on add action feature.
	*/
	void addAction();
	/**
		\brief Shows 'about' dialog.
	*/
	void showAbout();
	/**
		\brief Method invoked during selection of the action in the actions list (not in the calendar!).
	*/
	void actionSelected( QTableWidgetItem* item );
	/**
		\brief Method invoked during clicking on the detach feature.
	*/
	void detachAction();
	/**
		\brief Method invoked during clicking on the remove feature.
	*/
	void removeAction();
	/**
		\brief Method invoked during editing an action.
	*/
	void editAction();
	/**
		\brief Method invoked while saving the actions into the database.
	*/
	void saveData();
	/**
		\brief Moves currently selected action up.
	*/
	void moveUp();
	/**
		\brief Moves currently selected action down.
	*/
	void moveDown();
	/**
		\brief Moves currently selected action left.
	*/
	void moveLeft();
	/**
		\brief Moves currently selected action right.
	*/
	void moveRight();
	/**
		\brief Restores main window (used while the program is in tray).
	*/
	void openApp();
	/**
		\brief Terminates the program previously removing tray icon..
	*/
	void quitApp();

private:
	/**
		\brief Initializes all api functions for the scripts.
	*/
	void initLuaApi();
	/**
		\brief Initializes tray system with the context menu.
		\param[in] tray Tray system to which we set the context menu.
	*/
	void initTraySystem( TraySystem* tray );
	/**
		\brief Gets function name from the error message from the lua engine library (not from the LuaEngine class).
		\param[in] textError Error message from the lua engine library.
	*/
	QString getFuncName( QString textError );
	/**
		\brief Helper function for checking if the date is not old (used with adding actions to the calendar).
		\param[in] date Date to check.
		\retval True if the date is not old.
		\retval False if the date is already in the past.
	*/
	bool checkDateCorrectness( QDate date );
	/**
		\return Time (in milliseconds) that need to elapse to the next day (used with mainWin::m_updater).
	*/
	int calcTimeForNewDay() const;
	/**
		\brief Method invoked while closing the main window.
	*/
	void closeEvent( QCloseEvent* e );

};