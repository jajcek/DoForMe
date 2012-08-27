#include "action_caller.h"

ActionCaller* ActionCaller::ms_object = NULL;

ActionCaller::ActionCaller() : m_tray( NULL ), m_isExecuting( false ) {}

void ActionCaller::sortByTime( QVector<Action*>& actions ) {
	QVector<Action*> _out;

	// bubble sort
	while( !actions.isEmpty() ) {
		int _pos = 0;
		QTime _minTime = actions.at( 0 )->getTime();
		for( int i = 1; i < actions.size(); ++i ) {
			QTime _time = actions.at( i )->getTime();
			if( _time < _minTime ) {
				_minTime = _time;
				_pos = i;
			}
		}

		_out.push_back( actions.at( _pos ) );
		actions.remove( _pos );
	}

	actions = _out;
}

void ActionCaller::executeNextAction() {
	Action* _pAction = m_actions.at( 0 );
	LuaEngine::getInstance()->run( _pAction->getScript()->getCode().toStdString().c_str() );
	m_actions.remove( 0 );
}

ActionCaller* ActionCaller::getInstance() {
	if( !ms_object )
		ms_object = new ActionCaller();

	return ms_object;
}

void ActionCaller::setActions( QVector<Action*> actions ) {
	qDebug( "ActionCaller::setActions()" );

	// set pending actions for the current day
	for( int i = 0; i < actions.size(); ++i )
		if( actions.at( i )->getTime() > QTime::currentTime() )
			m_actions.push_back( actions.at( i ) );

	// if the vector is empty there's nothing to do
	if( !m_actions.isEmpty() ) {
		// sort the vector by the action's time
		sortByTime( m_actions );

		// get milliseconds until the closest action
		int _milliseconds = -1;
		do {
			QTime _timeForFirstAction = m_actions.at( 0 )->getTime();
			_milliseconds = QTime::currentTime().msecsTo( _timeForFirstAction );

			if( _milliseconds >= 0 ) {
				m_caller.start( _milliseconds, this );
				break;
			}
		} while( !m_actions.isEmpty() );			
	}

	// set actions for the context menu in the tray icon
	m_tray->update( m_actions );
}

QVector<Action*> ActionCaller::getActions() const {
	return m_actions;
}

void ActionCaller::setTrayToUpdate( TraySystem* tray ) {
	m_tray = tray;
}

void ActionCaller::timerEvent( QTimerEvent* e ) {
	qDebug( "ActionTimer::timerEvent()" );

	// calculate time for the next action
	int _milliseconds = -1;
	while( _milliseconds < 0 && !m_actions.isEmpty() ) {
		executeNextAction();

		if( !m_actions.isEmpty() ) {
			QTime _timeForFirstAction = m_actions.at( 0 )->getTime();
			_milliseconds = QTime::currentTime().msecsTo( _timeForFirstAction );
			if( _milliseconds < 0 )
				continue;
			m_caller.start( _milliseconds, this );
		} else {
			m_caller.stop();
		}
	}

	m_tray->update( m_actions );
}