#include "msg_box_with_duration.h"

MsgBoxWithDuration::MsgBoxWithDuration( const QString strTitle, const QString strMessage, const int iWinDuration )
: m_iWinDuration( iWinDuration ), m_strTitle( strTitle ), m_strMessage( strMessage ), m_buttonClicked( -1 ) {
	setWindowTitle( m_strTitle );
	// disable close button
	setWindowFlags(Qt::Dialog | Qt::Desktop | Qt::WindowStaysOnTopHint );

	// create text message
	int _width = 300;
	int _height = 120;
	setMinimumWidth( _width );
	setMaximumWidth( _width );
	setMinimumHeight( _height );
	setMaximumHeight( _height );

	// define elements of the dialog
	//QPixmap _pixmap = 
	m_pixmap.setPixmap( QPixmap( ":/mainWin/Resources/actionicon.png" ).scaled( 50, 50 ) );
	m_textLabel.setText( m_strMessage );
	m_runButton.setText( "Run" );
	m_suspendButton.setText( "Suspend" );
	m_ignoreButton.setText( "Ignore" );

	// connect signal to the buttons
	connect( &m_runButton, SIGNAL( clicked() ), this, SLOT( run() ) );
	connect( &m_suspendButton, SIGNAL( clicked() ), this, SLOT( suspend() ) );
	connect( &m_ignoreButton, SIGNAL( clicked() ), this, SLOT( ignore() ) );

	// add widgets to the layout
	_imageTextLay.addWidget( &m_pixmap );
	_imageTextLay.addWidget( &m_textLabel );
	_buttonsLay.addWidget( &m_runButton );
	_buttonsLay.addWidget( &m_suspendButton );
	_buttonsLay.addWidget( &m_ignoreButton );

	// add layout as a child layout
	_VLay.addLayout( &_imageTextLay );
	_VLay.addLayout( &_buttonsLay );

	setLayout( &_VLay );

	startTime();
}

void MsgBoxWithDuration::stopTime() {
	ReminderDialog::getInstance()->stopSound();
	m_timer.stop();
	m_textLabel.setText( m_strMessage );
}

void MsgBoxWithDuration::startTime() {
	if( ReminderDialog::getInstance()->isSoundOn() )
		ReminderDialog::getInstance()->playSound();
	m_timer.start( 1000, this );
	updateTime();
}

int MsgBoxWithDuration::buttonClicked() const {
	return m_buttonClicked;
}

void MsgBoxWithDuration::run() {
	m_buttonClicked = RUN;
	ReminderDialog::getInstance()->stopSound();
	close();
}

void MsgBoxWithDuration::suspend() {
	m_buttonClicked = SUSPEND;
	stopTime();
}

void MsgBoxWithDuration::ignore() {
	m_buttonClicked = IGNORING;
	ReminderDialog::getInstance()->stopSound();
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
	m_textLabel.setText( m_strMessage + "\n\nRunning action in " + QString::number( m_iWinDuration ) + " seconds." );
}