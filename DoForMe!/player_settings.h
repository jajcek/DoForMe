#pragma once

#include <qdialog.h>
#include "ui_player_settings_dialog.h"

/**
	\class RecorderSettings recorder_settings.h "recorder_settings.h"
	\brief Dialog with recorder settings.
	\details The dialog has been created with QT Designer.
	\author Jacek Topolski
	\version 1.0
	\date 4.09.2012
*/
class PlayerSettings : public QDialog {
	Q_OBJECT

private:
	/**
		\brief Object containing all controls of the dialog.
	*/
	Ui::player_settings_dialog ui;
	/**
		\brief Value determining the starting delay when clicked on Play button.
	*/
	int m_iDelay;
	/**
		\brief Pointer to the object of this class.
	*/
	static PlayerSettings* m_object;

	/**
		\brief Simple constructor which simply sets fields to its default values.
		\details The constructor has been put into the private section to prevent creating instances from the class
		(because the class is a singleton).
	*/
	PlayerSettings();

public:
	/**
		\return Pointer to the instance of the class.
	*/
	static PlayerSettings* getInstance();
	/**
		\return Delay value.
	*/
	int delay() const;

private slots:
	/**
		\brief Method called when Ok button is clicked.
	*/
	void pressedOk();
	/**
		\brief Method called when Cancel button is clicked.
	*/
	void pressedCancel();

};