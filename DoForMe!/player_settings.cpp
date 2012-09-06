#include "player_settings.h"

PlayerSettings* PlayerSettings::m_object = NULL;

PlayerSettings::PlayerSettings() {
	ui.setupUi( this );

	m_iDelay = ui.delaySpinBox->value();

	connect( ui.okButton, SIGNAL( clicked() ), this, SLOT( pressedOk() ) );
	connect( ui.cancelButton, SIGNAL( clicked() ), this, SLOT( pressedCancel() ) );
}

PlayerSettings* PlayerSettings::getInstance() {
	if( !m_object )
		m_object = new PlayerSettings();

	return m_object;
}

int PlayerSettings::delay() const {
	return m_iDelay;
}

void PlayerSettings::setDelay( int delay ) {
	m_iDelay = delay;
	ui.delaySpinBox->setValue( delay );
}

void PlayerSettings::pressedOk() {
	m_iDelay = ui.delaySpinBox->value();

	accept();
}

void PlayerSettings::pressedCancel() {
	ui.delaySpinBox->setValue( m_iDelay );

	reject();
}