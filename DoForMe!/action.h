#pragma once

#include <qstring.h>
#include <QTime>
#include "action_settings.h"
#include "script.h"
#include "scripts_manager.h"

/**
	\class Action action.h "action.h"
	\brief Data for action that has been created for calendar.
	\author Jacek Topolski
	\version 1.0
	\date 28.07.2012
*/
class Action {
private:
	/**
		\brief Pointer to script object which is used in the action. See Script class for more details.
	*/
	Script* m_pScript;
	/**
		\brief Time which the action will be called at.
	*/
	QTime m_time;
	/**
		\brief Value that determines if the actions has "every X days" repetitions.
	*/
	bool m_isXDays;
	/**
		\brief How many days have to pass to invoke the action again.
	*/
	int m_XDays;
	/**
		\brief which days the action is invoked on.
	*/
	char m_days;
	/**
		\brief Whether the action is highlighted (when a user selects the action on the calendar).
	*/
	bool m_isHighlighted;
	/**
		\brief What dates should be excluded from the repetitions
	*/
	QVector<QDate> m_excludedDates;
	/**
		\brief Id of the action. If there are actions that might be called at the same time
		the action with lower id will be performed first.
	*/
	int m_id;
	/**
		\brief Value used for assigning ids for actions. See Action::m_id.
	*/
	static int m_actionNumber;
	/**
		\brief Date which represents main action from which the repetition are created.
	*/
	QDate m_mainDate;

private:
	/**
		\brief Sets id for the action.
		\param[in] id Id to be set to the action.
	*/
	void setId( int id );
	/**
		\return Next free id for the action.
	*/
	int nextId();

public:
	/**
		\brief Some kind of copy constructor which creates action on the grounds of another action but eliminates all of the repetitions.
		\param[in] pAction Action to be copied.
	*/
	Action( Action* pAction );
	/**
		\brief Creates action for the given date with the specified settings.
		\param[in] mainDate Date which the action will be added on.
		\param[in] settings All settings for the action (repetitions, time etc.). See ActionSettings class for more details.
	*/
	Action( QDate mainDate, const ActionSettings& settings );
	/**
		\brief Sets settings for the action. See ActionSettings class for more details.
		\param[in] settings Settings for the action.
	*/
	void setSetting( const ActionSettings& settings );
	/**
		\brief Sets script that the action will be invoking.
		\param[in] pScript Pointer to the script object.
	*/
	void setScript( Script* pScript );
	/**
		\return Pointer to the script object that the action uses.
	*/
	Script* getScript() const;
	/**
		\brief Excludes date from repetitions.
		\param[in] date Date that needs to be excluded.
	*/
	void excludeDate( QDate date );
	/**
		\brief Check if the given date is exlcluded.
		\return Value which determines if the date is excluded.
	*/
	bool isExcluded( QDate date ) const;
	/**
		\brief Sets vector of excluded dates. Beware that the method will override the existing excluded dates.
		\param[in] excludedDates Vector of dates that will be excluded.
	*/
	void setExcludedDates( QVector<QDate> excludedDates );
	/**
		\return Vector of the excluded dates.
	*/
	QVector<QDate> getExcludedDates() const;
	/**
		\return Hours from the time at which the action will be performed.
	*/
	int getHours() const;
	/**
		\return Minutes from the time at which the action will be performed.
	*/
	int getMinutes() const;
	/**
		\return Seconds from the time at which the action will be performed.
	*/
	int getSeconds() const;
	/**
		\return Hours as a string in two-digit format from the time at which the action will be performed.
	*/
	QString getHoursHH() const;
	/**
		\return Minutes as a string in two-digit format from the time at which the action will be performed.
	*/
	QString getMinutesMM() const;
	/**
		\return Seconds as a string in two-digit format from the time at which the action will be performed.
	*/
	QString getSecondsSS() const;
	/**
		\return Time at which the action will be performed.
	*/
	QTime getTime() const;
	/**
		\return Value which determines if the action has a "every X days" repetition turned on.
	*/
	bool isXDays() const;
	/**
		\return Number of days that needs to pass to execute the action again. Works only if the Action::isXDays() returns true.
	*/
	int getXDays() const;
	/**
		\return Mask for days on which the action will be performed. See ActionSettings::MONDAY for more details.
	*/
	char getDays() const;
	/**
		\brief Sets the status of the highlighting action.
		\param[in] state State of the highlighting.
	*/
	void setHighlight( bool state );
	/**
		\return Checks whether the action is highlighted.
	*/
	bool isHighlighted() const;
	/**
		\return Id of the action.
	*/
	int getId() const;
	/**
		\brief Main date for the action from which the repetitions will be created.
		\param[in] mainDate Main date for the action.
	*/
	void setMainDate( QDate mainDate );
	/**
		\return Main date for the action from which the repetitions are created.
	*/
	QDate getMainDate() const;
};