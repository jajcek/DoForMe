#pragma once

#include <Windows.h>
#include <WindowsX.h>
#include <qdebug.h>
#include <qtextedit.h>
#include <qelapsedtimer.h>
#include "recorder_settings.h"

class Recorder {
private:
	/**
		\brief Hook handle for mouse.
	*/
	static HHOOK m_mouseHook;
	/**
		\brief Pointer to the QTextEdit which the commands will be put into.
	*/
	static QTextEdit* m_textEdit;
	/**
		\brief Timer used for calculating argument for sleep api function.
	*/
	static QElapsedTimer* m_timer;

public:
	/**
		\brief Starts recording by setting hooks on input devices.
	*/
	static void startRecording();
	/**
		\brief Stops recording by releasing hook.
	*/
	static void stopRecording();
	/**
		\brief Sets text area which the commands will be put into.
		\param[in] textEdit Pointer to the QTextEdit object.
	*/
	static void setTextEdit( QTextEdit* textEdit );

private:
	/**
		\brief Hooking procedure which parses all the messages from mouse.
	*/
	static LRESULT CALLBACK mouseHook( int code, WPARAM wParam, LPARAM lParam );
	/**
		\brief Puts necessary commands into the previously set Recorder::m_textEdit by using Recorder::setTextEdit method.
		\param[in] cmd String containing the command. Note that sleep() function is always added before the cmd.
	*/
	static void putCmd( QString cmd );

};