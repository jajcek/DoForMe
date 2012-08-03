#pragma once

#include <Windows.h>
#include <qstring.h>
#include <vector>

/**
	\class Key key.h "key.h"
	\brief Stores key code and its mode.
	\details The class is used to store keys that are available to users via sendText() api function. 
	The key is converted to INPUT structure to be put into SendInput function.
	\author Jacek Topolski
	\version 1.0
	\date 28.07.2012
*/
class Key {
private:
	/**
		\brief Virtual code for the key.
	*/
	unsigned short m_keyCode;
	/**
		\brief Mode for the key.
		\details See Key::MODE for more details.
	*/
	unsigned short m_mode;

public:
	/**
		\brief Mode for the key.
		\details The value is set to Key::m_mode variable.
		
		Possible value:
		Key::CLICK -> Down + Up,
		Key::DOWN -> Down,
		Key::UP -> UP.
	*/
	enum MODE { CLICK = 0, DOWN, UP };

public:
	/**
		\brief Creates new key with the given key code and mode.
		\details See Key::MODE for more details about modes.
		\param[in] keyCode Virtual key code.
		\param[in] mode Mode that the key is created for.
	*/
	Key( unsigned short keyCode, unsigned short mode = 0 );

	/**
		\brief Inserts new key to the specified vector of INPUT objects.
		\param[in,out] inputs Vector of INPUT objects which the key is inserted to.
	*/
	void insertKeyTo( std::vector<INPUT>& inputs );
	/**
		\brief Inserts given key with its mode to the specified vector of INPUT objects.
		\param[in] keyCode Virtual key code.
		\param[in] mode Mode of the key.
		\param[in,out] inputs Vector of INPUT objects which the key is inserted to.
	*/
	static void insertKeyTo( unsigned short keyCode, unsigned short mode, std::vector<INPUT>& inputs );
	
	/**
		\brief Sets virtual key code.
		\param[in] keyCode Virtual key code to be set.
	*/
	void setKeyCode( unsigned short keyCode );
	/**
		\return Virtual key code.
	*/
	unsigned short getKeyCode() const;

	/**
		\brief Sets mode for a key.
		\param[in] mode Mode of the key.
	*/
	void setMode( unsigned short mode );
	/**
		\return Mode for the key.
	*/
	unsigned short getMode() const;
};