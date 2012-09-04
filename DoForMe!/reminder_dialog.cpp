#include "reminder_dialog.h"

ReminderDialog* ReminderDialog::m_object = NULL;

ReminderDialog::ReminderDialog() {
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

void ReminderDialog::browseSound() {
	QString _fileName = QFileDialog::getOpenFileName( this, "Choose sound supported by your system.",
														 "C:/", "Sound files supported by your OS (*.*)" );
	ui.soundPathEdit->setText( _fileName );
}

void ReminderDialog::playSound() {
	qDebug( "ReminderDialog::playSound" );

	// stop the previous sound to play another (or the same from beginning)
	stopSound();
	m_sound = Phonon::createPlayer( Phonon::MusicCategory, Phonon::MediaSource( ui.soundPathEdit->text() ) );
	m_sound->play();
}

void ReminderDialog::pressedOk() {
	m_bIsOn = ui.signalCheck->isChecked();
	m_fTimeEarlier = ui.signalSpinBox->value();
	m_bIsSoundOn = ui.soundCheck->isChecked();
	m_strSoundPath = ui.soundPathEdit->text();

	stopSound();

	accept();
}

void ReminderDialog::pressedCancel() {
	// set previous values to controls
	ui.signalCheck->setChecked( m_bIsOn );
	ui.signalSpinBox->setValue( m_fTimeEarlier );
	ui.soundCheck->setChecked( m_bIsSoundOn );
	ui.soundPathEdit->setText( m_strSoundPath );

	stopSound();

	reject();
}

void ReminderDialog::signalUnchecked() {
	if( !ui.signalCheck->isChecked() )
		ui.soundCheck->setChecked( false );
}

ReminderDialog* ReminderDialog::getInstance() {
	if( !m_object )
		m_object = new ReminderDialog();

	return m_object;
}

bool ReminderDialog::isOn() const {
	return m_bIsOn;
}

int ReminderDialog::timeEarlier() const {
	if( m_bIsOn )
		return m_fTimeEarlier;
	else
		return 0;
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

void ReminderDialog::stopSound() {
	m_sound->stop();
}

void ReminderDialog::soundChecked() {
	ui.signalCheck->setChecked( true );
}

void ReminderDialog::closeEvent( QCloseEvent* e ) {
	stopSound();
}