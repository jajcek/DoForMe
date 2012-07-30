#include "lua_api.h"

#define defineKey( x, y )						    \
	m_specialKeys[x]    = new Key( y, Key::CLICK ); \
	m_specialKeys[x"+"] = new Key( y, Key::DOWN );  \
	m_specialKeys[x"-"] = new Key( y, Key::UP ); 

LuaEngine* LuaApiEngine::m_luaEngine;
std::map<QString, Key*> LuaApiEngine::m_specialKeys;

void LuaApiEngine::setLuaEngine( LuaEngine* luaEngine ) {
	m_luaEngine = luaEngine;
}

int LuaApiEngine::prepareLeftDown( lua_State* state ) {
	m_luaEngine->addCommand( reinterpret_cast<void (*)( std::deque<int> )>( LuaApiEngine::leftDown ) );
	return 0;
}

int LuaApiEngine::prepareRightDown( lua_State* state ) {
	m_luaEngine->addCommand( reinterpret_cast<void (*)( std::deque<int> )>( LuaApiEngine::rightDown ) );
	return 0;
}

int LuaApiEngine::prepareMiddleDown( lua_State* state ) {
	m_luaEngine->addCommand( reinterpret_cast<void (*)( std::deque<int> )>( LuaApiEngine::middleDown ) );
	return 0;
}

int LuaApiEngine::prepareLeftDownAt( lua_State* state ) {
	prepareMoveTo( state );
	m_luaEngine->addCommand( reinterpret_cast<void (*)( std::deque<int> )>( LuaApiEngine::leftDown ) );
	return 0;
}

int LuaApiEngine::prepareRightDownAt( lua_State* state ) {
	prepareMoveTo( state );
	m_luaEngine->addCommand( reinterpret_cast<void (*)( std::deque<int> )>( LuaApiEngine::rightDown ) );
	return 0;
}

int LuaApiEngine::prepareMiddleDownAt( lua_State* state ) {
	prepareMoveTo( state );
	m_luaEngine->addCommand( reinterpret_cast<void (*)( std::deque<int> )>( LuaApiEngine::middleDown ) );
	return 0;
}

int LuaApiEngine::prepareLeftUp( lua_State* state ) {
	m_luaEngine->addCommand( reinterpret_cast<void (*)( std::deque<int> )>( LuaApiEngine::leftUp ) );
	return 0;
}

int LuaApiEngine::prepareRightUp( lua_State* state ) {
	m_luaEngine->addCommand( reinterpret_cast<void (*)( std::deque<int> )>( LuaApiEngine::rightUp ) );
	return 0;
}

int LuaApiEngine::prepareMiddleUp( lua_State* state ) {
	m_luaEngine->addCommand( reinterpret_cast<void (*)( std::deque<int> )>( LuaApiEngine::middleUp ) );
	return 0;
}

int LuaApiEngine::prepareLeftUpAt( lua_State* state ) {
	prepareMoveTo( state );
	m_luaEngine->addCommand( reinterpret_cast<void (*)( std::deque<int> )>( LuaApiEngine::leftUp ) );
	return 0;
}

int LuaApiEngine::prepareRightUpAt( lua_State* state ) {
	prepareMoveTo( state );
	m_luaEngine->addCommand( reinterpret_cast<void (*)( std::deque<int> )>( LuaApiEngine::rightUp ) );
	return 0;
}

int LuaApiEngine::prepareMiddleUpAt( lua_State* state ) {
	prepareMoveTo( state );
	m_luaEngine->addCommand( reinterpret_cast<void (*)( std::deque<int> )>( LuaApiEngine::middleUp ) );
	return 0;
}

int LuaApiEngine::prepareLeftClick( lua_State* state ) {
	m_luaEngine->addCommand( reinterpret_cast<void (*)( std::deque<int> )>( LuaApiEngine::leftClick ) );
	return 0;
}

int LuaApiEngine::prepareRightClick( lua_State* state ) {
	m_luaEngine->addCommand( reinterpret_cast<void (*)( std::deque<int> )>( LuaApiEngine::rightClick ) );
	return 0;
}

