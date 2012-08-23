#pragma once

#include <qsystemtrayicon.h>
#include <qaction.h>
#include <qmenu.h>
#include "calendar.h"

class TraySystem : public QSystemTrayIcon {
	Q_OBJECT

private:
	QMenu* m_menu;
	unsigned m_actionsNumber;
	//void ( TraySystem::*m_funcTrigger )( QAction* );

private:
	void leftClickAction();
	void leftDblClickAction();
	void initContextMenu();

public:
	TraySystem( QString iconPath, QObject* parent );
	void update( QVector<Action*> actions );

private slots:
	void iconActivated( QSystemTrayIcon::ActivationReason reason );
	void actionTrigger( QAction* );

};