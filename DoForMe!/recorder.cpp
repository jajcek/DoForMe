#include "recorder.h"

HHOOK Recorder::m_mouseHook = NULL;
HHOOK Recorder::m_keyboardHook = NULL;
QTextEdit* Recorder::m_textEdit = NULL;
QElapsedTimer* Recorder::m_timer = NULL;
QMap<int, bool> Recorder::m_keys;
TrayRecording Recorder::m_tray;
QAction* Recorder::m_showMainWindow = NULL;
bool Recorder::m_isScreenSelecting = false;
bool Recorder::m_isRecStopped = true;

void Recorder::startRecording() {
	// set hooks
	//if( RecorderSettings::getInstance()->isMouseOn() )
	m_isRecStopped = false;
	m_mouseHook = SetWindowsHookEx( WH_MOUSE_LL, &mouseHookProcedure, GetModuleHandle( NULL ), 0 );
	//if( RecorderSettings::getInstance()->isKeyboardOn() )
	m_keyboardHook = SetWindowsHookEx( WH_KEYBOARD_LL, &keyboardHookProcedure, GetModuleHandle( NULL ), 0 );

	// start calculating elapsed time
	m_timer = new QElapsedTimer();
	m_timer->start();

	m_tray.setIcon( ":/play_record/Resources/record_on.png" );
	m_tray.show();
	m_tray.start();
}

void Recorder::stopRecording() {
	m_isRecStopped = true;
	delete m_timer;
	m_timer = NULL;

	m_tray.hide();

	// remove unnecessary lines
	if( m_textEdit && RecorderSettings::getInstance()->isKeyboardOn() ) {
		removeXLastLines( 3 );
	} else {
		qDebug( "m_textEdit in Recorder class is a NULL or keyboard hook off" );
	}

	QMessageBox _msg( QMessageBox::Information, "Information", "Recording has been stopped." );
	_msg.exec();

	m_keys[VK_LCONTROL] = false;
	m_keys[VK_LSHIFT] = false;

	if( m_mouseHook ) {
		UnhookWindowsHookEx( m_mouseHook );
		m_mouseHook = NULL;
	}
	if( m_keyboardHook ) {
		UnhookWindowsHookEx( m_keyboardHook );
		m_keyboardHook = NULL;
	}

	if( RecorderSettings::getInstance()->isTrayOn() )
		m_showMainWindow->trigger();
}

void Recorder::setTextEdit( QTextEdit* textEdit ) {
	m_textEdit = textEdit;
}

void Recorder::setMainWindowAction( QAction* pAction ) {
	m_showMainWindow = pAction;
}

void Recorder::startSelectingFragment() {
	QApplication::setOverrideCursor( Qt::CrossCursor );

	m_keys[VK_LCONTROL] = false;
	m_keys[VK_LSHIFT] = false;

	// remove unnecessary lines
	if( m_textEdit && RecorderSettings::getInstance()->isKeyboardOn() ) {
		removeXLastLines( 3 );
	} else {
		qDebug( "m_textEdit in Recorder class is a NULL or keyboard hook off" );
	}

	m_isScreenSelecting = true;
	ScreenSaver::getInstance()->resetPoints();
	ScreenSaver::getInstance()->setCurrentDesktop();
	ScreenSaver::getInstance()->show();
}