int LuaApiEngine::prepareMiddleClick( lua_State* state ) {
	m_luaEngine->addCommand( reinterpret_cast<void (*)( std::deque<int> )>( LuaApiEngine::middleClick ) );
	return 0;
}

int LuaApiEngine::prepareLeftClickAt( lua_State* state ) {
	prepareMoveTo( state );
	m_luaEngine->addCommand( reinterpret_cast<void (*)( std::deque<int> )>( LuaApiEngine::leftClick ) );
	return 0;
}

int LuaApiEngine::prepareRightClickAt( lua_State* state ) {
	prepareMoveTo( state );
	m_luaEngine->addCommand( reinterpret_cast<void (*)( std::deque<int> )>( LuaApiEngine::rightClick ) );
	return 0;
}

int LuaApiEngine::prepareMiddleClickAt( lua_State* state ) {
	prepareMoveTo( state );
	m_luaEngine->addCommand( reinterpret_cast<void (*)( std::deque<int> )>( LuaApiEngine::middleClick ) );
	return 0;
}

int LuaApiEngine::prepareLeftDoubleClick( lua_State* state ) {
	m_luaEngine->addCommand( reinterpret_cast<void (*)( std::deque<int> )>( LuaApiEngine::leftDoubleClick ) );
	return 0;
}

int LuaApiEngine::prepareLeftDoubleClickAt( lua_State* state ) {
	prepareMoveTo( state );
	m_luaEngine->addCommand( reinterpret_cast<void (*)( std::deque<int> )>( LuaApiEngine::leftDoubleClick ) );
	return 0;
}

int LuaApiEngine::prepareSleep( lua_State* state ) {
	// moveTo() has 1 argument, arguments are put onto lua's stack
	int _arg = ( int )lua_tonumber( state, -1 );

	// we took 1 argument from the stack, so we modify pointer to the top of the stack
	lua_settop( state, -1 );

	std::deque<int> _args;
	_args.push_back( _arg );
	m_luaEngine->addCommand( LuaApiEngine::sleep, _args );

	return 0;
}

int LuaApiEngine::prepareMoveTo( lua_State* state ) {
	// moveTo() has 2 arguments, arguments are put onto lua's stack
	int _arg1 = ( int )lua_tonumber( state, -2 );
	int _arg2 = ( int )lua_tonumber( state, -1 );

	// we took 2 arguments from the stack, so we modify pointer to the top of the stack
	lua_settop( state, -2 );

	std::deque<int> _args;
	_args.push_back( _arg1 );
	_args.push_back( _arg2 );

	m_luaEngine->addCommand( LuaApiEngine::moveTo, _args );

	return 0;
}

int LuaApiEngine::prepareSendText( lua_State* state ) {
	// moveTo() has 1 argument, arguments are put onto lua's stack
	const char* _arg = ( const char* )lua_tostring( state, -1 );

	// we took 1 argument from the stack, so we modify pointer to the top of the stack
	lua_settop( state, -1 );
	
	std::deque<int> _args;
	int _symbolsNumber = strlen( _arg );
	for( int i = 0; i < _symbolsNumber; ++i ) {
		_args.push_back( _arg[i] );
	}
	m_luaEngine->addCommand( LuaApiEngine::sendText, _args );

	return 0;
}

void LuaApiEngine::leftDown() {
	INPUT Input = { 0 };
	Input.type       = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput( 1, &Input, sizeof( INPUT ) );
}

void LuaApiEngine::rightDown() {
	INPUT Input = { 0 };
	Input.type       = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput( 1, &Input, sizeof( INPUT ) );
}

void LuaApiEngine::middleDown() {
	INPUT Input = { 0 };
	Input.type       = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
	SendInput( 1, &Input, sizeof( INPUT ) );
}

void LuaApiEngine::leftUp() {
	INPUT Input = { 0 };
	Input.type       = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput( 1, &Input, sizeof( INPUT ) );
}

