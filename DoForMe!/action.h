#pragma once

#include <qstring.h>
#include <QTime>

/**
	\class Action action.h "action.h"
	\brief Engine for maintaing LUA's API commands.
	\details Objects of this class load scripts, check their grammar correctness and store the commands for further executing.
	\author Jacek Topolski
	\version 1.0
	\date 6.07.2012
*/
class Action {
private:
	QString m_path;
	QString m_fileName;
	QString m_code; // for remove, we won't handle code here

	QTime m_time;
	bool m_bModified;

public:
	Action();
	~Action();

	void setPath( QString path );
	QString getPath() const;

	void setFileName( QString fileName );
	QString getFileName() const;

	void setCode( QString code );
	QString getCode() const;

	void setTime( QTime );
	QTime getTime() const;

	void setModified( bool );
	bool isModified() const;
};