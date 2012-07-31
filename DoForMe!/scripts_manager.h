#pragma once

#include <qmap.h>
#include <qinputdialog.h>
#include <qdir.h>
#include "script.h"

class ScriptsManager {
private:
	static QMap<QString, Script*> m_scripts;

	ScriptsManager();

private:
	static bool attemptToAddScript( Script* script );

public:
	static void removeScripts();

	static bool addScript( Script* script, bool showInput = false );
	static void saveToFile( const QString& title );

};