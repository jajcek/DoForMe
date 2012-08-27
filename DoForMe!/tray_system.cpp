#include "tray_system.h"

void TraySystem::update( QVector<Action*> actions ) {
	// clear all previous actions
	m_menu->clear();

	m_menu->addAction( m_qtActions.find( "Open" ).value() );
	m_menu->addSeparator();

	// add actions for the current day (except for the old one)
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
	m_menu->addAction(  m_qtActions.find( "Exit" ).value()  );
}

void TraySystem::addQAction( QAction* action ) {
	m_qtActions[action->text()] = action;
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

	// signal for clicking any mouse button on the tray icon
	connect( this, SIGNAL( activated( QSystemTrayIcon::ActivationReason ) ), this, SLOT( iconActivated( QSystemTrayIcon::ActivationReason ) ) );
}

void TraySystem::iconActivated( QSystemTrayIcon::ActivationReason reason ) {
	qDebug( "TraySystem::iconActivated()" );
}

void TraySystem::actionTrigger( QAction* action ) {
	qDebug( "%s", action->text().toStdString().c_str() );
}

void TraySystem::open() {
	
}

void TraySystem::info() {

}

void TraySystem::exit() {

}