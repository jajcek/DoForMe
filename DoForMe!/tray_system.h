#pragma once

#include <qsystemtrayicon.h>
#include <qaction.h>
#include <qmenu.h>
#include "calendar.h"

/**
	\class TraySystem tray_system.h "tray_system.h"
	\brief Controls behaviour of the tray icon system.
	\author Jacek Topolski
	\version 1.0
	\date 28.08.2012
*/
class TraySystem : public QSystemTrayIcon {
	Q_OBJECT

private:
	/**
		\brief Pointer to context menu which is shown when user click right mouse button on the icon.
	*/
	QMenu* m_menu;
	/**
		\brief Stores value which specifies the number of actions in the context menu.
	*/
	unsigned m_actionsNumber;
	/**
		\brief Map of all operation in the context menu.
		\details It maps operation (string from the context menu) into a QAction object.
	*/
	QMap<QString, QAction*> m_qtActions;

public:
	/**
		\brief Construct object with an icon from the given path.
		\param[in] iconPath Path to the icon we want to load.
		\param[in] parent Pointer to the parent to which the tray system will be connected.
	*/
	TraySystem( QString iconPath, QObject* parent );
	/**
		\brief Updates content of the context menu.
		\param[in] actions Vector of actions that will be added to the context menu.
	*/
	void update( QVector<Action*> actions );
	/**
		\brief Adds operation for the context menu (not the actions from the calendar), e.g. Open or Exit.
		\details Beware that it is necessary to modify the method, because it doesn't use any loop to obtain all operations.
		It was needed to put actions from calendar between some operations that's why the programmer sets the order.
		\param[in] action Action that will be added to the context menu.
	*/
	void addQAction( QAction* action );

private slots:
	/**
		\brief Method which is invoked when signal is emmited from clicking on tray icon.
		\param[in] reason Specifies that action has been performed on the tray icon (click, double click, middle click etc.)
	*/
	void iconActivated( QSystemTrayIcon::ActivationReason reason );

};