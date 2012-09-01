#pragma once

#include <qobject.h>
#include <qmessagebox.h>
#include <qpushbutton.h>
#include <qbasictimer.h>
#include <qlabel.h>
#include <qlayout.h>
#include <memory>

class MsgBoxWithDuration : public QDialog {
	Q_OBJECT

private:
	int m_iWinDuration;
	QString m_strTitle;
	QString m_strMessage;
	int m_buttonClicked;
	QBasicTimer m_timer;

	QVBoxLayout _VLay;
	QHBoxLayout _imageTextLay;
	QHBoxLayout _buttonsLay;
	QLabel m_pixmap;
	QLabel m_textLabel;
	QPushButton m_runButton;
	QPushButton m_suspendButton;
	QPushButton m_ignoreButton;

public:
	enum BUTTON { RUN = 0, SUSPEND, IGNORING };

public:
	MsgBoxWithDuration( const QString strTitle, const QString strMessage, const int iWinDuration );
	void stopTime();
	void startTime();
	int buttonClicked() const;

private slots:
	void run();
	void suspend();
	void ignore();

private:
	void timerEvent( QTimerEvent* e );
	void updateTime();

};