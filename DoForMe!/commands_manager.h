#pragma once

#include <deque>

/**
	\class CommandsManager commands_manager.h "commands_manager.h"
	\brief Manager for commands stored in the lua's engine.
	\details This class allows to add commands with its arguments for further executing.
	By using addCommand() method we are able to put commands on some kind of queue (the queue is actually a std::deque).
	After putting command we can invoke executeNext() method. That method executes one command with its arguments from deque
	(it's assumed that the deque is used as a FIFO structure). After executing a command, the command is dropped from the deque with its arguments.
	\author Jacek Topolski
	\version 1.0
	\date 14.07.2012
*/
class CommandsManager {
private:
	/**
		\brief Queue with all commands.
		\details It contains pointers to functions with signature void function( std::deque<int> ) that will be executed in the future.
	*/
	std::deque<void (*)( std::deque<int> )> m_commands;
	/**
		\brief Queue with all arguments.
	*/
	std::deque<std::deque<int> > m_args;

public:
	/**
		\brief Allows to add commands to the queue.
		\param[in] pCmd Pointer to a function that is intended to be a command.
		\param[in] args Queue with arguments for a specified command.
	*/
	void addCommand( void ( *pCmd )( std::deque<int> ), std::deque<int> args );
	/**
		\brief Executes a next commands from the queue.
		\details After execution the command is removed from the queue.
	*/
	void executeNext();
	/**
		\brief Checks if there are any commands in the queue.
		\retval true There are some commands.
		\retval false There are no commands.
	*/
	bool isEmpty() const;
	/**
		\brief Removes all commands from the queue.
	*/
	void clearCommands();

};