#pragma once

#include <qmap.h>
#include <qinputdialog.h>
#include <qdir.h>
#include "script.h"

class ScriptsManager {
private:
	static QMap<QString, Script*> m_scripts;

	ScriptsManager();

public:
	static void removeScripts();

	static bool addScript( Script* script );
	static void saveToFile( const QString& title );
	static Script* getScript( const QString scriptTitle );

};