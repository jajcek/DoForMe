#pragma once

#include "ui_recorder_settings_dialog.h"

class RecorderSettings : public QDialog {
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
		\return True is the keyboard check box is checked, otherwise false.
	*/
	bool isKeyboardOn() const;

};