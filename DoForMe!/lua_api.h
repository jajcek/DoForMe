#pragma once

#include <windows.h>
#include <qdebug.h>
#include <qbasictimer.h>
#include <queue>
#include <qwidget.h>
#include <stack>
#include <qmessagebox.h>
#include "lua_engine.h"
#include "key.h"

/**
	\class luaApiEngine lua_api.h "lua_api.h"
	\brief LUA API functions.
	\details Stores all the information and definitions about LUA API function. It has also a timer manager which allows to run every
	action after some time.
	\author Jacek Topolski
	\version 1.0
	\date 29.06.2012
	\pre Object of this class has a stack which is filled up using luaEngine class. Therefore before luaApiEngine::start() is
	executed there should be luaEngine::runScript() execution. Otherwise nothing will happen (because stack will be empty).
	\example luaApiEngine_example.cpp
	\brief Example of how to initialize lua api and start it.
*/
class LuaApiEngine {
private:
	static LuaEngine* m_luaEngine;
	static std::map<QString, Key*> m_specialKeys;

public:
	static void setLuaEngine( LuaEngine* luaEngine );
	static void initSpecialKeys();

	static int prepareSleep( lua_State* state );

	/**
		\brief Puts action of pressing left mouse button onto the stack.
		\details Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
	*/
	static int prepareLeftDown( lua_State* state );
	static int prepareRightDown( lua_State* state );
	static int prepareMiddleDown( lua_State* state );
	static int prepareLeftDownAt( lua_State* state );
	static int prepareRightDownAt( lua_State* state );
	static int prepareMiddleDownAt( lua_State* state );

	static int prepareLeftUp( lua_State* state );
	static int prepareRightUp( lua_State* state );
	static int prepareMiddleUp( lua_State* state );
	static int prepareLeftUpAt( lua_State* state );
	static int prepareRightUpAt( lua_State* state );
	static int prepareMiddleUpAt( lua_State* state );

	static int prepareLeftClick( lua_State* state );
	static int prepareRightClick( lua_State* state );
	static int prepareMiddleClick( lua_State* state );
	static int prepareLeftClickAt( lua_State* state );
	static int prepareRightClickAt( lua_State* state );
	static int prepareMiddleClickAt( lua_State* state );

	static int prepareLeftDoubleClick( lua_State* state );
	static int prepareLeftDoubleClickAt( lua_State* state );

	static int prepareMoveTo( lua_State* state );

	static int prepareSendText( lua_State* state );

	// --------------------------------------------------------------------------------------------------

	static void leftDown();
	static void rightDown();
	static void middleDown();

	static void leftUp();
	static void rightUp();
	static void middleUp();

	static void leftClick();
	static void rightClick();
	static void middleClick();

	static void leftDoubleClick();

	static void sleep( std::deque<int> args );

	static void moveTo( std::deque<int> args );

	static void sendText( std::deque<int> args );

private:
	static QString getSpecialKey( int& i, std::deque<int>& args );

};