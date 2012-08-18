#include "calendar_tools.h"

QToolButton* CalendarTools::AddButton = NULL;
QToolButton* CalendarTools::EditButton = NULL;
QToolButton* CalendarTools::RemoveActionButton = NULL;
QToolButton* CalendarTools::DetachActionButton = NULL;
QToolButton* CalendarTools::UpButton = NULL;
QToolButton* CalendarTools::DownButton = NULL;
QToolButton* CalendarTools::LeftButton = NULL;
QToolButton* CalendarTools::RightButton = NULL;

void CalendarTools::enableForAction() {
	EditButton->setEnabled( true );
	RemoveActionButton->setEnabled( true );
	DetachActionButton->setEnabled( true );
	UpButton->setEnabled( true );
	DownButton->setEnabled( true );
	LeftButton->setEnabled( true );
	RightButton->setEnabled( true );
}

void CalendarTools::disableForAction() {
	EditButton->setEnabled( false );
	RemoveActionButton->setEnabled( false );
	DetachActionButton->setEnabled( false );
	UpButton->setEnabled( false );
	DownButton->setEnabled( false );
	LeftButton->setEnabled( false );
	RightButton->setEnabled( false );
}