#pragma once

#include <qtoolbutton.h>

struct CalendarTools {
	static QToolButton* AddButton;
	static QToolButton* EditButton;
	static QToolButton* RemoveActionButton;
	static QToolButton* DetachActionButton;
	static QToolButton* UpButton;
	static QToolButton* DownButton;
	static QToolButton* LeftButton;
	static QToolButton* RightButton;

	static void enableForAction();
	static void disableForAction();
};