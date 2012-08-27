#pragma once

#include <qbasictimer.h>
#include "lua_engine.h"
#include "action.h"
#include "tray_system.h"

class ActionCaller : public QObject {
	Q_OBJECT

private:
	static ActionCaller* ms_object;
	QVector<Action*> m_actions;
	QBasicTimer m_caller;
	TraySystem* m_tray;
	bool m_isExecuting;

	ActionCaller();

private:
	void sortByTime( QVector<Action*>& actions );

public:
	static ActionCaller* getInstance();
	void setActions( QVector<Action*> actions );
	QVector<Action*> getActions() const;
	void setTrayToUpdate( TraySystem* tray );
	void timerEvent( QTimerEvent* e );
	void executeNextAction();

};