void LuaApiEngine::rightUp() {
	INPUT Input = { 0 };
	Input.type       = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput( 1, &Input, sizeof( INPUT ) );
}

void LuaApiEngine::middleUp() {
	INPUT Input = { 0 };
	Input.type       = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
	SendInput( 1, &Input, sizeof( INPUT ) );
}

void LuaApiEngine::leftClick() {
	leftDown();
	leftUp();
}

void LuaApiEngine::rightClick() {
	rightDown();
	rightUp();
}

void LuaApiEngine::middleClick() {
	middleDown();
	middleUp();
}

void LuaApiEngine::leftDoubleClick() {
	leftDown();
	leftUp();
	leftDown();
	leftUp();
}

void LuaApiEngine::sleep( std::deque<int> args ) {
	// set new interval for the lua engine (it will restart itself),
	// notice that setInterval changes interval only for one command (only for sleep here)
	m_luaEngine->setInterval( args.front() );

	// we 'used' the sleep()'s argument, so remove it from the stack
	// actually it's not even needed, as the sleep method has only one argument, so
	// we don't need to pop it because we don't need to get to another argument
	// but for integrity is added
	args.pop_front();
}

void LuaApiEngine::moveTo( std::deque<int> args ) {
	// get arguments from lua stack
	int _x = args.front();
	args.pop_front();
	int _y = args.front();
	args.pop_front();
	
	// get values for the current screen to be able to calculate real position of the cursor
	double _fScreenWidth   = GetSystemMetrics( SM_CXSCREEN ) - 1; 
	double _fScreenHeight  = GetSystemMetrics( SM_CYSCREEN ) - 1; 
	double _fx = _x * ( 65535.0f / _fScreenWidth );
	double _fy = _y * ( 65535.0f / _fScreenHeight );

	INPUT  Input = { 0 };
	Input.type       = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = _fx;
	Input.mi.dy = _fy;
	SendInput( 1, &Input,sizeof( INPUT ) );
}

void LuaApiEngine::sendText( std::deque<int> args ) {
	// store all send events
	std::vector<INPUT> _inputs;
	INPUT _in = { 0 };

	// for all symbols
	int _symbolsNumber = args.size();
	for( int i = 0; i < _symbolsNumber; ++i ) {
		// get current key
		char _char = args.front();

		// we will store a text describing special key that is written in {} brackets in the script
		// special key is a return key, tabulator etc.
		QString _specialKey = "";
		if( _char == '{' ) {
			// gets text between {} brackets
			int _symbolsRead = getSpecialKey( _specialKey, args );
			
			// it is needed to increase the iterator with number of elements read
			i += _symbolsRead;

			// if an error occured (no closing '}' bracket)
			if( _specialKey == "err" ) {
				QMessageBox _msg( QMessageBox::Critical, "Error", "There's no closing '}' symbol." );
				_msg.exec();

				return;
			}

			// check if the value from {} exists in the m_specialKeys map
			if( m_specialKeys.find( _specialKey ) != m_specialKeys.end() ) {
				// get value for specialKey string and insert the key to _inputs vector
				// (objects for keys are created in LuaApiEngine::initSpecialKeys()
				// invoked in mainwin.cpp in the constructor
				m_specialKeys[_specialKey]->insertKeyTo( _inputs );

				continue;
			} else {
				QMessageBox _msg( QMessageBox::Critical, "Error", "Undefined special key." );
				_msg.exec();

				return;
			}
		}

		// if it's not a special key
		// get virtual code of a character to high byte and its state (e.g. shift) to low byte
		unsigned short _symbol = VkKeyScan( _char );
		unsigned short _symbolCode = LOBYTE( _symbol );
		unsigned short _symbolState = HIBYTE( _symbol );

		// we took one letter so drop it from the stack
		args.pop_front();

		// is a shifted symbol
		if( _symbolState == 1 ) {
			Key::insertKeyTo( VK_RSHIFT, Key::DOWN, _inputs );
		}

		Key::insertKeyTo( _symbolCode, Key::CLICK, _inputs );

		// release shift
		if( _symbolState == 1 ) {
			Key::insertKeyTo( VK_RSHIFT, Key::UP, _inputs );
		}
	}

	// send all symbols from the sendText() api function
	SendInput( _inputs.size(), &_inputs.at( 0 ), sizeof( INPUT ) );
}

