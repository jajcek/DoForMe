#include "recorder.h"

HHOOK Recorder::m_mouseHook = NULL;
HHOOK Recorder::m_keyboardHook = NULL;
QTextEdit* Recorder::m_textEdit = NULL;
QElapsedTimer* Recorder::m_timer = NULL;
QMap<int, bool> Recorder::m_keys;

void Recorder::startRecording() {
	// set hooks
	if( RecorderSettings::getInstance()->isMouseOn() )
		m_mouseHook = SetWindowsHookEx( WH_MOUSE_LL, &mouseHookProcedure, GetModuleHandle( NULL ), 0 );
	if( RecorderSettings::getInstance()->isKeyboardOn() )
		m_keyboardHook = SetWindowsHookEx( WH_KEYBOARD_LL, &keyboardHookProcedure, GetModuleHandle( NULL ), 0 );

	// start calculating elapsed time
	m_timer = new QElapsedTimer();
	m_timer->start();
}

void Recorder::stopRecording() {
	UnhookWindowsHookEx( m_mouseHook );
	UnhookWindowsHookEx( m_keyboardHook );
	m_mouseHook = NULL;
	m_keyboardHook = NULL;
	delete m_timer;
	m_timer = NULL;
}

void Recorder::setTextEdit( QTextEdit* textEdit ) {
	m_textEdit = textEdit;
}

LRESULT CALLBACK Recorder::mouseHookProcedure( int code, WPARAM wParam, LPARAM lParam ) {
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

LRESULT CALLBACK Recorder::keyboardHookProcedure( int code, WPARAM wParam, LPARAM lParam ) {
	if( code < 0 )
		return CallNextHookEx( m_mouseHook, code, wParam, lParam );   

	DWORD _vkCode = reinterpret_cast<KBDLLHOOKSTRUCT*>( lParam )->vkCode;
	DWORD _isAltOn = reinterpret_cast<KBDLLHOOKSTRUCT*>( lParam )->flags & LLKHF_ALTDOWN;

	QString _symbol = "";
	if( _vkCode >= 65 && _vkCode <= 90 )
		_symbol = ( char )( _vkCode + 32 );
	else
		_symbol = ( char )_vkCode;

	//qDebug( "code: %d, alt: %d, wparam: %d, lparam: %d", _vkCode, _isAltOn, wParam, lParam );
	if( GetAsyncKeyState( VK_RSHIFT ) && !m_keys[VK_RSHIFT] ) {
		m_keys[VK_RSHIFT] = true;
		putCmd( "sendText( \"{rshift+}\" )" );
	}
	if( GetAsyncKeyState( VK_LSHIFT ) && !m_keys[VK_LSHIFT] ) {
		m_keys[VK_LSHIFT] = true;
		putCmd( "sendText( \"{lshift+}\" )" );
	}
	if( GetAsyncKeyState( VK_RMENU ) && !m_keys[VK_RMENU] ) {
		m_keys[VK_RMENU] = true;
		putCmd( "sendText( \"{ralt+}\" )" );
	}
	if( GetAsyncKeyState( VK_LMENU ) && !m_keys[VK_LMENU] ) {
		m_keys[VK_LMENU] = true;
		putCmd( "sendText( \"{lalt+}\" )" );
	}
	if( GetAsyncKeyState( VK_RCONTROL ) && !m_keys[VK_RCONTROL] ) {
		m_keys[VK_RCONTROL] = true;
		putCmd( "sendText( \"{rctrl+}\" )" );
	}
	if( GetAsyncKeyState( VK_LCONTROL ) && !m_keys[VK_LCONTROL] ) {
		m_keys[VK_LCONTROL] = true;
		putCmd( "sendText( \"{lctrl+}\" )" );
	}

	if( wParam != WM_KEYUP ) {
		QString _strKey = LuaApiEngine::getStringKey( _vkCode ).c_str();
		if( _vkCode == VK_OEM_4 )
			putCmd( "sendText( \"[\" )" );
		else if( _vkCode == VK_OEM_6 )
			putCmd( "sendText( \"]\" )" );
		else if( _vkCode == VK_OEM_5 )
			putCmd( "sendText( \"\\\\\" )" );
		else if( _vkCode == VK_OEM_1 )
			putCmd( "sendText( \";\" )" );
		else if( _vkCode == VK_OEM_7 )
			putCmd( "sendText( \";\" )" );
		else if( _vkCode == VK_OEM_3 )
			putCmd( "sendText( \"`\" )" );
		else if( _vkCode == VK_OEM_COMMA )
			putCmd( "sendText( \",\" )" );
		else if( _vkCode == VK_OEM_PERIOD )
			putCmd( "sendText( \".\" )" );
		else if( _vkCode == VK_OEM_2 )
			putCmd( "sendText( \"/\" )" );
		else if( _vkCode == VK_OEM_MINUS )
			putCmd( "sendText( \"-\" )" );
		else if( _vkCode == VK_OEM_PLUS )
			putCmd( "sendText( \"+\" )" );
		else if( _strKey != "" && ( _vkCode != VK_RSHIFT ) && ( _vkCode != VK_LSHIFT ) && ( _vkCode != VK_RMENU ) &&
							 ( _vkCode != VK_LMENU ) && ( _vkCode != VK_RCONTROL ) && ( _vkCode != VK_LCONTROL )) {

			putCmd( "sendText( \"{" + _strKey + "}\" )" );
		}
		if( ( _vkCode >= 65 && _vkCode <= 90 ) || ( _vkCode >= 48 && _vkCode <= 57 ) || _vkCode == VK_SPACE )
			putCmd( "sendText( \"" + _symbol + "\" )" );
	}

	switch( wParam ) {
		case WM_KEYUP:
			if( _vkCode == VK_RSHIFT ) {
				putCmd( "sendText( \"{rshift-}\" )" );
				m_keys[VK_RSHIFT] = false;
			} else if( _vkCode == VK_LSHIFT ) {
				putCmd( "sendText( \"{lshift-}\" )" );
				m_keys[VK_LSHIFT] = false;
			} else if( _vkCode == VK_RMENU ) {
				putCmd( "sendText( \"{ralt-}\" )" );
				m_keys[VK_RMENU] = false;
			} else if( _vkCode == VK_LMENU ) {
				putCmd( "sendText( \"{lalt-}\" )" );
				m_keys[VK_LMENU] = false;
			} else if( _vkCode == VK_RCONTROL ) {
				putCmd( "sendText( \"{rctrl-}\" )" );
				m_keys[VK_RCONTROL] = false;
			} else if( _vkCode == VK_LCONTROL ) {
				putCmd( "sendText( \"{lctrl-}\" )" );
				m_keys[VK_LCONTROL] = false;
			}
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