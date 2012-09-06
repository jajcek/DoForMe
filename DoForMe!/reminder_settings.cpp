#include "reminder_settings.h"

ReminderSettings* ReminderSettings::m_object = NULL;

ReminderSettings::ReminderSettings() {
	ui.setupUi( this );

	// it can't be on initialization list, because the ui.setupUi creates the controls
	m_bIsOn = ui.signalCheck->isChecked();
	m_fTimeEarlier = ui.signalSpinBox->value();
	m_bIsSoundOn = ui.soundCheck->isChecked();
	m_strSoundPath = ui.soundPathEdit->text();

	connect( ui.okButton, SIGNAL( clicked() ), this, SLOT( pressedOk() ) );
	connect( ui.cancelButton, SIGNAL( clicked() ), this, SLOT( pressedCancel() ) );
	connect( ui.browseSoundButton, SIGNAL( clicked() ), this, SLOT( browseSound() ) );
	connect( ui.playSoundButton, SIGNAL( clicked() ), this, SLOT( playSound() ) );
	connect( ui.stopSoundButton, SIGNAL( clicked() ), this, SLOT( stopSound() ) );
	connect( ui.soundCheck, SIGNAL( clicked() ), this, SLOT( soundChecked() ) );
	connect( ui.signalCheck, SIGNAL( clicked() ), this, SLOT( signalUnchecked() ) );

	m_sound = new Phonon::MediaObject( this );
}

void ReminderSettings::browseSound() {
	QString _fileName = QFileDialog::getOpenFileName( this, "Choose sound supported by your system.",
														 "C:/", "Sound files supported by your OS (*.*)" );
	ui.soundPathEdit->setText( _fileName );
}

void ReminderSettings::playSound() {
	qDebug( "ReminderSettings::playSound" );

	// stop the previous sound to play another (or the same from beginning)
	stopSound();
	m_sound = Phonon::createPlayer( Phonon::MusicCategory, Phonon::MediaSource( ui.soundPathEdit->text() ) );
	m_sound->play();
}

void ReminderSettings::pressedOk() {
	m_bIsOn = ui.signalCheck->isChecked();
	m_fTimeEarlier = ui.signalSpinBox->value();
	m_bIsSoundOn = ui.soundCheck->isChecked();
	m_strSoundPath = ui.soundPathEdit->text();

	stopSound();

	accept();
}

void ReminderSettings::pressedCancel() {
	// set previous values to controls
	ui.signalCheck->setChecked( m_bIsOn );
	ui.signalSpinBox->setValue( m_fTimeEarlier );
	ui.soundCheck->setChecked( m_bIsSoundOn );
	ui.soundPathEdit->setText( m_strSoundPath );

	stopSound();

	reject();
}

void ReminderSettings::signalUnchecked() {
	if( !ui.signalCheck->isChecked() )
		ui.soundCheck->setChecked( false );
}

ReminderSettings* ReminderSettings::getInstance() {
	if( !m_object )
		m_object = new ReminderSettings();

	return m_object;
}

bool ReminderSettings::isOn() const {
	return m_bIsOn;
}

int ReminderSettings::timeEarlier() const {
	if( m_bIsOn )
		return m_fTimeEarlier;
	else
		return 0;
}

bool ReminderSettings::isSoundOn() const {
	return m_bIsSoundOn;
}

QString ReminderSettings::soundPath() const {
	if( m_bIsSoundOn )
		return m_strSoundPath;
	else
		return "";
}

void ReminderSettings::stopSound() {
	m_sound->stop();
}

void ReminderSettings::soundChecked() {
	ui.signalCheck->setChecked( true );
}

void ReminderSettings::closeEvent( QCloseEvent* e ) {
	stopSound();
}