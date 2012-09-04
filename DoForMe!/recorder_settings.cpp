#include "recorder_settings.h"

RecorderSettings* RecorderSettings::m_object = NULL;

RecorderSettings::RecorderSettings() {
	ui.setupUi( this );

	// get default values from controls
	m_isMouseOn = ui.mouseCheck->isChecked();
	m_isMouseMoveOn = ui.mouseMoveCheck->isChecked();
	m_isKeyboardOn = ui.keyboardCheck->isChecked();
	m_isTrayOn = ui.trayCheck->isChecked();

	connect( ui.okButton, SIGNAL( clicked() ), this, SLOT( pressedOk() ) );
	connect( ui.cancelButton, SIGNAL( clicked() ), this, SLOT( pressedCancel() ) );
}

RecorderSettings* RecorderSettings::getInstance() {
	if( !m_object )
		m_object = new RecorderSettings();

	return m_object;
}

bool RecorderSettings::isMouseOn() const {
	return m_isMouseOn;
}

bool RecorderSettings::isMouseMoveOn() const {
	return m_isMouseMoveOn;
}

bool RecorderSettings::isKeyboardOn() const {
	return m_isKeyboardOn;
}

bool RecorderSettings::isTrayOn() const {
	return m_isTrayOn;
}

void RecorderSettings::pressedOk() {
	m_isMouseOn = ui.mouseCheck->isChecked();
	m_isMouseMoveOn = ui.mouseMoveCheck->isChecked();
	m_isKeyboardOn = ui.keyboardCheck->isChecked();
	m_isTrayOn = ui.trayCheck->isChecked();

	accept();
}

void RecorderSettings::pressedCancel() {
	ui.mouseCheck->setChecked( m_isMouseOn );
	ui.mouseMoveCheck->setChecked( m_isMouseMoveOn );
	ui.keyboardCheck->setChecked( m_isKeyboardOn );
	ui.trayCheck->setChecked( m_isTrayOn );

	reject();
}