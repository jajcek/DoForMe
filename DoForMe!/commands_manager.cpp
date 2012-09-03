#include "commands_manager.h"

void CommandsManager::addCommand( void ( *pCmd )( std::deque<int> ), std::deque<int> args ) {
	m_commands.push_back( pCmd );
	m_args.push_back( args );
}

void CommandsManager::executeNext() {
	void ( *_pCmd )( std::deque<int> ) = m_commands.front();
	std::deque<int> _args = m_args.front();

	m_commands.pop_front();
	m_args.pop_front();

	if( _pCmd != NULL )
		_pCmd( _args );
	else { // new action - we will show dialog box which informs about it
		// get name of the script by converting ascii codes to chars
		QString _actionName = "";
		int _size = _args.size();
		for( int i = 0; i < _size; ++i ) {
			_actionName += (char)_args.front();
			_args.pop_front();
		}

		// show dialog with notification of the new action
		if( ReminderDialog::getInstance()->isOn() ) {
			MsgBoxWithDuration _msg( "Information", "An action \"" + _actionName
									 + "\" is coming up. What to do?", ReminderDialog::getInstance()->timeEarlier() );
			_msg.exec();

			if( _msg.buttonClicked() == MsgBoxWithDuration::IGNORING ) {
				// remove the command until next NULL (= until next action)
				do {
					_pCmd = m_commands.front();
					m_commands.pop_front();
					m_args.pop_front();
					if( !m_commands.empty() )
						_pCmd = m_commands.front();
				} while( _pCmd != NULL && !m_commands.empty() );
			}
		}
	}
}

bool CommandsManager::isEmpty() const {
	return m_commands.empty();
}

void CommandsManager::clearCommands() {
	m_commands.clear();
	m_args.clear();
}