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