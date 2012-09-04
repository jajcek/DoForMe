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
	\class LuaApiEngine lua_api.h "lua_api.h"
	\brief LUA API functions.
	\details Stores all the definitions of API functions available to users. Functions with pattern "prepareX" are the preparing functions
	that are invoked during lua's engine parsing. The functions put the commands (pointers to functions without 'prepare' prefix)
	to the LuaEngine object. See example for LuaEngine.
	\author Jacek Topolski
	\version 1.0
	\date 29.06.2012
*/
class LuaApiEngine {
private:
	/**
		\brief Field that maps string to Key object.
		\details String is a special key text (e.g. {tab} which is equal to tabulator symbol on keyboard),
		whereas key object is a manager for a key on the keyboard. See Key class for more details.
	*/
	static std::map<QString, Key*> m_specialKeys;
	/**
		\brief Field that maps virtual key code to string key.
		\details String is a special key text (e.g. {tab} which is equal to tabulator symbol on keyboard).
	*/
	static std::map<int, std::string> m_vkCodeToKey;

public:
	/**
		\brief Initialize all special keys that will be available to users.
	*/
	static void initSpecialKeys();

	/**
		\brief Gets string key from m_vkCodeToKey map.
	*/
	static std::string getStringKey( int vkCode );
	/**
		\brief Puts changing GUI interval (LuaApiEngie::GUIIntervalChange) command to the LuaEngine.
		\details Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareSetInterval( lua_State* state );
	/**
		\brief Puts watiting (LuaApiEngie::sleep) command to the LuaEngine.
		\details Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareSleep( lua_State* state );

	/**
		\brief Puts left mouse button press command (LuaApiEngine::leftDown) to the LuaEngine.
		\details Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareLeftDown( lua_State* state );
	/**
		\brief Puts right mouse button press command (LuaApiEngine::rightDown) to the LuaEngine.
		\details Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareRightDown( lua_State* state );
	/**
		\brief Puts middle mouse button press command (LuaApiEngine::middleDown) to the LuaEngine.
		\details Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareMiddleDown( lua_State* state );
	/**
		\brief Puts left mouse button press command (LuaApiEngine::leftDownAt) to the LuaEngine.
		\details Comparing to the LuaApiEngine::prepareLeftDown, this version lets user to define a point that the mouse will move to before pressing.
		Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareLeftDownAt( lua_State* state );
	/**
		\brief Puts right mouse button press command (LuaApiEngine::rightDownAt) to the LuaEngine.
		\details Comparing to the LuaApiEngine::prepareRightDown, this version lets user to define a point that the mouse will move to before pressing.
		Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareRightDownAt( lua_State* state );
	/**
		\brief Puts middle mouse button press command (LuaApiEngine::middleDownAt) to the LuaEngine.
		\details Comparing to the LuaApiEngine::prepareMiddleDown, this version lets user to define a point that the mouse will move to before pressing.
		Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareMiddleDownAt( lua_State* state );

	/**
		\brief Puts left mouse button releasing command (LuaApiEngine::leftUp) to the LuaEngine.
		\details Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareLeftUp( lua_State* state );
	/**
		\brief Puts right mouse button releasing command (LuaApiEngine::rightUp) to the LuaEngine.
		\details Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareRightUp( lua_State* state );
	/**
		\brief Puts middle mouse button releasing command (LuaApiEngine::middleUp) to the LuaEngine.
		\details Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareMiddleUp( lua_State* state );
	/**
		\brief Puts left mouse button releasing command (LuaApiEngine::leftUpAt) to the LuaEngine.
		\details Comparing to the LuaApiEngine::prepareLeftUp, this version lets user to define a point that the mouse will move to before releasing.
		Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareLeftUpAt( lua_State* state );
	/**
		\brief Puts right mouse button releasing command (LuaApiEngine::rightUpAt) to the LuaEngine.
		\details Comparing to the LuaApiEngine::prepareRightUp, this version lets user to define a point that the mouse will move to before releasing.
		Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareRightUpAt( lua_State* state );
	/**
		\brief Puts middle mouse button releasing command (LuaApiEngine::middleUpAt) to the LuaEngine.
		\details Comparing to the LuaApiEngine::prepareMiddleUp, this version lets user to define a point that the mouse will move to before releasing.
		Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareMiddleUpAt( lua_State* state );

	/**
		\brief Puts left mouse button click command (LuaApiEngine::leftClick) to the LuaEngine.
		\details Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareLeftClick( lua_State* state );
	/**
		\brief Puts right mouse button click command (LuaApiEngine::rightClick) to the LuaEngine.
		\details Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareRightClick( lua_State* state );
	/**
		\brief Puts middle mouse button click command (LuaApiEngine::middleClick) to the LuaEngine.
		\details Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareMiddleClick( lua_State* state );
	/**
		\brief Puts left mouse button click command (LuaApiEngine::leftClickAt) to the LuaEngine.
		\details Comparing to the LuaApiEngine::prepareLeftUp, this version lets user to define a point that the mouse will move to before clicking.
		Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareLeftClickAt( lua_State* state );
	/**
		\brief Puts right mouse button click command (LuaApiEngine::rightClickAt) to the LuaEngine.
		\details Comparing to the LuaApiEngine::prepareRightUp, this version lets user to define a point that the mouse will move to before clicking.
		Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareRightClickAt( lua_State* state );
	/**
		\brief Puts middle mouse button click command (LuaApiEngine::middleClickAt) to the LuaEngine.
		\details Comparing to the LuaApiEngine::prepareMiddleUp, this version lets user to define a point that the mouse will move to before clicking.
		Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareMiddleClickAt( lua_State* state );

	/**
		\brief Puts left mouse button double click command (LuaApiEngine::leftDoubleClick) to the LuaEngine.
		\details Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareLeftDoubleClick( lua_State* state );
	/**
		\brief Puts left mouse button double click command (LuaApiEngine::leftDoubleClickAt) to the LuaEngine.
		\details Comparing to the LuaApiEngine::prepareLeftDoubleClick, this version lets user to define a point that the mouse will move to before pressing.
		Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareLeftDoubleClickAt( lua_State* state );

	/**
		\brief Puts mouse move command (LuaApiEngine::moveTo) to the LuaEngine.
		\details Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareMoveTo( lua_State* state );

	/**
		\brief Puts sending text command (LuaApiEngine::sendText) to the LuaEngine.
		\details See LuaApiEngine::sendText( std::deque<int> args ) for more details about sending text.
		Parameter state is not explicitly used. The function is passed as a pointer to the lua's engine.
		prepareX functions load arguments from the api function in scripts and put the appriopriate command to the lua's engine (LuaEngine).
		\return Number of results on the lua's stack (in this class this value is always zero).
	*/
	static int prepareSendText( lua_State* state );

