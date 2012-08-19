#pragma once

#include <qtoolbutton.h>
#include "action.h"

/**
	\class CalendarTools calendar_tools.h "calendar_tools.h"
	\brief Pointers for calendar tools.
	\details Tools used for editing, removing, detaching and positioning actions on the calendar.
	\author Jacek Topolski
	\version 1.0
	\date 18.08.2012
*/
struct CalendarTools {
	/**
		\brief Pointer to the "Add" button.
	*/
	static QToolButton* AddButton;
	/**
		\brief Pointer to the "Edit" button.
	*/
	static QToolButton* EditButton;
	/**
		\brief Pointer to the "Remove" button on the calendar (not the one next to scripts list).
	*/
	static QToolButton* RemoveActionButton;
	/**
		\brief Pointer to the "Detach" button.
	*/
	static QToolButton* DetachActionButton;
	/**
		\brief Pointer to the "Up" button (blue up arrow).
	*/
	static QToolButton* UpButton;
	/**
		\brief Pointer to the "Down" button (blue down arrow).
	*/
	static QToolButton* DownButton;
	/**
		\brief Pointer to the "Left" button (blue left arrow).
	*/
	static QToolButton* LeftButton;
	/**
		\brief Pointer to the "Right" button (blue right arrow).
	*/
	static QToolButton* RightButton;

	/**
		\brief This method is called when an action without repetitions has been selected on the calendar to enable buttons for operating on actions.
		\details This method will be called when there is only one action on actions list.
	*/
	static void enableForAction( Action* action );
	/**
		\brief This method is called when an action with repetitions has been selected on the calendar to enable buttons for operating on actions.
		\details This method will be called when  there are more than once actions on actions list.
	*/
	static void disableForAction();
};