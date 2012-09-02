#pragma once

#include <qfiledialog.h>
#include <phonon/mediaobject.h>
#include <phonon/mediasource.h>
#include "ui_reminder_dialog.h"

/**
	\class ReminderDialog reminder_dialog.h "reminder_dialog.h"
	\brief Settings for actions reminder.
	\details The dialog has been created with QT Designer.
	\author Jacek Topolski
	\version 1.0
	\date 2.09.2012
*/
class ReminderDialog : public QDialog {
	Q_OBJECT

private:
	/**
		\brief Object containing all controls of the window.
	*/
	Ui::reminderDialog ui;
	/**
		\brief Pointer to the object of this class.
	*/
	static ReminderDialog* m_object;
	/**
		\brief Value specifying whether the signaling actions is on.
	*/
	bool m_bIsOn;
	/**
		\brief How many seconds need to elapse to execute the notification.
	*/
	int m_fTimeEarlier;
	/**
		\brief Value specifying whether the sound is on.
	*/
	bool m_bIsSoundOn;
	/**
		\brief Path to the sound file.
	*/
	QString m_strSoundPath;
	/**
		\brief Object which allows to play sounds.
	*/
	Phonon::MediaObject* m_sound;

	/**
		\brief Simple constructor which simply sets fields to its default values.
		\details The constructor has been put into the private section to prevent creating instances from the class
		(because the class is a singleton).
	*/
	ReminderDialog();

private slots:
	/**
		\brief Method called when clicking Browse button.
	*/
	void browseSound();
	/**
		\brief Method called when clicking Ok button.
	*/
	void pressedOk();
	/**
		\brief Method called when clicking Ok button.
	*/
	void pressedCancel();
	/**
		\brief Method called when signal check box is turned off.
	*/
	void signalUnchecked();
	/**
		\brief Method called when sound check box is turned on.
	*/
	void soundChecked();

public slots:
	/**
		\brief Method called when clicking Play button.
	*/
	void playSound();
	/**
		\brief Stops sound.
	*/
	void stopSound();

public:
	/**
		\return Pointer to the instance of the class.
	*/
	static ReminderDialog* getInstance();
	/**
		\return True if the notifications are enbaled, otherwise false.
	*/
	bool isOn() const;
	/**
		\return How many seconds before executing an action.
	*/
	int timeEarlier() const;
	/**
		\return True if the sound is on, otherwise false.
	*/
	bool isSoundOn() const;
	/**
		\return Path to the sound file.
	*/
	QString soundPath() const;

};