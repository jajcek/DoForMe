#include "lua_engine.h"

LuaEngine* LuaEngine::m_object = NULL;

LuaEngine::LuaEngine() : luaState( lua_open() ), m_loadError( 0 ), m_parseError( 0 ), m_bSpecialKeyError( false ), m_textError( "" ),
						 m_timer( new QBasicTimer() ), m_uInterval( 1000 ), m_uGUIInterval( 1000 ), m_bIntervalChanged( false ),
						 m_isExecuting( false ) {}

LuaEngine::~LuaEngine() {
	lua_close( luaState );
	delete m_timer;
}

LuaEngine* LuaEngine::getInstance() {
	if( !m_object )
		m_object = new LuaEngine();

	return m_object;
}

void LuaEngine::registerFunction( const char* functionName, lua_CFunction pFunction ) {
	// registers function, after this manner the function called "functionName"
	// will be available to use in scripts (it will be invoking pFunction in C/C++ code)
	lua_register( luaState, functionName, pFunction );
}

int LuaEngine::loadScript( const char* code, int mode ) {
	// load script code from a buffer, otherwise from a file
	if( mode == BUFFER )
		m_loadError = luaL_loadbuffer( luaState, code, strlen( code ), NULL );
	else
		m_loadError = luaL_loadfile( luaState, code );

	return m_loadError;
}

int LuaEngine::parseScript() {
	qDebug( "LuaEngine::parseScript" );

	// reset value for special key error
	m_bSpecialKeyError = false;

	// invoke previously loaded script (put commands to the queue by using LuaApiEngine class)
	m_parseError = lua_pcall( luaState, 0, 0, 0 );

	// get error message if error occured
	m_textError = lua_tostring( luaState, -1 );
	
	return m_parseError + ( int )m_bSpecialKeyError;
}

bool LuaEngine::run( const char* code, bool onlyParse ) {
	qDebug( "LuaEngine::run" );

	m_loadError = loadScript( code, LuaEngine::BUFFER );
	m_parseError = parseScript();

	// if the engine is executing a script we can't invoke start again,
	// because it will pause the timer for the GUI interval.
	if( onlyParse == false && !m_isExecuting ) {
		start();
		m_isExecuting = true;
	}
	
	return ( m_loadError | m_parseError );
}

int LuaEngine::validateLastLoad() {
	return m_loadError;
}

int LuaEngine::validateLastParse() {
	return m_parseError | static_cast<int>( m_bSpecialKeyError );
}

void LuaEngine::setSpecialKeyError( bool error ) {
	if( error )
		m_bSpecialKeyError = static_cast<bool>( LUA_ERRRUN );
	else
		m_bSpecialKeyError = 0;
}

QString LuaEngine::getTextError() const {
	return m_textError;
}

void LuaEngine::addCommand( void ( *pCmd )( std::deque<int> ) ) {
	std::deque<int> _args;
	m_commands.addCommand( pCmd, _args );
}

void LuaEngine::addCommand( void ( *pCmd )( std::deque<int> ), std::deque<int> args ) {
	m_commands.addCommand( pCmd, args );
}

void LuaEngine::timerEvent( QTimerEvent* ) {
	qDebug( "LuaEngine::timerEvent" );

	// check if there are any commands to execute, otherwise stop the timer
	if( !m_commands.isEmpty() ) {
		m_commands.executeNext();
	} else {
		// stop the timer if there are no more commands to execute
		stop();
		m_isExecuting = false;
	}

	// if the engine's interval has been changed from outside (e.g. by using some of the api function like sleep())
	// we need to take it into account by going through the timer function without changing anything
	// and then execute it again with another interval
	// after that 'sleep' function we need to change the interval to its previous value (a value set in GUI)
	if( !m_bIntervalChanged ) {
		// it's not necessary to restart the timer if the values are the same (for better performance)
		bool _bRestart = false;
		if( m_uInterval != m_uGUIInterval )
			_bRestart = true;

		// change interval to its previous value
		m_uInterval = m_uGUIInterval;

		// restart the timer if necessary
		if( _bRestart )
			start();
	} else {
		// we've already prepared 'sleep' so we can continue invoking this method in an old interval set in the GUI
		m_bIntervalChanged = false;
	}
}

void LuaEngine::start() {
	m_timer->start( m_uInterval, this );
}

void LuaEngine::stop() {
	m_timer->stop();
}

void LuaEngine::setInterval( int interval ) {
	m_uInterval = interval;
	m_bIntervalChanged = true;
	m_timer->start( m_uInterval, this );
}

void LuaEngine::setGUIInterval( int interval ) {
	m_uGUIInterval = interval;
	m_uInterval = interval;
}

int LuaEngine::getGUIInterval() const {
	return m_uGUIInterval;
}

void LuaEngine::reset() {
	m_loadError = 0;
	m_parseError = 0;
	m_bSpecialKeyError = false;
	m_isExecuting = false;
	m_commands.clearCommands();
}