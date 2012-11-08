#include "screen_saver.h"

ScreenSaver* ScreenSaver::object = NULL;

ScreenSaver::ScreenSaver() : m_sx( -1 ), m_sy( -1 ) {
	setGeometry( 0, 0, QApplication::desktop()->width(), QApplication::desktop()->height() );
	setWindowFlags( Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
}

ScreenSaver* ScreenSaver::getInstance() {
	if( !object )
		object = new ScreenSaver();

	return object;
}

void ScreenSaver::setStartPoint( int x, int y ) {
	m_sx = x;
	m_sy = y;
	m_ex = x;
	m_ey = y;
	//qDebug( ( "Start: " + QString::number( x ) + ", " + QString::number( y ) ).toStdString().c_str() );
}

void ScreenSaver::setEndPoint( int x, int y ) {
	repaint();

	m_ex = x;
	m_ey = y;
	//qDebug( ( "End: " + QString::number( x ) + ", " + QString::number( y ) ).toStdString().c_str() );
}

void ScreenSaver::setCurrentDesktop() {
	desktop = QPixmap::grabWindow( QApplication::desktop()->winId() ).toImage();
}

QString ScreenSaver::saveSelectedFragment() {
	QDir _dir;
	int _dirExists = _dir.exists( CONF::PICS_DIR );

	if( !_dirExists )
		_dir.mkdir( CONF::PICS_DIR );

	QFile _file;
	int _number = 0;
	while( _file.exists( CONF::PICS_DIR + "pic" + QString::number( _number ) + ".bmp" ) )
		++_number;
	
	QString _fileName = CONF::PICS_DIR + "pic" + QString::number( _number ) + ".bmp";

	QImage fragment = desktop.copy( m_sx, m_sy, m_ex - m_sx + 1, m_ey - m_sy + 1 );
	fragment.save( _fileName );

	return _fileName;
}

void ScreenSaver::resetPoints() {
	m_sx = -1;
	m_sy = -1;
	m_ex = -1;
	m_ey = -1;
}

void ScreenSaver::paintEvent( QPaintEvent* p ) {
	QPainter painter( this );
	painter.drawImage( 0, 0, desktop );
	
	painter.setPen( Qt::red );
	if( !( m_sx == -1 && m_sy == -1 ) )
		painter.drawRect( m_sx, m_sy, m_ex - m_sx + 1, m_ey - m_sy + 1 );
}