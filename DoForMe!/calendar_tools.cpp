#include "calendar_tools.h"

QToolButton* CalendarTools::AddButton = NULL;
QToolButton* CalendarTools::EditButton = NULL;
QToolButton* CalendarTools::RemoveActionButton = NULL;
QToolButton* CalendarTools::DetachActionButton = NULL;
QToolButton* CalendarTools::UpButton = NULL;
QToolButton* CalendarTools::DownButton = NULL;
QToolButton* CalendarTools::LeftButton = NULL;
QToolButton* CalendarTools::RightButton = NULL;
QAction* CalendarTools::NewMenu = NULL;
QAction* CalendarTools::EditMenu = NULL;
QAction* CalendarTools::RemoveMenu = NULL;
QAction* CalendarTools::DetachMenu = NULL;
QAction* CalendarTools::MoveLeftMenu = NULL;
QAction* CalendarTools::MoveUpMenu = NULL;
QAction* CalendarTools::MoveDownMenu = NULL;
QAction* CalendarTools::MoveRightMenu = NULL;

void CalendarTools::enableForAction( Action* action ) {
	EditButton->setEnabled( true );
	EditMenu->setEnabled( true );
	RemoveActionButton->setEnabled( true );
	RemoveMenu->setEnabled( true );
	if( action->isXDays() || action->getDays() ) {
		DetachActionButton->setEnabled( true );
		DetachMenu->setEnabled( true );
	} else {
		DetachActionButton->setEnabled( false );
		DetachMenu->setEnabled( false );
	}
	UpButton->setEnabled( true );
	MoveUpMenu->setEnabled( true );
	DownButton->setEnabled( true );
	MoveDownMenu->setEnabled( true );
	LeftButton->setEnabled( true );
	MoveLeftMenu->setEnabled( true );
	RightButton->setEnabled( true );
	MoveRightMenu->setEnabled( true );
}

void CalendarTools::disableForAction() {
	EditButton->setEnabled( false );
	EditMenu->setEnabled( false );
	RemoveActionButton->setEnabled( false );
	RemoveMenu->setEnabled( false );
	DetachActionButton->setEnabled( false );
	DetachMenu->setEnabled( false );
	UpButton->setEnabled( false );
	MoveUpMenu->setEnabled( false );
	DownButton->setEnabled( false );
	MoveDownMenu->setEnabled( false );
	LeftButton->setEnabled( false );
	MoveLeftMenu->setEnabled( false );
	RightButton->setEnabled( false );
	MoveRightMenu->setEnabled( false );
}