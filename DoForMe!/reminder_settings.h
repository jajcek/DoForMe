#pragma once

#include <qfiledialog.h>
#include <phonon/mediaobject.h>
#include <phonon/mediasource.h>
#include "ui_reminder_dialog.h"

/**
	\class ReminderSettings reminder_settings.h "reminder_settings.h"
	\brief Settings for actions reminder.
	\details The dialog has been created with QT Designer.
	\author Jacek Topolski
	\version 1.0
	\date 2.09.2012
*/
class ReminderSettings : public QDialog {
	Q_OBJECT

private:
	/**
		\brief Object containing all controls of the window.
	*/
	Ui::ReminderSettings ui;
	/**
		\brief Pointer to the object of this class.
	*/
	static ReminderSettings* m_object;
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
	ReminderSettings();

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
	static ReminderSettings* getInstance();
	/**
		\return True if the notifications are enbaled, otherwise false.
	*/
	bool isReminderOn() const;
	/**
		\brief Sets reminder on/off.
		\param[in] state State of the reminder's check box.
	*/
	void setReminder( bool state );
	/**
		\return How many seconds before executing an action.
	*/
	int timeEarlier() const;
	/**
		\brief Sets value for time delay.
		\param[in] time Time delay in milliseconds.
	*/
	void setTimeEarlier( int delay );
	/**
		\return True if the sound is on, otherwise false.
	*/
	bool isSoundOn() const;
	/**
		\brief Sets check box for sound.
		\param[in] state State of the check box.
	*/
	void setSound( bool state );
	/**
		\return Path to the sound file.
	*/
	QString soundPath() const;
	/**
		\brief Sets path for the sound file.
		\param[in] path Path to the source file.
	*/
	void setSoundPath( QString path );

private:
	void closeEvent( QCloseEvent* e );

};