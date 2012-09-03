#include "recorder.h"

HHOOK Recorder::m_mouseHook = NULL;
QTextEdit* Recorder::m_textEdit = NULL;
QElapsedTimer* Recorder::m_timer = NULL;

void Recorder::startRecording() {
	m_mouseHook = SetWindowsHookEx( WH_MOUSE_LL, &mouseHook, GetModuleHandle( NULL ), 0 );
	m_timer = new QElapsedTimer();
	m_timer->start();
}

void Recorder::stopRecording() {
	UnhookWindowsHookEx( m_mouseHook );
	m_mouseHook = NULL;
	delete m_timer;
	m_timer = NULL;
}

void Recorder::setTextEdit( QTextEdit* textEdit ) {
	m_textEdit = textEdit;
}

LRESULT CALLBACK Recorder::mouseHook( int code, WPARAM wParam, LPARAM lParam ) {
	if( code < 0 )
		return CallNextHookEx( m_mouseHook, code, wParam, lParam );   

	// prepare coordinates of the mouse cursor
	POINT pt = reinterpret_cast<MSLLHOOKSTRUCT*>( lParam )->pt;
	QString _x = QString::number( pt.x );
	QString _y = QString::number( pt.y );
	switch( wParam ) {
		case WM_LBUTTONDOWN:
			putCmd( "leftDownAt(" + _x + ", " + _y + ")" );
			break;
		case WM_LBUTTONUP:
			putCmd( "leftUpAt(" + _x + ", " + _y + ")" );
			break;
		case WM_RBUTTONDOWN:
			putCmd( "rightDownAt(" + _x + ", " + _y + ")" );
			break;
		case WM_RBUTTONUP:
			putCmd( "rightUpAt(" + _x + ", " + _y + ")" );
			break;
		case WM_MBUTTONDOWN:
			putCmd( "middleDownAt(" + _x + ", " + _y + ")" );
			break;
		case WM_MBUTTONUP:
			putCmd( "middleUpAt(" + _x + ", " + _y + ")" );
			break;
	}
 
	return CallNextHookEx( 0, code, wParam, lParam );
}

void Recorder::putCmd( QString cmd ) {
	int _elapsedMilliseconds = m_timer->elapsed();
	m_timer->restart();
	QString _sleepCmd = "sleep(" + QString::number( _elapsedMilliseconds ) + ")";
	m_textEdit->append( _sleepCmd );
	m_textEdit->append( cmd );
}