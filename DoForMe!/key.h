#pragma once

#include <Windows.h>
#include <qstring.h>
#include <vector>

class Key {
private:
	unsigned short m_keyCode;
	unsigned short m_mode;

public:
	enum MODE { CLICK = 0, DOWN, UP };

public:
	Key( unsigned short keyCode, unsigned short mode = 0 );

	void insertKeyTo( std::vector<INPUT>& inputs );
	static void insertKeyTo( unsigned short keyCode, unsigned short mode, std::vector<INPUT>& inputs );
	
	void setKeyCode( unsigned short keyCode );
	unsigned short getKeyCode() const;

	void setMode( unsigned short mode );
	unsigned short getMode() const;
};