int LuaApiEngine::getSpecialKey( QString& specialKey, std::deque<int>& args ) {
	unsigned int i = 0;
	// remove '{' and get next symbol (and btw increase an iterator, because we dropped one argument)
	args.pop_front();
	++i;
	char _char = args.front();

	// get everything from the {} brackets into _specialKey
	while(  _char != '}' ) {
		// store current symbol
		specialKey += _char;
		// current symbol has been stored, so we can remove it from the stack
		args.pop_front();
		++i;

		// if there are no more symbols on the stack, it means that there's lack of '}' somewhere
		// otherwise get next symbol
		if( args.empty() ) {
			specialKey = "err";
			return i;
		} else {
			// get next symbol from the stack
			_char = args.front();
		}
	}

	// remove the '}' it's not needed anywhere now (it was need to stop the loop above)
	// if the char is '}' return the key (it means that the key is closed correctly), otherwise return an empty string
	// the code will always go into this if, if not the return "err" from above will end the function
	if( _char == '}' ) {
		args.pop_front();
		return i;
	}
}

void LuaApiEngine::initSpecialKeys() {
	// check macro 'defineKey' defined at the top of the file

	defineKey( "n", VK_RETURN )
	defineKey( "t", VK_TAB )
	defineKey( "caps", VK_CAPITAL )
	defineKey( "ralt", VK_RMENU )
	defineKey( "lalt", VK_LMENU )
	defineKey( "rctrl", VK_RCONTROL )
	defineKey( "lctrl", VK_LCONTROL )
	defineKey( "rshift", VK_RSHIFT )
	defineKey( "lshift", VK_LSHIFT )
	defineKey( "back", VK_BACK )
	defineKey( "del", VK_DELETE )
	defineKey( "home", VK_HOME )
	defineKey( "end", VK_END )
	defineKey( "pup", VK_PRIOR )
	defineKey( "pdown", VK_NEXT )
	defineKey( "ins", VK_INSERT )
	defineKey( "print", VK_PRINT )
	defineKey( "up", VK_UP )
	defineKey( "down", VK_DOWN )
	defineKey( "left", VK_LEFT )
	defineKey( "right", VK_RIGHT )
	defineKey( "n0", VK_NUMPAD0 )
	defineKey( "n1", VK_NUMPAD1 )
	defineKey( "n2", VK_NUMPAD2 )
	defineKey( "n3", VK_NUMPAD3 )
	defineKey( "n4", VK_NUMPAD4 )
	defineKey( "n5", VK_NUMPAD5 )
	defineKey( "n6", VK_NUMPAD6 )
	defineKey( "n7", VK_NUMPAD7 )
	defineKey( "n8", VK_NUMPAD8 )
	defineKey( "n9", VK_NUMPAD9 )
	defineKey( "n0", VK_NUMPAD0 )
	defineKey( "f1", VK_F1 )
	defineKey( "f2", VK_F2 )
	defineKey( "f3", VK_F3 )
	defineKey( "f4", VK_F4 )
	defineKey( "f5", VK_F5 )
	defineKey( "f6", VK_F6 )
	defineKey( "f7", VK_F7 )
	defineKey( "f8", VK_F8 )
	defineKey( "f9", VK_F9 )
	defineKey( "f10", VK_F10 )
	defineKey( "f11", VK_F11 )
	defineKey( "f12", VK_F12 )
	defineKey( "sum", VK_ADD )
	defineKey( "sub", VK_SUBTRACT )
	defineKey( "mul", VK_MULTIPLY )
	defineKey( "div", VK_DIVIDE )
	defineKey( "dec", VK_DECIMAL )
	defineKey( "numlock", VK_NUMLOCK )
	defineKey( "rwin", VK_RWIN )
	defineKey( "lwin", VK_LWIN )
}