#include "key.h"

Key::Key( unsigned short keyCode, unsigned short mode ) : m_keyCode( keyCode ), m_mode( mode ) {}

void Key::insertKeyTo( std::vector<INPUT>& inputs ) {
	INPUT _in = { 0 };
	
	switch( m_mode ) {
		default:
		case CLICK:
			_in.type   = INPUT_KEYBOARD;
			_in.ki.wVk = m_keyCode;
			inputs.push_back( _in );

			_in.type       = INPUT_KEYBOARD;
			_in.ki.dwFlags = KEYEVENTF_KEYUP;
			_in.ki.wVk     = m_keyCode;
			inputs.push_back( _in );
			break;
		case DOWN:
			_in.type   = INPUT_KEYBOARD;
			_in.ki.wVk = m_keyCode;
			inputs.push_back( _in );
			break;
		case UP:
			_in.type       = INPUT_KEYBOARD;
			_in.ki.dwFlags = KEYEVENTF_KEYUP;
			_in.ki.wVk     = m_keyCode;
			inputs.push_back( _in );
	}
}

void Key::insertKeyTo( unsigned short keyCode, unsigned short mode, std::vector<INPUT>& inputs ) {
	INPUT _in = { 0 };
	
	switch( mode ) {
		default:
		case CLICK:
			_in.type   = INPUT_KEYBOARD;
			_in.ki.wVk = keyCode;
			inputs.push_back( _in );

			_in.type       = INPUT_KEYBOARD;
			_in.ki.dwFlags = KEYEVENTF_KEYUP;
			_in.ki.wVk     = keyCode;
			inputs.push_back( _in );
			break;
		case DOWN:
			_in.type   = INPUT_KEYBOARD;
			_in.ki.wVk = keyCode;
			inputs.push_back( _in );
			break;
		case UP:
			_in.type       = INPUT_KEYBOARD;
			_in.ki.dwFlags = KEYEVENTF_KEYUP;
			_in.ki.wVk     = keyCode;
			inputs.push_back( _in );
	}
}

inline void Key::setKeyCode( unsigned short keyCode ) {
	m_keyCode = keyCode;
}

inline unsigned short Key::getKeyCode() const {
	return m_keyCode;
}

inline void Key::setMode( unsigned short mode ) {
	m_mode = mode;
}

inline unsigned short Key::getMode() const {
	return m_mode;
}