LRESULT CALLBACK Recorder::mouseHookProcedure( int code, WPARAM wParam, LPARAM lParam ) {
	if( code < 0 )
		return CallNextHookEx( m_mouseHook, code, wParam, lParam );   

	// prepare coordinates of the mouse cursor
	POINT pt = reinterpret_cast<MSLLHOOKSTRUCT*>( lParam )->pt;

	if( m_isScreenSelecting ) {
		ScreenSaver::getInstance()->setEndPoint( pt.x, pt.y );
		if( wParam == WM_LBUTTONDOWN ) {
			ScreenSaver::getInstance()->setStartPoint( pt.x, pt.y );
		}
		if( wParam == WM_LBUTTONUP ) {
			putCmd( "setInterval(1000)" );

			// remove unnecessary sleep before setInterval(); waitForImage();
			m_textEdit->moveCursor( QTextCursor::End, QTextCursor::MoveAnchor );
			m_textEdit->moveCursor( QTextCursor::StartOfLine, QTextCursor::MoveAnchor );
			m_textEdit->moveCursor( QTextCursor::Up, QTextCursor::MoveAnchor );
			m_textEdit->moveCursor( QTextCursor::Up, QTextCursor::MoveAnchor );
			m_textEdit->moveCursor( QTextCursor::Down, QTextCursor::KeepAnchor );
			m_textEdit->moveCursor( QTextCursor::EndOfLine, QTextCursor::KeepAnchor );
			m_textEdit->textCursor().removeSelectedText();

			QString _picFile = ScreenSaver::getInstance()->saveSelectedFragment();
			putCmd( "waitForImage(\"" + _picFile + "\")" );
			putCmd( "setInterval(0)" );
			ScreenSaver::getInstance()->close();
			QApplication::restoreOverrideCursor();
			m_isScreenSelecting = false;
		}

		return CallNextHookEx( 0, code, wParam, lParam );
	}
	

	if( RecorderSettings::getInstance()->isMouseOn() ) {
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
			case WM_MOUSEMOVE:
				if( RecorderSettings::getInstance()->isMouseMoveOn() )
					putCmd( "moveTo(" + _x + ", " + _y + ")" );
				break;
		}
	}

	return CallNextHookEx( 0, code, wParam, lParam );
}

