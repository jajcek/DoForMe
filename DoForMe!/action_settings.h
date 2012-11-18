#pragma once

#include <qdialog.h>
#include <qdesktopwidget.h>
#include <qicon.h>
#include <qdatetime.h>
#include <qmessagebox.h>
#include <qtablewidget.h>
#include "ui_action_dialog.h"
#include "lua_engine.h"
#include "scripts_manager.h"

/**
	\class ActionSettings action_settings.h "action_settings.h"
	\brief Shows action settings dialog and stores information selected on controls.
	\details Dialog is shown to choose properties for action that will be added.
	The dialog can be show by methods derived from QDialog like QDialog::exec().
	\author Jacek Topolski
	\version 1.0
	\date 28.08.2012
*/
class ActionSettings : public QDialog {
	Q_OBJECT

private:
	/**
		\brief Structure which contains pointers to all controls on the dialog.
	*/
	Ui::actionSettingsDialog ui;
	/**
		\brief Date which the action will be added to.
		\details The date is set when creating an object by passing it to the constructor's argument.
	*/
	QDate m_selectedDate;
	/**
		\brief Values that specify is the date is old or not.
	*/
	enum STATUS { OLD = 0, OK };

public:
	/**
		\brief Value for monday.
		\details The values must be remembered in memory to perform bit operations.
		For example if we want to set a monday and a tuesday we should use MONDAY | TUESDAY to get value that indicates these two days.
	*/
	static const char MONDAY;
	/**
		\brief Value for tuesday. See ActionSettings::MONDAY for details.
	*/
	static const char TUESDAY;
	/**
		\brief Value for wednesday. See ActionSettings::MONDAY for details.
	*/
	static const char WEDNESDAY;
	/**
		\brief Value for thursday. See ActionSettings::MONDAY for details.
	*/
	static const char THURSDAY;
	/**
		\brief Value for friday. See ActionSettings::MONDAY for details.
	*/
	static const char FRIDAY;
	/**
		\brief Value for saturday. See ActionSettings::MONDAY for details.
	*/
	static const char SATURDAY;
	/**
		\brief Value for sunday. See ActionSettings::MONDAY for details.
	*/
	static const char SUNDAY;

private:
	/**
		\brief Check the time whether it's an old date.
		\details To do this the function uses ActionSettings::m_selectedDate field.
		\return One of the value defined in the enumeration ActionSettings::STATUS. See ActionSettings::STATUS for details.
	*/
	int checkTimeCorrectness();

public:
	/**
		\brief Creates the dialog with current date.
		\details Use another version of constructor (ActionSettings::ActionSettings( QDate date )) if you wish to set the date by yourself.
		See ActionSettings:m_selectedDate for details.
	*/
	ActionSettings();
	/**
		\brief Creates the dialog with the given date.
	*/
	ActionSettings( QDate date );

	/**
		\brief Sets list of all scripts which are listed in the combo box of the dialog.
		\param[in] scripts List of the scripts (scripts names).
	*/
	void setScripts( const QStringList& scripts );
	/**
		\return Name of the currently selected (in combo box) script.
	*/
	QString getScriptName() const;
	/**
		\brief Selects script on the combo box.
		\param[in] scriptName Name of the script which can be obtained by Script::getFileName method.
	*/
	void selectScript( const QString& scriptName );

	/**
		\brief Sets hours to the spin box.
		\param[in] hours Hours to be set.
	*/
	void setHours( int hours );
	/**
		\return Hours from the spin box.
	*/
	int getHours() const;
	/**
		\brief Sets minutes to the spin box.
		\param[in] minutes Minutes to be set.
	*/
	void setMinutes( int minutes );
	/**
		\return Minutes from the spin box.
	*/
	int getMinutes() const;
	/**
		\brief Sets seconds to the spin box.
		\param[in] seconds Seconds to be set.
	*/
	void setSeconds( int seconds );
	/**
		\return Seconds from the spin box.
	*/
	int getSeconds() const;

	/**
		\brief Sets the check box which specified if the user wants to use repetitions every X days.
		\param[in] isXDays State of the check box.
	*/
	void setIsXDays( bool isXDays );
	/**
		\return State of the check box.
	*/
	bool isXDays() const;
	/**
		\brief Sets the number of days which determine a repetition every X days.
		\param[in] days Number of days.
	*/
	void setXDays( int days );
	/**
		\return Number of days which determines the "every X days" option.
	*/
	int getXDays() const;
	/**
		\brief Sets the number of days which determine a repetition every X days.
		\param[in] mask Number of days.
	*/
	void setDaysFlags( char mask );
	/**
		\details Mask is created by using fields of this class: ActionSettings::MONDAY etc. See ActionSettings::MONDAY for details.
		\return Mask which specifies days of the week that has been chosen by the user.
	*/
	int getDays() const;

public slots:
	/**
		\brief Action which is performed during clicking on Apply button.
		\details The method invalidates all values in controls.
	*/
	void apply();

};