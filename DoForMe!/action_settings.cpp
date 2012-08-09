#include "action_settings.h"

const int ActionSettings::MONDAY = 1;
const int ActionSettings::TUESDAY = 1 << 1;
const int ActionSettings::WEDNESDAY = 1 << 2;
const int ActionSettings::THURSDAY = 1 << 3;
const int ActionSettings::FRIDAY = 1 << 4;
const int ActionSettings::SATURDAY = 1 << 5;
const int ActionSettings::SUNDAY = 1 << 6;

bool ActionSettings::checkTimeCorrectness() {
	QDate _currentDate = QDate::currentDate();
	QTime _currentTime = QTime::currentTime();

	if( m_selectedDate == _currentDate ) {
		if( _currentTime >= QTime( getHours(), getMinutes(), getSeconds() ) ) {
			return false;
		}
	}

	return true;
}

ActionSettings::ActionSettings() : m_selectedDate( QDate::currentDate() ) {
	ui.setupUi( this );

	connect( ui.applyButton, SIGNAL( CLICKED() ), this, SLOT( apply() ) );

	// make the dialog on the middle of screen
	QDesktopWidget screen;
	setGeometry( ( screen.width() - width() ) / 2, ( screen.height() - height() ) / 2, width(), height() );

	/*
		cancel button action is defined in QT Designer!
	*/
}

ActionSettings::ActionSettings( QDate date ) : m_selectedDate( date ) {
	ui.setupUi( this );

	connect( ui.applyButton, SIGNAL( clicked() ), this, SLOT( apply() ) );

	// make the dialog on the middle of screen
	QDesktopWidget screen;
	setGeometry( ( screen.width() - width() ) / 2, ( screen.height() - height() ) / 2, width(), height() );

	/*
		cancel button action is defined in QT Designer!
	*/
}

int ActionSettings::getHours() const {
	return ui.hourSpin->value();
}

int ActionSettings::getMinutes() const {
	return ui.minSpin->value();
}

int ActionSettings::getSeconds() const {
	return ui.secSpin->value();
}

bool ActionSettings::isXDays() const {
	return ui.runEveryXDaysCheck->isChecked();
}

int ActionSettings::getXDays() const {
	return ui.daysSpin->value();
}

int ActionSettings::getDays() const {
	int _daysMask = 0;

	if( ui.mondayCheck->isChecked() )
		_daysMask |= MONDAY;
	if( ui.tuesdayCheck->isChecked() )
		_daysMask |= TUESDAY;
	if( ui.wednesdayCheck->isChecked() )
		_daysMask |= WEDNESDAY;
	if( ui.thursdayCheck->isChecked() )
		_daysMask |= THURSDAY;
	if( ui.fridayCheck->isChecked() )
		_daysMask |= FRIDAY;
	if( ui.saturdayCheck->isChecked() )
		_daysMask |= SATURDAY;
	if( ui.sundayCheck->isChecked() )
		_daysMask |= SUNDAY;

	return _daysMask;
}

void ActionSettings::apply() {
	// inform user that the time passed already
	if( !checkTimeCorrectness() ) {
		QMessageBox _msg( QMessageBox::Information, "Information", "The time passed already. Do you still want to add the action?",
			QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel );
		int _result = _msg.exec();
		if( _result == QMessageBox::Cancel )
			return;
		else if( _result == QMessageBox::No )
			reject();
		else
			accept();
	}
}