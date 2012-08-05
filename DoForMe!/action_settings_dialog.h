#pragma once

#include <qdialog.h>
#include <qdesktopwidget.h>
#include <qicon.h>
#include "ui_action_dialog.h"
#include "constants.h"


class ActionSettingsDialog : public QDialog {
private:
	Ui::actionSettingsDialog ui;

public:
	ActionSettingsDialog();

	int getHours() const;
	int getMinutes() const;
	int getSeconds() const;

	bool isXDays() const;
	int getXDays() const;

	int getDays() const;
};