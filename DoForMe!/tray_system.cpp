#include "tray_system.h"

void TraySystem::initContextMenu() {
	
}

void TraySystem::update( QVector<Action*> actions ) {
	QAction* _open   = new QAction( "Open", this );
	QAction* _info   = new QAction( "Info", this );
	QAction* _exit   = new QAction( "Exit", this );
	
	// clear all previous actions
	m_menu->clear();

	m_menu->addAction( _open );
	m_menu->addSeparator();
	int _actionsNumber = actions.size();
	if( _actionsNumber == 0 ) {
		m_menu->addAction( new QAction( "No actions left for this day.", this ) );
	} else {
		m_menu->addAction( new QAction( "Actions left for this day:", this ) );
	}
	for( int i = 0; i < _actionsNumber; ++i ) {
		Action* _pAction = actions.at( i );
		QString _scriptName = _pAction->getScript()->getFileName();
		QString _time = _pAction->getHoursHH() + ":" + _pAction->getMinutesMM() + ":" + _pAction->getSecondsSS();
		m_menu->addAction( new QAction( _time + " " + _scriptName, this ) );
	}
	m_menu->addSeparator();
	m_menu->addAction( _info );
	m_menu->addSeparator();
	m_menu->addAction( _exit );
}

TraySystem::TraySystem( QString iconPath, QObject* parent ) : m_menu( NULL ), m_actionsNumber( 3 ) {
	// set the icon for the tray icon
	QIcon icon = QIcon( iconPath );
	setIcon( icon );
	
	// set context menu
	m_menu = new QMenu( static_cast<QWidget*>( parent ) );
	QSystemTrayIcon::setContextMenu( m_menu );
	connect( m_menu, SIGNAL( triggered( QAction* ) ), this, SLOT( actionTrigger( QAction* ) ) );

	// set object which the tray system belongs to
	setParent( parent );
	show();

	// signal for clicking any mouse button on the tray icon
	connect( this, SIGNAL( activated( QSystemTrayIcon::ActivationReason ) ), this, SLOT( iconActivated( QSystemTrayIcon::ActivationReason ) ) );
}

void TraySystem::iconActivated( QSystemTrayIcon::ActivationReason reason ) {
	qDebug( "TraySystem::iconActivated()" );
}

void TraySystem::actionTrigger( QAction* action ) {
	qDebug( "%s", action->text().toStdString().c_str() );
}