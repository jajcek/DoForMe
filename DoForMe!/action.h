#pragma once

#include <qstring.h>
#include <QTime>
#include "action_settings.h"
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
	ActionSettings m_actionSettings;
	QTime m_time;
	bool m_isXDays;
	int m_XDays;
	int m_days;
	bool m_isHighlighted;
	QVector<QDate> m_excludedDates;

public:
	Action( Action* action );
	Action( Script* pScript, const ActionSettings& settings );

	void setSetting( const ActionSettings& settings );

	void setScript( Script* pScript );
	Script* getScript() const;

	void excludeDate( QDate date );
	bool isExcluded( QDate date ) const;

	int getHours() const;
	int getMinutes() const;
	int getSeconds() const;
	QTime getTime() const;

	bool isXDays() const;
	int getXDays() const;

	int getDays() const;

	void setHighlight( bool state );
	bool isHighlighted() const;
};