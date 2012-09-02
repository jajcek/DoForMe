#pragma once

#include <Windows.h>
#include <WindowsX.h>
#include <qdebug.h>
#include <qtextedit.h>
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

public:
	/**
		\brief Starts recording by setting hooks on input devices.
	*/
	static void startRecording();
	/**
		\brief Sets text area which the commands will be put into.
		\param[in] textEdit Pointer to the QTextEdit object.
	*/
	static void setTextEdit( QTextEdit* textEdit );

private:
	static LRESULT CALLBACK mouseHook( int code, WPARAM wParam, LPARAM lParam );
	static void putCmd( QString cmd );

};