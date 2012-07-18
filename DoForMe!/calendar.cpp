#include "calendar.h"

void DetailedCalendar::drawActions( QPainter* painter, const QRect& rect, unsigned actionsNumber ) const {
	painter->setPen( Qt::black );

	/*unsigned _size = 6;
	float _fromTop = 2;
	float _fromLeft = 2.5;
	QPoint trianglePoints[3];
	trianglePoints[0].setX( rect.left() + ( rect.width() - _size - 1 ) - _size );
	trianglePoints[0].setY( rect.top() + ( rect.height() - _size - 1 ) - _size );
	trianglePoints[1].setX( rect.left() + ( rect.width() - _size - 1 ) - _size );
	trianglePoints[1].setY( rect.top() + ( rect.height() - _size - 1 ) + _size );
	trianglePoints[2].setX( rect.left() + ( rect.width() - _size - 1 ) );
	trianglePoints[2].setY( rect.top() + ( rect.height() - _size - 1 ) );

	painter->drawPolygon( trianglePoints, 3 );*/

	QString _actionsNumber;
	_actionsNumber.setNum( actionsNumber );
	painter->drawText( rect.adjusted( 3, rect.height() - 15, -3, 0 ), Qt::AlignRight , _actionsNumber + " actions" );
}

DetailedCalendar::DetailedCalendar( QWidget* pParent ) {
	setParent( pParent );
	setCursor( Qt::PointingHandCursor );

	m_selectedDate = QDate::currentDate();
	m_displayedMonth = m_selectedDate.month();

	QObject::connect( this, SIGNAL( clicked( const QDate& ) ), this, SLOT( select( const QDate& ) ) );
	QObject::connect( this, SIGNAL( currentPageChanged( int, int ) ), this, SLOT( setCurrentPage( int, int ) ) );

	QVector<QString> vec;
	QDate a = QDate::currentDate();
	a = a.addDays( -10 );
	m_actions.insert( a, vec );
}

void DetailedCalendar::paintCell( QPainter* painter, const QRect& rect, const QDate& date ) const {
	if( date == m_selectedDate ) {
		painter->setPen( QPen( Qt::black, 2 ) );
		painter->setBrush( Qt::transparent );
	}

	if( m_actions.contains( date ) ) {
		if( date != m_selectedDate ) painter->setPen( QPen( QColor( 220, 220, 220 ), 2 ) );
		painter->setBrush( QColor( 220, 220, 220 ) );
	}

	if( date == QDate::currentDate() ) {
		if( date != m_selectedDate ) painter->setPen( QPen( QColor( 51, 153, 255 ), 2 ) );
		painter->setBrush( QColor( 51, 153, 255 ) );
	}

	if( date == QDate::currentDate() || date == m_selectedDate || m_actions.contains( date ) ) {
		painter->drawRect( rect );
	}

	if( m_actions.contains( date ) ) {
		drawActions( painter, rect, 2 );
	}

	if( date.month() != m_displayedMonth ) {
		painter->setPen( Qt::gray );
	} else if( date == QDate::currentDate() ) {
		painter->setPen( Qt::white );
	} else if( date.dayOfWeek() == 6 || date.dayOfWeek() == 7 ) {
		painter->setPen( Qt::red );
	} else {
		painter->setPen( QColor( 50, 50, 50 ) );
	}

	QString day;
	day.setNum( date.day() );
	painter->drawText( rect.adjusted( 3, 3, 0, 0 ), day );
}

void DetailedCalendar::select( const QDate& date ) {
	m_selectedDate = date;
}

void DetailedCalendar::setCurrentPage( int year, int month ) {
	m_displayedMonth = month;
}