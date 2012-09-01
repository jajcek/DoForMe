#pragma once

#include "ui_reminder_dialog.h"

/**
	\class ReminderDialog reminder_dialog.h "reminder_dialog.h"
	\brief "About" dialog.
	\details Layout for the dialog has been made in Qt Designer.
	The only thing that is generated in this code is a gradient background for a logo.
	\author Jacek Topolski
	\version 1.0
	\date 6.07.2012
*/
class ReminderDialog : public QDialog {
	Q_OBJECT

private:
	Ui::reminderDialog ui;
	static ReminderDialog* m_object;

	bool m_bIsOn;
	float m_fTimeEarlier;
	bool m_bIsMsgOn;
	int m_iMsgDuration;
	bool m_bIsSoundOn;
	QString m_strSoundPath;

	ReminderDialog();

private slots:
	void pressedOk();

public:
	static ReminderDialog* getInstance();
	
	bool isOn() const;
	float timeEarlier() const;
	bool isMsgOn() const;
	int msgDuration() const;
	bool isSoundOn() const;
	QString soundPath() const;

};