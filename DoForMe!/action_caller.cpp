#include "action_caller.h"

ActionCaller* ActionCaller::ms_object = NULL;

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

ActionCaller* ActionCaller::getInstance() {
	if( !ms_object )
		ms_object = new ActionCaller();

	return ms_object;
}

void ActionCaller::setActions( QVector<Action*> actions ) {
	qDebug( "ActionCaller::setActions()" );

	m_actions = actions;

	// if the vector is empty there's nothing to do
	if( !m_actions.isEmpty() ) {
		// sort the vector by the action's time
		sortByTime( m_actions );

		// get milliseconds until the closest action
		int _milliseconds = -1;
		do {
			QTime _timeForFirstAction = m_actions.at( 0 )->getTime();
			_milliseconds = QTime::currentTime().msecsTo( _timeForFirstAction );

			if( _milliseconds < 0 ) {
				m_actions.remove( 0 );
			} else {
				break;
			}
		} while( _milliseconds < 0 && !m_actions.isEmpty() );

		// start the timer to invoke actions at the calculated time
		if( _milliseconds >= 0 )
			m_caller.start( _milliseconds, this );
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

	// execute the action
	Action* _pAction = m_actions.at( 0 );
	LuaEngine::getInstance()->run( _pAction->getScript()->getCode().toStdString().c_str() );
	m_actions.remove( 0 );

	// calculate time for the next action
	if( !m_actions.isEmpty() ) {
		QTime _timeForFirstAction = m_actions.at( 0 )->getTime();
		int _milliseconds = QTime::currentTime().msecsTo( _timeForFirstAction );
		m_caller.start( _milliseconds, this );
	} else {
		m_caller.stop();
	}

	m_tray->update( m_actions );
}