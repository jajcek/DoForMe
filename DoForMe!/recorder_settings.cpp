#include "recorder_settings.h"

RecorderSettings* RecorderSettings::m_object = NULL;

RecorderSettings::RecorderSettings() {
	ui.setupUi( this );
}

RecorderSettings* RecorderSettings::getInstance() {
	if( !m_object )
		m_object = new RecorderSettings();

	return m_object;
}

bool RecorderSettings::isMouseOn() const {
	return ui.mouseCheck->isChecked();
}

bool RecorderSettings::isKeyboardOn() const {
	return ui.keyboardCheck->isChecked();
}