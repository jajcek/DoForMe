#include "action_settings_dialog.h"

ActionSettingsDialog::ActionSettingsDialog() {
	ui.setupUi( this );

	// make the dialog on the middle of screen
	QDesktopWidget screen;
	setGeometry( ( screen.width() - width() ) / 2, ( screen.height() - height() ) / 2, width(), height() );

	/*
		apply and cancel buntton actions are defined in QT Designer!
	*/
}

int ActionSettingsDialog::getHours() const {
	return ui.hourSpin->value();
}

int ActionSettingsDialog::getMinutes() const {
	return ui.minSpin->value();
}

int ActionSettingsDialog::getSeconds() const {
	return ui.secSpin->value();
}

bool ActionSettingsDialog::isXDays() const {
	return ui.runEveryXDaysCheck->isChecked();
}

int ActionSettingsDialog::getXDays() const {
	return ui.daysSpin->value();
}

int ActionSettingsDialog::getDays() const {
	int _daysMask = 0;

	if( ui.mondayCheck->isChecked() )
		_daysMask |= DAYS::MONDAY;
	if( ui.tuesdayCheck->isChecked() )
		_daysMask |= DAYS::TUESDAY;
	if( ui.wednesdayCheck->isChecked() )
		_daysMask |= DAYS::WEDNESDAY;
	if( ui.thursdayCheck->isChecked() )
		_daysMask |= DAYS::THURSDAY;
	if( ui.fridayCheck->isChecked() )
		_daysMask |= DAYS::FRIDAY;
	if( ui.saturdayCheck->isChecked() )
		_daysMask |= DAYS::SATURDAY;
	if( ui.sundayCheck->isChecked() )
		_daysMask |= DAYS::SUNDAY;

	return _daysMask;
}