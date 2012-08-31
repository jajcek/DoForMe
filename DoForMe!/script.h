#pragma once

#include <qfileinfo.h>
#include <qstring.h>
#include <qfile.h>
#include <qmessagebox.h>
#include <qdir.h>
#include "conf.h"

/**
	\class Script script.h "script.h"
	\brief Keeps all data for scripts.
	\details The data in the class are: code, path to the script file and state that indicates if the script has been modified.
	\author Jacek Topolski
	\version 1.0
	\date 28.07.2012
*/
class Script {
private:
	/**
		\brief Code of the script.
	*/
	QString m_strCode;
	/**
		\brief Path to the file by which has been created an object.
	*/
	QString m_strPath;
	/**
		\brief State of the script which indicates if the script is modified or not.
	*/
	bool m_bModified;

public:
	/**
		\brief Constant which is used for file open exception.
		\details A file can throw (actually the constructor) an exception when e.g. file is not found or somehow is not able to open/write.
	*/
	static const int FileOpenException;
	/**
		\brief Constant which instructs constructor to load file from the given path.
	*/
	static const int LOAD;
	/**
		\brief Constant which instructs constructor to create file with the given path.
	*/
	static const int CREATE;

private:
	/**
		\brief Helper function that loads content of the file.
		\details Beware that the file object will be fully read with readLine method of QFile class,
		so after executing the function on the object, your cursor will point to the end of the file.
		\param[in] file File which the function reads from.
		\return Content of the file.
	*/
	QString getCodeFromFile( QFile& file );

public:
	/**
		\brief Contructor which creates or loads a file from the given path.
		\details If the file can't be somehow opened to read or write, or the file doesn't exists the Script::FileOpenException exception is thrown.
		\param[in] path Path to a file.
		\param[in] iMode Parameter which determines what the constructor should do, create or load file.
		See Script::LOAD and Script::CREATE for more details. By default the value is set to Script::LOAD.
	*/
	Script( const QString& path, int iMode = LOAD ) throw( int );

	/**
		\brief Sets the code for the script.
		\param[in] code Code to be set for the script.
	*/
	void setCode( const QString& code );
	/**
		\brief Gets the code for the script.
		\return Code of the script.
	*/
	QString getCode() const;

	/**
		\brief Get path to the file by which the object has been created.
		\return Path of the file.
	*/
	QString getPath() const;

	/**
		\brief Gets file name (without extension) of the script file.
		\details File name is taken from its path Script::m_strPath.
		\return File name (without extension).
	*/
	QString getFileName() const;

	/**
		\brief Changes state of the script (modified/unmodified).
		\param[in] isModified State of the script.
	*/
	void setModified( bool isModified );
	/**
		\return State of the script (modified or not).
	*/
	bool isModified() const;

};