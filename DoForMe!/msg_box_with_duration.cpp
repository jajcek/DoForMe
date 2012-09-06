#include "msg_box_with_duration.h"

MsgBoxWithDuration::MsgBoxWithDuration( const QString strTitle, const QString strMessage, const int iWinDuration )
: m_iWinDuration( iWinDuration ), m_strTitle( strTitle ), m_strMessage( strMessage ), m_buttonClicked( -1 ) {
	ui.setupUi( this );

	setWindowTitle( m_strTitle );
	// disable close button
	setWindowFlags(Qt::Dialog | Qt::Desktop | Qt::WindowStaysOnTopHint );

	connect( ui.runButton, SIGNAL( clicked() ), this, SLOT( run() ) );
	connect( ui.suspendButton, SIGNAL( clicked() ), this, SLOT( suspend() ) );
	connect( ui.ignoreButton, SIGNAL( clicked() ), this, SLOT( ignore() ) );

	startTime();
}

void MsgBoxWithDuration::stopTime() {
	ReminderSettings::getInstance()->stopSound();
	m_timer.stop();
	ui.textMessage->setText( m_strMessage );
	ui.suspendButton->setEnabled( false );
	ui.suspendButton->setText( "Suspended" );
}

void MsgBoxWithDuration::startTime() {
	if( ReminderSettings::getInstance()->isSoundOn() )
		ReminderSettings::getInstance()->playSound();
	m_timer.start( 1000, this );
	updateTime();
}

int MsgBoxWithDuration::buttonClicked() const {
	return m_buttonClicked;
}

void MsgBoxWithDuration::run() {
	m_buttonClicked = RUN;
	ReminderSettings::getInstance()->stopSound();
	close();
}

void MsgBoxWithDuration::suspend() {
	m_buttonClicked = SUSPEND;
	stopTime();
}

void MsgBoxWithDuration::ignore() {
	m_buttonClicked = IGNORING;
	ReminderSettings::getInstance()->stopSound();
	close();
}

void MsgBoxWithDuration::timerEvent( QTimerEvent* e ) {
	if( m_iWinDuration == 1 ) {
		// time has elapsed - stop the timer and sound (if on) and close the dialog
		stopTime();
		close();
	} else {
		--m_iWinDuration;
		updateTime();
	}
}

void MsgBoxWithDuration::updateTime() {
	ui.textMessage->setText( m_strMessage + "\n\nRunning action in " + QString::number( m_iWinDuration ) + " seconds." );
}