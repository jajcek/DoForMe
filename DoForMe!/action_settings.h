#pragma once

#include <qdialog.h>
#include <qdesktopwidget.h>
#include <qicon.h>
#include <qdatetime.h>
#include <qmessagebox.h>
#include <qtablewidget.h>
#include "ui_action_dialog.h"
#include "lua_engine.h"
#include "scripts_manager.h"

class ActionSettings : public QDialog {
	Q_OBJECT

private:
	Ui::actionSettingsDialog ui;
	QDate m_selectedDate;

	enum { OLD = 0, OK };

public:
	static const int MONDAY;
	static const int TUESDAY;
	static const int WEDNESDAY;
	static const int THURSDAY;
	static const int FRIDAY;
	static const int SATURDAY;
	static const int SUNDAY;

private:
	int checkTimeCorrectness();

public:
	ActionSettings();
	ActionSettings( QDate date );

	void setScripts( const QStringList& scripts );
	QString getScriptName() const;
	void selectScript( const QString& scriptName );

	void setHours( int hours );
	int getHours() const;
	void setMinutes( int minutes );
	int getMinutes() const;
	void setSeconds( int seconds );
	int getSeconds() const;

	void setIsXDays( bool isXDays );
	bool isXDays() const;
	void setXDays( int days );
	int getXDays() const;

	void setDaysFlags( int mask );
	int getDays() const;

public slots:
	void apply();

};