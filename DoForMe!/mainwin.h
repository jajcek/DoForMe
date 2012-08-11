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

class mainWin : public QMainWindow
{
	Q_OBJECT

private:
	Ui::mainWinClass ui;
	unsigned m_iWidth;
	unsigned m_iHeight;

	ActionsCalendar* m_calendar;
	LuaEngine* m_lua;
	Script* m_pCurrScript;

public:
	mainWin(QWidget *parent = 0, Qt::WFlags flags = 0);
	~mainWin();

	void loadScripts( const QString& path );

public slots:
	void newFile();
	void runAction();
	void saveScript();
	void saveAction();
	void scriptSelected( const QString& scriptTitle );
	void scriptModified();
	void addAction();
	void showAbout();
	void actionSelected( QTableWidgetItem* item );
	void detachAction();

private:
	void initLuaApi();
	void getDataForAction();
	QString getFuncName( QString textError );
	void setScriptTitle( QString title );
	void setCode( const QString& );
	bool checkDateCorrectness( QDate date );

};