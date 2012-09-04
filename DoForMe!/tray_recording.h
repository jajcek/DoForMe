#pragma once

#include <qsystemtrayicon.h>
#include <qbasictimer.h>

/**
	\class TrayRecording tray_recording.h "tray_recording.h"
	\brief Tray system used while recording (the blinking red dot as tray icon).
	\author Jacek Topolski
	\version 1.0
	\date 4.09.2012
*/
class TrayRecording : public QSystemTrayIcon {
private:
	/**
		\brief Simple timer used for showing and hiding the tray icon every second.
	*/
	QBasicTimer m_timer;
	/**
		\brief Flag which determines whether the tray icon is shown.
	*/
	bool m_isOn;
	/**
		\brief Path to the icon.
	*/
	QString m_iconPath;

public:
	/**
		\brief Sets icon for the tray system.
		\param[in] path Path to the image which represents icon.
	*/
	void setIcon( QString path );
	/**
		\brief Starts blinking the icon.
	*/
	void start();

private:
	/**
		\brief Method invoked by the TrayRecording::m_timer timer.
	*/
	void timerEvent( QTimerEvent* e );

};