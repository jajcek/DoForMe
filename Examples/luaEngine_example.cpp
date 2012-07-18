// create lua object
LuaEngine lua;

// register functions that will be used in lua's scripts
// in this example the functions are defined as static in LuaApiEngine class
lua.registerFunction( "sleep", LuaApiEngine::prepareSleep, LuaApiEngine::sleep, 1 );
lua.registerFunction( "leftDown", LuaApiEngine::prepareLeftDown, LuaApiEngine::leftDown, 0 );
lua.registerFunction( "moveTo", LuaApiEngine::prepareMoveTo, LuaApiEngine::moveTo, 2 );
//...

// load script.apc and check if the script has been successfully loaded (by checking its correctness)
// you can load it from file using LuaEngine::FILE, or from a buffer using LuaEngine::BUFFER
switch( lua.loadScript( "script.apc", LuaEngine::FILE ) {
	case LUA_ERRSYNTAX: // handle syntax error
	case LUA_ERRMEM: // handle memory allocation error
	case 0: { // everything went ok
		// parse script and put api functions onto its lua's engine stack
		switch( lua.parseScript() ) {
			case LUA_ERRRUN: // handle runtime error (e.g. 'function xyz doesn't exists' - we can get this with lua.getTextError())
				QString _error = lua.getTextError();
				// ...
			}
			case LUA_ERRMEM: // handle memory allocation error
			case LUA_ERRERR: {
			// case LUA_ERRERR: not needed, there's no defined lua's function that handles errors
			case 0: // everything went ok
				// you have to copy created (by lua.parseScript()) stacks that contain
				// commands and arguments. Actually these stacks are not created by lua.parseScript(),
				// but using static api functions (registered using lua.registerFunction())
				// from LuaApiEngine which are invoked by lua.parseScript()
				lua.copyStacks( LuaApiEngine::getCommandsStack(), LuaApiEngine::getArgsStack() ); 
		}
	}
}

// it is possible to change timer interval, e.g. now the commands will be executed with 1 second delay
lua.setGUIInterval( 1000 );

// start script (by taking commands from the LuaEngine's stack one by one)
lua.start();