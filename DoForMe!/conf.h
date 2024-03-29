#pragma once

#include <qstring.h>

/**
	\class CONF conf.h "conf.h"
	\brief Configuration data.
	\details Structure containing all configuration data like application name,
	directory name where the application saves the scripts, extenstion for the script files and so on.
	\author Jacek Topolski
	\version 1.0
	\date 2.08.2012
*/
struct CONF {
	/**
		\brief Application name.
	*/
	static QString APP_NAME;
	/**
		\brief Directory name for the scripts files.
	*/
	static QString SCRIPT_DIR;
	/**
		\brief Extension for the script files.
	*/
	static QString EXT;
	/**
		\brief Folder which the fragments of the pictures are kept.
	*/
	static QString PICS_DIR;
};