#pragma once

#include <qdebug.h>
#include <qmap.h>
#include <qpair.h>
#include <qdebug.h>
#include <qbasictimer.h>
#include <queue>
#include <qwidget.h>
#include <stack>
#include "lua_headers.h"
#include "commands_manager.h"
#include <Windows.h>

/**
	\class LuaEngine lua_engine.h "lua_engine.h"
	\brief Engine for maintaing LUA's API commands.
	\details Objects of this class load scripts, check their grammar correctness and store the commands for further executing.
	As first step after creating an object of this class you have to register your API functions by using LuaEngine::registerFunction method.
	When all of the functions has been registered you are allowed to load and parse scripts by using LuaEngine::loadScript and LuaEngine::parseScript methods.
	LuaEngine::loadScript simply loads code to the memory and check its correctness whereas LuaEngine::parseScript runs the script.
	During parsing LUA invokes methods which can prepare commands by putting them to a queue. This is done for allowing executing commands with some
	time interval (we can remove time interval - simply set GUI interval to 0). Check LuaEngine::registerFunction for more details.
	Next step (optional) is to set a time interval in which the commands will be executed (default is 500 milliseconds) by using LuaEngine::setGUIInterval method.
	After successful load and parse you need to copy queue and stack to the lua's engine by using LuaEngine::copyData.
	Last step is to invoke LuaEngine::start() to start executing the commands.
	Also important thing to mention is LuaEngine::setInterval. Comparing to the GUI version it changes time interval only for the next command.
	Therefore it should be used for some API functions like sleep().
	\author Jacek Topolski
	\version 1.0
	\date 28.06.2012
	\example LuaEngine_example.cpp
	\brief Example of how to initialize lua's object, register functions for scripts, load the script and run it.
*/
class LuaEngine : public QObject {
	Q_OBJECT // used for timer support

public:
	/**
		\enum MODE
		\brief Values determining which mode we are using loadScript() function in.
		\var BUFFER
		\brief Value which indicates that the loadScript() function loads from a buffer.
		\var FILE
		\brief Value which indicates that the loadScript() function loads from a file.
	*/
	enum MODE { BUFFER = 0, FILE };

private:
	/**
		\brief The instance of the singleton.
	*/
	static LuaEngine* m_object;

	/**
		\brief State of the lua's engine. Used by lua's library - don't touch it.
	*/
	lua_State *luaState;

	/**
		\brief Timer is used for supporting commands execution in a latency.
		\details It is possible to execute commands every some time which is specified in LuaEngine::m_uInterval (as milliseconds).
	*/
	QBasicTimer* m_timer;
	/**
		\brief Stores time (as milliseconds) needed to execute next command that is available in the queue LuaEngine::m_commands.
		\details This can be changed while calling e.g. sleep() in the script. This value is used in timer event, not the LuaEngine::m_uGUIInterval.
		Check LuaEngine::m_uGUIInterval for more details.
	*/
	unsigned m_uInterval;
	/**
		\brief This is the same as LuaEngine::m_uInterval, but it stores value from "Commands time interval" in GUI.
		\details This shouldn't be changed while calling e.g API sleep() function. This value only depends on value set in the GUI.
		The value is assigned to m_uInterval if needed to come back from sleep() function used in script.
	*/
	unsigned m_uGUIInterval;
	
	/**
		\brief Stores all commands that are executed by the engine. See CommandsManager for more details.
	*/
	CommandsManager m_commands;

	/**
		\brief Indicates if there is a syntax/memory error in the loaded lua's script.
		\details If there is no errors the value is equal to 0, otherwise the value is a number of error code.

		Error code:
		3 - syntax error (defined as LUA_ERRSYNTAX in lua.h).
		4 - memory allocation error (defined as LUA_ERRMEM in lua.h).
	*/
	int m_loadError;

	/**
		\brief Indicates if there is a runtime error in the loaded lua's script.
		\details If there is no errors the value is equal to 0, otherwise the value is a number of error code.

		Error code:
		2 - a runtime error (defined as LUA_ERRRUN in lua.h).
		4 - memory allocation error (defined as LUA_ERRMEM in lua.h).
		5 - error while running the error handler function (defined as LUA_ERRERR in lua.h).
	*/
	int m_parseError;

