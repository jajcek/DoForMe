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
	QMap<QString, QAction*> m_qtActions;
	//void ( TraySystem::*m_funcTrigger )( QAction* );

private:
	void leftClickAction();
	void leftDblClickAction();
	void open();
	void info();
	void exit();

public:
	TraySystem( QString iconPath, QObject* parent );
	void update( QVector<Action*> actions );
	void addQAction( QAction* action );

private slots:
	void iconActivated( QSystemTrayIcon::ActivationReason reason );
	void actionTrigger( QAction* );

};