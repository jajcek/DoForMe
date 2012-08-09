#pragma once

#include <qdialog.h>
#include <qdesktopwidget.h>
#include <qicon.h>
#include <qdatetime.h>
#include <qmessagebox.h>
#include "ui_action_dialog.h"


class ActionSettings : public QDialog {
	Q_OBJECT

private:
	Ui::actionSettingsDialog ui;
	QDate m_selectedDate;

public:
	static const int MONDAY;
	static const int TUESDAY;
	static const int WEDNESDAY;
	static const int THURSDAY;
	static const int FRIDAY;
	static const int SATURDAY;
	static const int SUNDAY;

private:
	bool checkTimeCorrectness();

public:
	ActionSettings();
	ActionSettings( QDate date );

	int getHours() const;
	int getMinutes() const;
	int getSeconds() const;

	bool isXDays() const;
	int getXDays() const;

	int getDays() const;

public slots:
	void apply();

};