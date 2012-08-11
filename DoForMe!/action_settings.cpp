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

	// check if there are any actions with the same time
	int _actionsNumber = m_list->rowCount();
	for( int i = 0; i < _actionsNumber; ++i ) {
		int _hours   = m_list->item( i, 1 )->text().left( 2 ).toInt();
		int _minutes = m_list->item( i, 1 )->text().mid( 3, 2 ).toInt();
		int _seconds = m_list->item( i, 1 )->text().mid( 6, 2 ).toInt();

		if( _hours == getHours() && _minutes == getMinutes() && _seconds == getSeconds() ) {
			return EQUAL;
		}
	}

	return OK;
}

ActionSettings::ActionSettings() : m_selectedDate( QDate::currentDate() ), m_list( NULL ) {
	ui.setupUi( this );

	connect( ui.applyButton, SIGNAL( clicked() ), this, SLOT( apply() ) );

	// make the dialog on the middle of screen
	QDesktopWidget screen;
	setGeometry( ( screen.width() - width() ) / 2, ( screen.height() - height() ) / 2, width(), height() );

	/*
		cancel button action is defined in QT Designer!
	*/
}

ActionSettings::ActionSettings( QDate date, QTableWidget* list ) : m_selectedDate( date ), m_list( list ) {
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
	/*int _result = checkTimeCorrectness();
	switch( _result ) {
		case OLD: {
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
		case EQUAL: {
			QMessageBox _msg( QMessageBox::Information, "Information", "An actions with the same time already exists.",
				QMessageBox::Ok );
			_msg.exec();
			return;
		}
		case OK:
			accept();
	}*/
	accept();
}