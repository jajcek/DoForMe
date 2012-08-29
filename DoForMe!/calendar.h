#pragma once

#include <qcalendarwidget.h>
#include <qpainter.h>
#include <qvector.h>
#include <qmap.h>
#include <qlistwidget.h>
#include <qbasictimer.h>
#include "action.h"
#include "action_settings.h"
#include "database.h"
#include "calendar_tools.h"

/**
	\class ActionsCalendar calendar.h "calendar.h"
	\brief Stores all information about added actions as well as enables possibility to operate on them.
	\details The class is derived from the QCalendarWidget class. In this class the paintCell method has been overriden to make a unique way
	to paint cells (numbers of actions in a day, exclamation marks for conflicts, highlighting actions etc.).
	\author Jacek Topolski
	\version 1.0
	\date 28.07.2012
*/
class ActionsCalendar : public QCalendarWidget {
	Q_OBJECT

private:
	/**
		\brief Selected date on the calendar.
	*/
	QDate m_selectedDate;
	/**
		\brief Number of month in a year that is displayed.
	*/
	int m_displayedMonth;
	/**
		\brief Current year that is displayed on the calendar.
	*/
	int m_displayedYear;
	/**
		\brief Pointer to the list where actions for the selected date are listed.
	*/
	static QTableWidget* m_list;
	/**
		\brief Pointer to the currently selected action.
	*/
	Action* m_pCurrAction;
	/**
		\brief Map of all actions added to the calendar. The structure maps date into vector of actions for this date.
		\details The repetitions are not available in this map.
	*/
	QMap<QDate, QVector<Action*> > m_actionsAll;
	/**
		\brief Structure that maps date into vector of actions for this date.
		\details Similar structure to the ActionsCalendar::m_actionsAll with difference that
		in this map we store actions (also with its repetitions) only for the currently selected month and
		few days from previous and next month (because these days are visible on the calendar).
	*/
	QMap<QDate, QVector<Action*> > m_actionsInMonth;

public:
	/**
		\brief Values used to determine direction for the action moving.
	*/
	enum DIR { UP = 0, DOWN, LEFT, RIGHT };

private:
	/**
		\brief Draws text "X actions" if there are any actions.
		\param[in] painter Pointer to the engine which enables possibility to draw.
		\param[in] rect Coordinates of the rect in which we will be drawing.
		\param[in] actionsNumber Number of actions.
	*/
	void drawActionsNum( QPainter* painter, const QRect& rect, unsigned actionsNumber ) const;
	/**
		\brief Draws exclamation mark is there are any conflicts.
		\details Conflict happens when there are at least two actions added for the same time.
		\param[in] painter Pointer to the engine which enables possibility to draw.
		\param[in] rect Coordinates of the rect in which we will be drawing.
	*/
	void drawExclamation( QPainter* painter, const QRect& rect ) const;
	/**
		\brief Sets repetitions for an action.
		\param[in] date Main date for the action. From this date the repetition will be created.
		\param[in] action Pointer to the action which we want to repeat.
	*/
	void setRepetition( QDate date, Action* action );
	/**
		\brief Looks for an index of action in the vector of actions in ActionsCalendar::m_actionsAll.
		\details The method searches the action in ActionsCalendar::m_actionsAll by using as a key Action::getMainDate method.
		\param[in] action Pointer to the action we want to find.
		\return Index of the action.
	*/
	int findIndexOf( Action* action );
	/**
		\brief Moves excluded dates.
		\details This is a helper method using in connection with ActionsCalendar::moveCurrAction.
		If you move the action you also have to move the excluded days in the same direction.
		\param[in] action Pointer to the action of which we want to move excluded dates.
		\param[in] days Number of days to add to the excluded dates. See ActionsCalendar::moveCurrAction for more details.
	*/
	void moveExcludedDates( Action* action, const int days );
	/**
		\brief Calculates time (in milliseconds) until midnight.
		\details It is used for refreshing calendar at midnight.
	*/
	int calcTimeForNewDay() const;

public:
	/**
		\brief Constructs calendar object.
		\details This constructor sets fundamental parts for the QCalendarWidget like
		language, colours, grid, cursor as well as selects current date.
		\param[in] pParent Parent widget which the calendar belongs to.
	*/
	ActionsCalendar( QWidget* pParent );
	/**
		\brief Removes all actions by freeing its memory.
	*/
	~ActionsCalendar();
	/**
		\brief Adds action to the calendar structures.
		\details These structures are: ActionsCalendar::m_actionsAll (always) and ActionsCalendar::m_actionsInMonth
		(on condition that this date in not an excluded date from the action).
		\param[in] date Date which the action will be added to.
		\param[in] action Pointer to the action to add.
	*/
	void addAction( QDate date, Action* action );
	/**
		\brief Looks for an action with the given id.
		\param[in] id Id of the searched action.
		\param[in] forSelectedDate It will search only in the selected date (see ActionsCalendar::m_selectedDate)
		in ActionsCalendar::m_actionsInMonth if set to true, otherwise it will be searching over the whole keys in ActionsCalendar::m_actionsAll.
		\return Pointer to the searched action.
	*/
	Action* getActionById( int id, bool forSelectedDate = true ) const;
	/**
		\return Pointer to the currently selected action.
	*/
	Action* getCurrentAction() const;
	/**
		\brief Detaches action from the repetition of the currently selected action.
	*/
	void detachCurrentAction();
	/**
		\brief Removes currently selected action.
		\details Note that this doesn't remove all of the repetitions, but only the selected by the cursor,
		so actually it just sets new date into the excluded dates.
		If you want to remove also all repetitions use ActionsCalendar::removeCurrentActions method.
	*/
	void removeCurrentAction();
	/**
		\brief Removes action and its repetitions.
		\details This method removes all of the highlighted actions and frees its memory
		(actually it's only one action in the memory and only pointers are repeated).
	*/
	void removeCurrentActions();
	/**
		\brief Removes all actions by freeing its memory.
	*/
	void removeAllActions();
	/**
		\brief Moves currently selected action to the given direction.
		\param[in] direction Direction of the moving. See ActionsCalendar::DIR enumeration for details.
	*/
	void moveCurrAction( int direction );
	// only for the current month!
	/**
		\param[in] date Date from which we want to get actions.
		\return Vector of all actions for a specified date. Beware that this looks for actions
		only in the displayed month and visible days from other months.
	*/
	QVector<Action*> getActionsForDate( QDate date ) const;
	/**
		\brief Sets action as a currently selected action.
		\param[in] action Pointer to the action you want to set.
	*/
	void setCurrentAction( Action* action );
	/**
		\brief Sets list on which the actions for the selected date will be listed.
		\param[in] list Pointer to the QTableWidget list.
	*/
	static void setList( QTableWidget* list );
	/**
		\return Date that is currently selected.
	*/
	QDate getSelectedDate() const;
	/**
		\brief Refreshes all actions on the calendar
		\details  Refreshing is done by clearing ActionsCalendar::m_actionsInMonth
		and recreting it on the grounds of ActionsCalendar::m_actionsAll by using ActionsCalendar::setRepetitions method.
	*/
	void refreshRepetitions();
	/**
		\brief Saves all actions into database. See Database class for more details.
	*/
	void saveData() const;
	/**
		\brief Loads actions data from database. See Database class for more details.
	*/
	void loadData();
	/**
		\brief Checks if the script is used in any action added to calendar.
		\param[in] pScript Pointer to the script.
		\retval True if the given script is used by some actions added to calendar.
		\retval False if the given script is not used by any action added to calendar.
	*/
	bool isScriptUsed( Script* pScript ) const;
	/**
		\brief Removes all actions and its repetitions that uses given script.
		\param[in] pScript Pointer to the script object.
	*/
	void removeActionsUsingScript( Script* pScript );

protected:
	/**
		\brief Overriden method from QCalendarWidget. It is responsible for painting each individual cell of the calendar.
		\param[in] painter Pointer to the engine that enables possibility to draw on screen.
		\param[in] rect Coordinates of the rect are used to specify where to draw.
		\param[in] date Date for the currently drawn cell.
	*/
	void paintCell( QPainter* painter, const QRect& rect, const QDate& date ) const;

protected slots:
	/**
		\brief Selects date on the calendar.
		\param[in] date Date to select.
	*/
	void selectDate( const QDate& date );
	/**
		\brief Sets the displayed calendar page with the given year and month.
		\param[in] year Year.
		\param[in] month Month.
	*/
	void setCurrentPage( int year, int month );
};