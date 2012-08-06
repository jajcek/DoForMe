#pragma once

#include <qdialog.h>
#include <qdesktopwidget.h>
#include <qicon.h>
#include "ui_action_dialog.h"


class ActionSettings : public QDialog {
private:
	Ui::actionSettingsDialog ui;

public:
	static const int MONDAY;
	static const int TUESDAY;
	static const int WEDNESDAY;
	static const int THURSDAY;
	static const int FRIDAY;
	static const int SATURDAY;
	static const int SUNDAY;

public:
	ActionSettings();

	int getHours() const;
	int getMinutes() const;
	int getSeconds() const;

	bool isXDays() const;
	int getXDays() const;

	int getDays() const;
};