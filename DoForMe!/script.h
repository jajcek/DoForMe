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

private:
	QString getTitleFromFile(  QFile& file );
	QString getDescriptionFromFile( QFile& file );
	QString getCodeFromFile( QFile& file );

public:
	Script( const QString& path );

	QString getTitle() const;
	QString getDescription() const;
	QString getCode() const;
	QString getPath() const;

};