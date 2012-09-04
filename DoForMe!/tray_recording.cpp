#include "tray_recording.h"

void TrayRecording::setIcon( QString path ) {
	QSystemTrayIcon::setIcon( QPixmap( path ) );
	m_iconPath = path;
}

void TrayRecording::start() {
	m_isOn = true;
	m_timer.start( 500, this );
}

void TrayRecording::timerEvent( QTimerEvent* e ) {
	if( m_isOn ) {
		QSystemTrayIcon::setIcon( QPixmap( "" ) );
		m_isOn = false;
	} else {
		QSystemTrayIcon::setIcon( QPixmap( m_iconPath ) );
		m_isOn = true;
	}
}