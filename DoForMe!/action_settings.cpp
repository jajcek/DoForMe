#include "action_settings.h"

const int ActionSettings::MONDAY = 1;
const int ActionSettings::TUESDAY = 1 << 1;
const int ActionSettings::WEDNESDAY = 1 << 2;
const int ActionSettings::THURSDAY = 1 << 3;
const int ActionSettings::FRIDAY = 1 << 4;
const int ActionSettings::SATURDAY = 1 << 5;
const int ActionSettings::SUNDAY = 1 << 6;

int ActionSettings::checkTimeCorrectness() {
	QDate _currentDate = QDate::currentDate();
	QTime _currentTime = QTime::currentTime();

	// check if the time set is older or equal to the current time
	if( m_selectedDate == _currentDate ) {
		if( _currentTime >= QTime( getHours(), getMinutes(), getSeconds() ) ) {
			return OLD;
		}
	}

	return OK;
}

ActionSettings::ActionSettings() : m_selectedDate( QDate::currentDate() ) {
	ui.setupUi( this );

	connect( ui.applyButton, SIGNAL( clicked() ), this, SLOT( apply() ) );

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

void ActionSettings::setHours( int hours ) {
	ui.hourSpin->setValue( hours );
}

int ActionSettings::getHours() const {
	return ui.hourSpin->value();
}

void ActionSettings::setMinutes( int minutes ) {
	ui.minSpin->setValue( minutes );
}

int ActionSettings::getMinutes() const {
	return ui.minSpin->value();
}

void ActionSettings::setSeconds( int seconds ) {
	ui.secSpin->setValue( seconds );
}

int ActionSettings::getSeconds() const {
	return ui.secSpin->value();
}

void ActionSettings::setIsXDays( bool isXDays ) {
	ui.runEveryXDaysCheck->setChecked( isXDays );
}

bool ActionSettings::isXDays() const {
	return ui.runEveryXDaysCheck->isChecked();
}

void ActionSettings::setXDays( int days ) {
	ui.daysSpin->setValue( days );
}

int ActionSettings::getXDays() const {
	return ui.daysSpin->value();
}

void ActionSettings::setDaysFlags( int mask ) {
	if( mask & MONDAY )
		ui.mondayCheck->setChecked( true );
	if( mask & TUESDAY )
		ui.tuesdayCheck->setChecked( true );
	if( mask & WEDNESDAY )
		ui.wednesdayCheck->setChecked( true );
	if( mask & THURSDAY )
		ui.thursdayCheck->setChecked( true );
	if( mask & FRIDAY )
		ui.fridayCheck->setChecked( true );
	if( mask & SATURDAY )
		ui.saturdayCheck->setChecked( true );
	if( mask & SUNDAY )
		ui.sundayCheck->setChecked( true );
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
	int _result = checkTimeCorrectness();
	switch( _result ) {
		case OLD: {
			QMessageBox _msg( QMessageBox::Information, "Information", "The time passed already. Do you still want to continue?",
				QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel );
			int _result = _msg.exec();
			if( _result == QMessageBox::Cancel )
				return;
			else if( _result == QMessageBox::No )
				reject();
			else
				accept();
		}
		case OK:
			accept();
	}
}