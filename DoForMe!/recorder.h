#pragma once

#include <Windows.h>
#include <WindowsX.h>
#include <qdebug.h>
#include <qtextedit.h>
#include <qelapsedtimer.h>
#include "recorder_settings.h"
#include "lua_api.h"
#include "tray_recording.h"

/**
	\class Recorder recorder.h "recorder.h"
	\brief Engine for recording mouse and keyborad.
	\author Jacek Topolski
	\version 1.0
	\date 4.09.2012
*/
class Recorder {
private:
	/**
		\brief Hook handle for mouse.
	*/
	static HHOOK m_mouseHook;
	/**
		\brief Hook handle for keyboard.
	*/
	static HHOOK m_keyboardHook;
	/**
		\brief Pointer to the QTextEdit which the commands will be put into.
	*/
	static QTextEdit* m_textEdit;
	/**
		\brief Timer used for calculating argument for sleep api function.
	*/
	static QElapsedTimer* m_timer;
	/**
		\brief Map with keys actually pressed.
	*/
	static QMap<int, bool> m_keys;
	/**
		\brief Determines whether the Tab key is up or down.
	*/
	static bool m_isTabOn;
	/**
		\brief Determines whether the Esc key is up or down.
	*/
	static bool m_isF1On;
	/**
		\brief Tray object shown while recording is on.
	*/
	static TrayRecording m_tray;
	/**
		\brief Pointer to the action which can trigger show() method on main window.
	*/
	static QAction* m_showMainWindow;

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
	/**
		\brief Sets pointer to the action which can trigger main window show up.
		\param[in] pAction Pointer to the action.
	*/
	static void setMainWindowAction( QAction* pAction );

private:
	/**
		\brief Hooking procedure which parses all the messages from mouse.
	*/
	static LRESULT CALLBACK mouseHookProcedure( int code, WPARAM wParam, LPARAM lParam );
	/**
		\brief Hooking procedure which parses all the messages from keyboard.
	*/
	static LRESULT CALLBACK keyboardHookProcedure( int code, WPARAM wParam, LPARAM lParam );
	/**
		\brief Puts necessary commands into the previously set Recorder::m_textEdit by using Recorder::setTextEdit method.
		\param[in] cmd String containing the command. Note that sleep() function is always added before the cmd.
	*/
	static void putCmd( QString cmd );

};