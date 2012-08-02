#pragma once

#include <qfileinfo.h>
#include <qstring.h>
#include <qfile.h>
#include <qmessagebox.h>
#include "conf.h"

class Script {
private:
	QString m_strCode;
	QString m_strPath;
	bool m_bModified;

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

	void setModified( bool isModified );
	bool isModified() const;

};