LRESULT CALLBACK Recorder::keyboardHookProcedure( int code, WPARAM wParam, LPARAM lParam ) {
	if( code < 0 )
		return CallNextHookEx( m_keyboardHook, code, wParam, lParam );   

	DWORD _vkCode = reinterpret_cast<KBDLLHOOKSTRUCT*>( lParam )->vkCode;
	DWORD _isAltOn = reinterpret_cast<KBDLLHOOKSTRUCT*>( lParam )->flags & LLKHF_ALTDOWN;

	if( m_isScreenSelecting && _vkCode == VK_ESCAPE ) {
		m_isScreenSelecting = false;
		ScreenSaver::getInstance()->close();
		return CallNextHookEx( 0, code, wParam, lParam );
	}

	if( GetAsyncKeyState( VK_LCONTROL ) && GetAsyncKeyState( VK_LSHIFT ) && _vkCode == 'X' && !m_isRecStopped )
			stopRecording();
	if( GetAsyncKeyState( VK_LCONTROL ) && GetAsyncKeyState( VK_LSHIFT ) && _vkCode == 'Z' && !m_isScreenSelecting )
			startSelectingFragment();

	if( m_isScreenSelecting || !RecorderSettings::getInstance()->isKeyboardOn() ) 
		return CallNextHookEx( 0, code, wParam, lParam );

	QString _symbol = "";
	if( _vkCode >= 65 && _vkCode <= 90 )
		_symbol = ( char )( _vkCode + 32 );
	else
		_symbol = ( char )_vkCode;

	//qDebug( "code: %d, alt: %d, wparam: %d, lparam: %d", _vkCode, _isAltOn, wParam, lParam );
	if( GetAsyncKeyState( VK_RSHIFT ) && !m_keys[VK_RSHIFT] ) {
		m_keys[VK_RSHIFT] = true;
		putCmd( "sendText(\"{rshift+}\")" );
	}
	if( GetAsyncKeyState( VK_LSHIFT ) && !m_keys[VK_LSHIFT] ) {
		m_keys[VK_LSHIFT] = true;
		putCmd( "sendText(\"{lshift+}\")" );
	}
	if( GetAsyncKeyState( VK_RMENU ) && !m_keys[VK_RMENU] ) {
		m_keys[VK_RMENU] = true;
		putCmd( "sendText(\"{ralt+}\")" );
	}
	if( GetAsyncKeyState( VK_LMENU ) && !m_keys[VK_LMENU] ) {
		m_keys[VK_LMENU] = true;
		putCmd( "sendText(\"{lalt+}\")" );
	}
	if( GetAsyncKeyState( VK_RCONTROL ) && !m_keys[VK_RCONTROL] ) {
		m_keys[VK_RCONTROL] = true;
		putCmd( "sendText(\"{rctrl+}\")" );
	}
	if( GetAsyncKeyState( VK_LCONTROL ) && !m_keys[VK_LCONTROL] ) {
		m_keys[VK_LCONTROL] = true;
		putCmd( "sendText(\"{lctrl+}\")" );
	}

	if( wParam != WM_KEYUP && wParam != WM_SYSKEYUP ) {
		QString _strKey = LuaApiEngine::getStringKey( _vkCode ).c_str();
		if( _vkCode == VK_OEM_4 )
			putCmd( "sendText(\"[\")" );
		else if( _vkCode == VK_OEM_6 )
			putCmd( "sendText(\"]\")" );
		else if( _vkCode == VK_OEM_5 )
			putCmd( "sendText(\"\\\\\")" );
		else if( _vkCode == VK_OEM_1 )
			putCmd( "sendText(\";\")" );
		else if( _vkCode == VK_OEM_7 )
			putCmd( "sendText(\";\")" );
		else if( _vkCode == VK_OEM_3 )
			putCmd( "sendText(\"`\")" );
		else if( _vkCode == VK_OEM_COMMA )
			putCmd( "sendText(\",\")" );
		else if( _vkCode == VK_OEM_PERIOD )
			putCmd( "sendText(\".\")" );
		else if( _vkCode == VK_OEM_2 )
			putCmd( "sendText(\"/\")" );
		else if( _vkCode == VK_OEM_MINUS )
			putCmd( "sendText(\"-\")" );
		else if( _vkCode == VK_OEM_PLUS )
			putCmd( "sendText(\"+\")" );
		else if( _strKey != "" && ( _vkCode != VK_RSHIFT ) && ( _vkCode != VK_LSHIFT ) && ( _vkCode != VK_RMENU ) &&
							 ( _vkCode != VK_LMENU ) && ( _vkCode != VK_RCONTROL ) && ( _vkCode != VK_LCONTROL )) {

			putCmd( "sendText(\"{" + _strKey + "}\")" );
		}
		if( ( _vkCode >= 65 && _vkCode <= 90 ) || ( _vkCode >= 48 && _vkCode <= 57 ) )
			putCmd( "sendText(\"" + _symbol + "\")" );
	}

	switch( wParam ) {
		case WM_KEYUP:
			if( _vkCode == VK_RSHIFT ) {
				putCmd( "sendText(\"{rshift-}\")" );
				m_keys[VK_RSHIFT] = false;
			} else if( _vkCode == VK_LSHIFT ) {
				putCmd( "sendText(\"{lshift-}\")" );
				m_keys[VK_LSHIFT] = false;
			} else if( _vkCode == VK_RMENU ) {
				putCmd( "sendText(\"{ralt-}\")" );
				m_keys[VK_RMENU] = false;
			} else if( _vkCode == VK_LMENU ) {
				putCmd( "sendText(\"{lalt-}\")" );
				m_keys[VK_LMENU] = false;
			} else if( _vkCode == VK_RCONTROL ) {
				putCmd( "sendText(\"{rctrl-}\")" );
				m_keys[VK_RCONTROL] = false;
			} else if( _vkCode == VK_LCONTROL ) {
				putCmd( "sendText(\"{lctrl-}\")" );
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

void Recorder::removeXLastLines( int number ) {
	m_textEdit->moveCursor( QTextCursor::End, QTextCursor::MoveAnchor );
	m_textEdit->moveCursor( QTextCursor::StartOfLine, QTextCursor::MoveAnchor );
	for( int i = 0; i < number; ++i )
		m_textEdit->moveCursor( QTextCursor::Up, QTextCursor::MoveAnchor );
	m_textEdit->moveCursor( QTextCursor::End, QTextCursor::KeepAnchor );
	m_textEdit->textCursor().removeSelectedText();
}