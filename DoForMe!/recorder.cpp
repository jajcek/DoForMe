#include "recorder.h"

HHOOK Recorder::m_mouseHook = NULL;
QTextEdit* Recorder::m_textEdit = NULL;

void Recorder::startRecording() {
	m_mouseHook = SetWindowsHookEx( WH_MOUSE_LL, &mouseHook, GetModuleHandle( NULL ), 0 );
}

void Recorder::setTextEdit( QTextEdit* textEdit ) {
	m_textEdit = textEdit;
}

LRESULT CALLBACK Recorder::mouseHook( int code, WPARAM wParam, LPARAM lParam ) {
     if( code < 0 )
		 return CallNextHookEx( m_mouseHook, code, wParam, lParam );   
 
     switch( wParam ) {
		case WM_LBUTTONDOWN:
			//putCmd( "leftDown(" + QString::number( GET_X_LPARAM( lParam ) ) + ", " + QString::number( GET_Y_LPARAM( lParam ) ) + ")" );
			qDebug( "%d", GET_X_LPARAM( lParam ) );
			break;
		case WM_LBUTTONUP:
			putCmd( QString( "leftUp(" ) + LOWORD( wParam ) + ", " + HIWORD( wParam ) + ")" );
			break;
	 }
 
     return CallNextHookEx( 0, code, wParam, lParam );
}

void Recorder::putCmd( QString cmd ) {
	m_textEdit->append( cmd );
}