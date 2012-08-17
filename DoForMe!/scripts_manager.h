#pragma once

#include <qmap.h>
#include <qinputdialog.h>
#include <qdir.h>
#include "script.h"

/**
	\class ScriptsManager scripts_manager.h "scripts_manager.h"
	\brief Manager for scripts.
	\details The class stores all scripts and allows to save them to file. It cannot be instantiated. It contains only static methods for managing scripts in the application.
	\author Jacek Topolski
	\version 1.0
	\date 2.08.2012
*/
class ScriptsManager {
private:
	/**
		\brief Map which stores all scripts, name mapped to it's object. See Script class for more details.
	*/
	static QMap<QString, Script*> m_scripts;
	/**
		\brief Private constructor which doesn't allow the class to be instantiated.
	*/
	ScriptsManager();

public:
	/**
		\brief Removes all script and frees its memory.
	*/
	static void removeScripts();

	/**
		\brief Adds new script to the manager.
		\param[in] script Script to add.
		\retval true The script has been added successfully.
		\retval false The script couldn't be added due to existence of another script with the same name.
	*/
	static bool addScript( Script* script );
	/**
		\brief Saves specified (with name) script to a file.
		\details The script will be saved to the Script::m_strPath path.
		\param[in] scriptName Name of the script which can be obtained by Script::getFileName method.
		\retval true The script has been saved to its file successfully.
		\retval false The script couldn't be saved due to missing name in the ScriptsManager. The script wasn't probably added to the manager.
	*/
	static bool saveToFile( const QString& scriptName );
	/**
		\brief Gets pointer to the script with the given name.
		\param[in] scriptName Name of the script which can be obtained by Script::getFileName method.
		\return Pointer to the Script object.
	*/
	static Script* getScript( const QString& scriptName );
	/**
		\return List of scripts names.
	*/
	static QStringList getScriptsList();

};