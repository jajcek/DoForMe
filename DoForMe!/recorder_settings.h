#pragma once

#include "ui_recorder_settings_dialog.h"

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
		\return True is the mouse check box is checked, otherwise false.
	*/
	bool isMouseOn() const;
	/**
		\return True is mouse move check box is checked, otherwise false.
	*/
	bool isMouseMoveOn() const;
	/**
		\return True is the keyboard check box is checked, otherwise false.
	*/
	bool isKeyboardOn() const;

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