	// --------------------------------------------------------------------------------------------------

	/**
		\brief Executes left mouse button press.
	*/
	static void leftDown();
	/**
		\brief Executes right mouse button press.
	*/
	static void rightDown();
	/**
		\brief Executes middle mouse button press.
	*/
	static void middleDown();

	/**
		\brief Executes left mouse button release.
	*/
	static void leftUp();
	/**
		\brief Executes right mouse button release.
	*/
	static void rightUp();
	/**
		\brief Executes middle mouse button release.
	*/
	static void middleUp();

	/**
		\brief Executes left mouse button click.
	*/
	static void leftClick();
	/**
		\brief Executes right mouse button click.
	*/
	static void rightClick();
	/**
		\brief Executes middle mouse button click.
	*/
	static void middleClick();

	/**
		\brief Executes left mouse button double click.
	*/
	static void leftDoubleClick();

	/**
		\brief Executes changing GUI interval command.
		\param[in] args Array which contains arguments for the function. In this case there's only one argument.
	*/
	static void setInterval( std::deque<int> args );
	/**
		\brief Executes waiting command.
		\param[in] args Array which contains arguments for the function. In this case there's only one argument.
	*/
	static void sleep( std::deque<int> args );

	/**
		\brief Executes mouse movement.
		\param[in] args Array which contains arguments for the function. In this case there are two arguments.
	*/
	static void moveTo( std::deque<int> args );

	/**
		\brief Executes sending text.
		\param[in] args Array which contains arguments for the function. In this case every element is a symbol from the given text.
	*/
	static void sendText( std::deque<int> args );

private:
	/**
		\brief Helper function that gets text from {} brackets from LuaApiEngine::sendText() argument.
		\param[in,out] specialKey Variable in which we save text taken from {} brackets.
		\param[in,out] args Kind of vector which keeps all symbol from the text from LuaApiEngine::sendText() argument.
		\return Number of read symbols.
	*/
	static int getSpecialKey( QString& specialKey, std::deque<int>& args );

};