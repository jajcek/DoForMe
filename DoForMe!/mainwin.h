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

class mainWin : public QMainWindow
{
	Q_OBJECT

private:
	Ui::mainWinClass ui;

	ActionsCalendar* m_calendar;
	Script* m_pCurrScript;
	TraySystem* m_tray;
	QBasicTimer m_updater;

public:
	mainWin(QWidget *parent = 0, Qt::WFlags flags = 0);
	~mainWin();

	void loadScripts( const QString& path );
	QString getCode() const;
	void setCode( const QString& );
	void setScriptTitle( QString title );
	void timerEvent( QTimerEvent* e );

public slots:
	void newFile();
	void importScripts();
	void saveScript();
	void toTray();
	void runScript( bool onlyParse = false );
	void removeScript();
	void scriptSelected( const QString& scriptTitle );
	void scriptModified();
	void addAction();
	void showAbout();
	void actionSelected( QTableWidgetItem* item );
	void detachAction();
	void removeAction();
	void editAction();
	void saveData();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void openApp();
	void quitApp();

private:
	void initLuaApi();
	void initTraySystem( TraySystem* tray );
	QString getFuncName( QString textError );
	bool checkDateCorrectness( QDate date );
	int calcTimeForNewDay() const;
	void closeEvent( QCloseEvent* e );

};