#pragma once

#include <qobject.h>
#include <qmessagebox.h>
#include <qpushbutton.h>
#include <qbasictimer.h>
#include <qlabel.h>
#include <qlayout.h>
#include <memory>
#include "reminder_dialog.h"

/**
	\class MsgBoxWithDuration msg_box_with_duration.h "msg_box_with_duration.h"
	\brief Message box showed when an action is coming up.
	\details Note that the dialog hasn't been created with QT Designer, evey control on the dialog is created programatically.
	\author Jacek Topolski
	\version 1.0
	\date 2.09.2012
*/
class MsgBoxWithDuration : public QDialog {
	Q_OBJECT

private:
	/**
		\brief Duration of the window displaying.
	*/
	int m_iWinDuration;
	/**
		\brief Window title.
	*/
	QString m_strTitle;
	/**
		\brief Window text message.
	*/
	QString m_strMessage;
	/**
		\brief Value determining which button has been clicked (to process it outside the class).
	*/
	int m_buttonClicked;
	/**
		\brief Time used in connection with MsgBoxWithDuration::m_iWinDuration value.
	*/
	QBasicTimer m_timer;

	/**
		\brief Vertical layout for the dialog.
		\details First element of the layout is MsgBoxWithDuration::_imageTextLay and the second -
		MsgBoxWithDuration::_buttonsLay.
	*/
	QVBoxLayout _VLay;
	/**
		\brief Horizontal layout for the dialog which keeps image and text message.
	*/
	QHBoxLayout _imageTextLay;
	/**
		\brief Horizontal layout for the dialog which keeps all the buttons.
	*/
	QHBoxLayout _buttonsLay;
	/**
		\brief Label actually used for displaying... a bitmap.
	*/
	QLabel m_pixmap;
	/**
		\brief Label used to display MsgBoxWithDuration::m_strMessage.
	*/
	QLabel m_textLabel;
	/**
		\brief Run button.
	*/
	QPushButton m_runButton;
	/**
		\brief Suspend button.
	*/
	QPushButton m_suspendButton;
	/**
		\brief Ignore button.
	*/
	QPushButton m_ignoreButton;

public:
	/**
		\brief Values used to determine the buttons.
	*/
	enum BUTTON { RUN = 0, SUSPEND, IGNORING };

public:
	/**
		\brief Constructs dialog with window title, text message and duration.
		\param[in] strTitle Title of the window.
		\param[in] strMessage Text message for the window.
		\param[in] iWinDuration Duration of displaying the window in seconds.
	*/
	MsgBoxWithDuration( const QString strTitle, const QString strMessage, const int iWinDuration );
	/**
		\brief Stops the timer (to not close the dialog after tim duration).
	*/
	void stopTime();
	/**
		\brief Starts the timer.
		\details This can be used to re-start the timer, because the MsgBoxWithDuration::m_iWinDuration
		value is not reseted. See MsgBoxWithDuration::stopTime method for details.
	*/
	void startTime();
	/**
		\return Value which specifies which button has been clicked.
	*/
	int buttonClicked() const;

private slots:
	/**
		\brief Method called when run button is clicked.
	*/
	void run();
	/**
		\brief Method called when suspend button is clicked.
	*/
	void suspend();
	/**
		\brief Method called when ignore button is clicked.
	*/
	void ignore();

private:
	/**
		\brief Timer which takes care of duration of displaying the dialog.
	*/
	void timerEvent( QTimerEvent* e );
	/**
		\brief Updates text message by adding some kind of "Time elapsed: X".
	*/
	void updateTime();

};