	/**
		\brief Stores exact string which is returned by lua's lua_pcall function.
		\details In lua 5.1 the string has form like "[string "?"]:1: attempt to call global 'FunctionName' (a nil value)"
	*/
	QString m_textError;

	/**
		\brief Indicates if the interval has been changed by using GUI or sleep() api function.
		\details If the variable is set to true it means that the sleep() api function is being executed,
		otherwise the interval has been changed by using GUI.
	*/
	bool m_bIntervalChanged;

private:
	/**
		\brief Private constructor to make the class a singleton.
		\details Also initializes LuaEngine::m_loadError and LuaEngine::m_runtimeError to 0, m_uInterval to 500 and creates object for m_timer.
		m_textError is set to "". After that you have to register functions used in the LUA API and load a script by using
		loadScript() before run it with runScript().
	*/
	LuaEngine();

public:
	/**
		\brief Gets the only isntance of the object.
	*/
	static LuaEngine* getInstance();

	/**
		\brief Ends lua engine by releasing memory.
	*/
	~LuaEngine();

	/**
		\brief Registers API function used in scripts.
		\details <B>lua_CFunction</B> is declared as <B>typedef int (*lua_CFunction) (lua_State *L);</B>
		\param[in] functionName Name of the function that has to be available in the LUA API.
		\param[in] pFunction Pointer to a function which will be called when the functionName() in the script is found.
	*/
	void registerFunction( const char* functionName, lua_CFunction pFunction );

	/**
		\brief Parses script (prepares for running it) into memory from a specified buffer.
		\param[in] code Script code or file name, depends on the second argument.
		\param[in] mode Indicates whether this function loads from file or from a buffer. See LuaEngine::MODE for more details.
		\return Error code or 0 if there are no errors. See luaEngine::m_loadError for more details.
	*/
	int loadScript( const char* code, int mode );
	/**
		\brief Puts api functions onto stack - LuaEngine::m_commands - that has been previously loaded by loadScript().
		\return Error code or 0 if there are no errors. See luaEngine::m_parseError for more details.
	*/
	int parseScript();
	/**
		\brief Runs action.
		\details This is a wrapper for 3 other functions - LuaEngine::loadScript, LuaEngine::parseScript and LuaEngine::start().
		\param[in] code Code to be executed.
		\return Value which informs if the code has been executed without errors.
		If there was an error get it by using LuaEngine::validateLastLoad and LuaEngine::validateLastParse.
	*/
	bool run( const char* code );

	/**
		\brief Checks if there was error in the last loaded file.
		\return Error code. See luaEngine::m_loadError for more details.
	*/
	int validateLastLoad();
	/**
		\brief Checks if there was error in the last parsed file.
		\return Error code. See luaEngine::m_parseError for more details.
	*/
	int validateLastParse();

	/**
		\brief Returns error in a text form from last parsed (with LuaEngine::parseScript()) script.
		\details In lua 5.1 the string has form like "[string "?"]:1: attempt to call global 'FunctionName' (a nil value)"
		\return Error in a text form.
	*/
	QString getTextError() const;

	/**
		\brief Puts actions onto stack. See LuaEngine::m_commands for more details.
		\param[in] pCmd Action which is put onto LuaEngine::m_commands stack.
	*/
	void addCommand( void ( *pCmd )( std::deque<int> ) );
	/**
		\brief Puts actions onto stack with its arguments. See LuaEngine::m_commands for more details.
		\param[in] pCmd Action which is put onto LuaEngine::m_commands stack.
		\param[in] args Arguments for api functions that is put onto LuaEngine::m_args stack.
	*/
	void addCommand( void ( *pCmd )( std::deque<int> ), std::deque<int> args );

	/**
		\brief Funtion which is called by the LuaEngine::m_timer timer.
		\param[in] e Event which invoked the function.
	*/
	void timerEvent( QTimerEvent* e );
	/**
		\brief Starts executing commands (actually starts the timer which executes the commands).
	*/
	void start();
	/**
		\brief Stops executing commands (stop the LuaEngine::m_timer timer).
	*/
	void stop();
	/**
		\brief Set time interval for one command (used for sleep() api function).
		\param[in] interval Time interval.
	*/
	void setInterval( int interval );
	/**
		\brief Set time time interval for all commands.
		\param[in] interval Time interval.
	*/
	void setGUIInterval( int interval );
	/**
		\return Time interval for all commands.
	*/
	int getGUIInterval() const;
};