#include "commands_manager.h"

void CommandsManager::addCommand( void ( *pCmd )( std::deque<int> ), std::deque<int> args ) {
	m_commands.push_back( pCmd );
	m_args.push_back( args );
}

void CommandsManager::executeNext() {
	void ( *_pCmd )( std::deque<int> ) = m_commands.front();
	std::deque<int> _args = m_args.front();

	_pCmd( _args );

	m_commands.pop_front();
	m_args.pop_front();
}

bool CommandsManager::isEmpty() const {
	return m_commands.empty();
}