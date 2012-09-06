#pragma once

#include <qbasictimer.h>
#include "lua_engine.h"
#include "action.h"
#include "tray_system.h"
#include "msg_box_with_duration.h"
#include "reminder_settings.h"

/**
	\class ActionCaller action_caller.h "action_caller.h"
	\brief Singleton used for calling actions from the calendar.
	\details ActionCaller::getInstance returns the only object. By using ActionCaller::setActions we are able to
	set actions that will be called by the ActionCaller's timer. The timer is set when settings action in ActionCaller:setAction method.
	\author Jacek Topolski
	\version 1.0
	\date 28.07.2012
*/
class ActionCaller : public QObject {
	Q_OBJECT

private:
	/**
		\brief Pointer to the object of this class.
	*/
	static ActionCaller* ms_object;
	/**
		\brief Vector of actions waiting for executing.
	*/
	QVector<Action*> m_actions;
	/**
		\brief Timer used for calling actions.
		\details It calls ActionCaller::executeNextAction method which uses the vector mentioned above.
	*/
	QBasicTimer m_caller;
	/**
		\brief Pointer to the TraySystem object.
		\details The object is needed to perfom updating content of the tray context menu.
	*/
	TraySystem* m_tray;
	/**
		\brief Simple constructor which simply sets AcionCaller::m_tray to NULL.
		\details The constructor has been put into the private section to prevent creating instances from the class (because the class is a singleton).
	*/
	ActionCaller();

private:
	/**
		\brief Helper method which sorts vector of actions by time and id.
		\details The actions are sorted from the earliest time. If the time is equal the Action::getId value is used (taking lower id at first).
		\param[in] actions Vector of actions to sort.
	*/
	void sortByTime( QVector<Action*>& actions );

public:
	/**
		\return Pointer to the instance of the class.
	*/
	static ActionCaller* getInstance();
	/**
		\brief Sets actions for executing.
		\details The method calculates time (in milliseconds) for the ActionCaller::m_caller timer to the closest action that will be executed.
		\param[in] actions Vector of actions to set.
	*/
	void setActions( QVector<Action*> actions );
	/**
		\return Vector of actions left. Beware that if you call ActionCaller::executeNextAction method, the action won't be in the vector anymore. See ActionCaller::executeNextAction for more details.
	*/
	QVector<Action*> getActions() const;
	/**
		\brief Sets pointer to the tray system object. Updating of the tray is in the ActionCaller::setActions and ActionCaller::timerEvent which is invoked by the ActionCaller::m_caller.
		\param[in] tray Pointer to the tray system object.
	*/
	void setTrayToUpdate( TraySystem* tray );
	/**
		\brief Method which is invoked by the ActionCaller::m_caller timer.
	*/
	void timerEvent( QTimerEvent* e );
	/**
		\brief Executes next action from the vector of actions.
		\details The action which will be executed during the method will be removed from the vector of actions.
	*/
	void executeNextAction();

};