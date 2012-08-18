#pragma once

#include <qtoolbutton.h>

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
		\brief This method is called when an action has been selected on the calendar to enable buttons for operating on actions.
		\details Beware that when in a day there are more than one actions, thic method will be called
		when an action has been selected on a actions list.
	*/
	static void enableForAction();
	/**
		\brief This method is called when an actions has been unselected.
		\details Action is unselected e.g. when a user selected date where there are no actions at all.
	*/
	static void disableForAction();
};