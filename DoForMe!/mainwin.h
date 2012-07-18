#pragma once

#include <QFile>
#include <QApplication>
#include <QLabel>
#include <QString>
#include <QTextStream>
#include <qdesktopwidget.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include "ui_mainwin.h"
#include "lua_api.h"
#include "lua_engine.h"
#include "calendar.h"
#include "about_dialog.h"
#include "action.h"

class mainWin : public QMainWindow
{
	Q_OBJECT

private:
	Ui::mainWinClass ui;
	unsigned m_iWidth;
	unsigned m_iHeight;

	static QString APP_NAME;

	DetailedCalendar* m_calendar;
	LuaEngine* m_lua;
	Action* m_currAction;

public:
	mainWin(QWidget *parent = 0, Qt::WFlags flags = 0);
	~mainWin();

public slots:
	void browseScript(); // lepiej zrobic klase Action i tam wrzucac path do skryptu, stan czy zmodyfikowany etc.
	void runAction();
	void saveAction();
	void saveAsAction();
	void scriptModified();
	void showAbout();

private:
	void initLuaApi();
	QString getFuncName( QString textError );

};