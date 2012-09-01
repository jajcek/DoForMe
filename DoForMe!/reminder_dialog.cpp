#include "reminder_dialog.h"

ReminderDialog* ReminderDialog::m_object = NULL;

ReminderDialog::ReminderDialog() : m_bIsOn( ui.signalCheck->isChecked() ), m_fTimeEarlier( ui.signalSpinBox->value() ),
								   m_bIsMsgOn( ui.msgCheck->isChecked() ), m_iMsgDuration( ui.msgDurationSpinBox->value() ),
								   m_bIsSoundOn( ui.soundCheck->isChecked() ), m_strSoundPath( ui.soundPathEdit->text() ) {
	ui.setupUi( this );

	connect( ui.okButton, SIGNAL( clicked() ), this, SLOT( pressedOk() ) );
}

void ReminderDialog::pressedOk() {
	m_bIsOn = ui.signalCheck->isChecked();
	m_fTimeEarlier = ui.signalSpinBox->value();
	m_bIsMsgOn = ui.msgCheck->isChecked();
	m_iMsgDuration = ui.msgDurationSpinBox->value();
	m_bIsSoundOn = ui.soundCheck->isChecked();
	m_strSoundPath = ui.soundPathEdit->text();

	accept();
}

ReminderDialog* ReminderDialog::getInstance() {
	if( !m_object )
		m_object = new ReminderDialog();

	return m_object;
}

bool ReminderDialog::isOn() const {
	return m_bIsOn;
}

float ReminderDialog::timeEarlier() const {
	if( m_bIsOn )
		return m_fTimeEarlier;
	else
		return -1;
}

bool ReminderDialog::isMsgOn() const {
	return m_bIsMsgOn;
}

int ReminderDialog::msgDuration() const {
	if( m_bIsMsgOn )
		return m_iMsgDuration;
	else
		return -1;
}

bool ReminderDialog::isSoundOn() const {
	return m_bIsSoundOn;
}

QString ReminderDialog::soundPath() const {
	if( m_bIsSoundOn )
		return m_strSoundPath;
	else
		return "";
}