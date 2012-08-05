#pragma once

#include <qstring.h>
#include <QTime>
#include "script.h"

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
	Script* m_pScript;
	QDate m_date;
	QTime m_time;

public:
	Action( Script* pScript, QDate date, QTime time );

	void setScript( Script* pScript );
	Script* getScript() const;

	void setDate( QDate date );
	QDate getDate() const;

	void setTime( QTime time );
	QTime getTime() const;

};