#pragma once

#include "ui_recorder_settings_dialog.h"

/**
	\class RecorderSettings recorder_settings.h "recorder_settings.h"
	\brief Dialog with recorder settings.
	\details The dialog has been created with QT Designer.
	\author Jacek Topolski
	\version 1.0
	\date 4.09.2012
*/
class RecorderSettings : public QDialog {
	Q_OBJECT

private:
	/**
		\brief Object containing all controls of the dialog.
	*/
	Ui::recorder_settings_dialog ui;
	/**
		\brief Pointer to the object of this class.
	*/
	static RecorderSettings* m_object;
	/**
		\brief Determines whether the mouse recording is turned on.
	*/
	bool m_isMouseOn;
	/**
		\brief Determines whether the mouse move recording is turned on.
	*/
	bool m_isMouseMoveOn;
	/**
		\brief Determines whether the keyboard recording is turned on.
	*/
	bool m_isKeyboardOn;
	/**
		\brief Determines whether the app should hide into tray after starting recording.
	*/
	bool m_isTrayOn;

	/**
		\brief Simple constructor which simply sets fields to its default values.
		\details The constructor has been put into the private section to prevent creating instances from the class
		(because the class is a singleton).
	*/
	RecorderSettings();

public:
	/**
		\return Pointer to the instance of the class.
	*/
	static RecorderSettings* getInstance();
	/**
		\return True if the mouse check box is checked, otherwise false.
	*/
	bool isMouseOn() const;
	/**
		\brief Sets value for the mouse check box.
		\param[in] state State of the check box.
	*/
	void setMouse( bool state );
	/**
		\return True if mouse move check box is checked, otherwise false.
	*/
	bool isMouseMoveOn() const;
	/**
		\brief Sets value for the mouse move check box.
		\param[in] state State of the check box.
	*/
	void setMouseMove( bool state );
	/**
		\return True if the keyboard check box is checked, otherwise false.
	*/
	bool isKeyboardOn() const;
	/**
		\brief Sets value for the keyboard move check box.
		\param[in] state State of the check box.
	*/
	void setKeyboard( bool state );
	/**
		\return True if the tray check box is checked, otherwise false.
	*/
	bool isTrayOn() const;
	/**
		\brief Sets value for the tray move check box.
		\param[in] state State of the check box.
	*/
	void setTray( bool state );

private slots:
	/**
		\brief Method called when ok button is clicked.
	*/
	void pressedOk();
	/**
		\brief Method called when cancel button is clicked.
	*/
	void pressedCancel();

};