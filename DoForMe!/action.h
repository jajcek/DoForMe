#pragma once

#include <qstring.h>

/**
	\class Action action.h "action.h"
	\brief Engine for maintaing LUA's API commands.
	\details Objects of this class load scripts, check their grammar correctness and store the commands for further executing.
	\author Jacek Topolski
	\version 1.0
	\date 6.07.2012
*/
class Action {
private:
	QString m_path;
	QString m_fileName;
	QString m_code;

public:
	Action();
	~Action();

	void setPath( QString path );
	QString getPath() const;

	void setFileName( QString fileName );
	QString getFileName() const;

	void setCode( QString code );
	QString getCode() const;
};