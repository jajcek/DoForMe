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

	QMap<QString, Script*> m_scripts;

public:
	mainWin(QWidget *parent = 0, Qt::WFlags flags = 0);
	~mainWin();

	void loadScripts( const QString& path );

public slots:
	void browseScript();
	void runAction();
	void saveAction();
	void saveAsAction();
	void addAction();
	void scriptModified();
	void showAbout();
	void newFile();

private:
	void initLuaApi();
	void saveToFile( QString path, QString code );
	void getDataForAction();
	QString getFuncName( QString textError );
	void setCode( const QString& );

};