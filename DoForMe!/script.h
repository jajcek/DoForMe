#pragma once

#include <qfileinfo.h>
#include <qstring.h>
#include <qfile.h>
#include <qmessagebox.h>

class Script {
private:
	QString m_strTitle;
	QString m_strDescription;
	QString m_strCode;
	QString m_strPath;

public:
	static int FileOpenException;
	static int LOAD;
	static int CREATE;

private:
	QString getCodeFromFile( QFile& file );

public:
	Script( const QString& path, int iMode ) throw( int );

	void setCode( QString code );
	QString getCode() const;

	QString getPath() const;

	QString getFileName() const;

};