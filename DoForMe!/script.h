#pragma once

#include <qmap.h>
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
	static int InvalidFileException;

private:
	QString getTitleFromFile(  QFile& file );
	QString getDescriptionFromFile( QFile& file );
	QString getCodeFromFile( QFile& file );

public:
	Script( const QString& path ) throw( int );
	Script( const QString& title, const QString& path, const QString& description = "", const QString& code = "" );

	void execute();

	void setTitle( QString title );
	QString getTitle() const;

	void setDescription( QString description );
	QString getDescription() const;

	void setCode( QString code );
	QString getCode() const;

	void setPath( QString path );
	QString getPath() const;

};