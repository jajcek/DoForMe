#include "calendar.h"

QListWidget* DetailedCalendar::m_list;

void DetailedCalendar::drawActionsNum( QPainter* painter, const QRect& rect, unsigned actionsNumber ) const {
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
	// fit it to the main window by making the window its parent
	setParent( pParent );
	// hand cursor over the calendar
	setCursor( Qt::PointingHandCursor );

	setGridVisible( true );

	// the calendar start from sunday by default
	setFirstDayOfWeek( Qt::Monday );

	// make it english
	setLocale( QLocale( "English, United States" ) );

	setStyleSheet( "#qt_calendar_navigationbar { background-color: gray }" );

	// set current date
	m_selectedDate = QDate::currentDate();
	m_displayedMonth = m_selectedDate.month();

	QObject::connect( this, SIGNAL( clicked( const QDate& ) ), this, SLOT( selectDate( const QDate& ) ) );
	QObject::connect( this, SIGNAL( currentPageChanged( int, int ) ), this, SLOT( setCurrentPage( int, int ) ) );
}

void DetailedCalendar::addAction( QDate date, Action* action ) {
	// add new action for a specified date and repaint cells
	m_actions[date].push_back( action );
	updateCells();
}

void DetailedCalendar::setList( QListWidget* list ) {
	m_list = list;
}

QDate DetailedCalendar::getSelectedDate() const {
	return m_selectedDate;
}

void DetailedCalendar::paintCell( QPainter* painter, const QRect& rect, const QDate& date ) const {
	// set brushes for selecting
	if( date == m_selectedDate ) {
		painter->setPen( QPen( Qt::black, 2 ) );
		painter->setBrush( Qt::transparent );
	}

	// if action for the date exists
	if( m_actions.contains( date ) ) {
		// there would be black border (because of above)
		// but we want to draw the black border only if it is selected, otherwise draw gray border
		if( date != m_selectedDate ) painter->setPen( QPen( QColor( 220, 220, 220 ), 2 ) );
		painter->setBrush( QColor( 220, 220, 220 ) );
	}

	// set brusher for current day
	if( date == QDate::currentDate() ) {
		// we want to draw border only if it's selected, otherwise set the border color the same as background
		if( date != m_selectedDate ) painter->setPen( QPen( QColor( 51, 153, 255 ), 2 ) );
		painter->setBrush( QColor( 51, 153, 255 ) );
	}

	// draw border with previously set pens/brushes
	if( date == QDate::currentDate() || date == m_selectedDate || m_actions.contains( date ) ) {
		painter->drawRect( rect );
	}

	// draw text that informs how many actions are there
	if( m_actions.contains( date ) ) {
		int _actionsNumber = m_actions[date].size();
		drawActionsNum( painter, rect, _actionsNumber );
	}

	// we set text color for number of day in month
	if( date.month() != m_displayedMonth ) {
		painter->setPen( Qt::gray );
	} else if( date == QDate::currentDate() ) {
		// white text on blue background
		painter->setPen( Qt::white );
	} else if( date.dayOfWeek() == 6 || date.dayOfWeek() == 7 ) {
		// if it's saturday or sundar draw it in red
		painter->setPen( Qt::red );
	} else {
		painter->setPen( QColor( 50, 50, 50 ) );
	}

	// draw number of day in month
	QString _day = QString::number( date.day() );
	painter->drawText( rect.adjusted( 3, 3, 0, 0 ), _day );
}

// ------------------------ slots -----------------------------

void DetailedCalendar::selectDate( const QDate& date ) {
	// set new selected date
	m_selectedDate = date;

	// clear the list to prepare it for another day
	m_list->clear();

	// fill up the list with new actions
	if( m_actions.find( date ) != m_actions.end() ) {
		QVector<Action*> _actions = m_actions.find( date ).value();

		// go through all actions
		int _actionsNumber = _actions.size();
		for( int i = 0; i < _actions.size();  ++i ) {
			Action* _action = _actions.at( i );

			// item on the list is displayed in "0:0:0 Name" form, so we get time here
			QTime _time = _action->getTime();

			QString _strTime = QString::number( _time.hour() ) + ":" + QString::number( _time.minute() ) + ":" + QString::number( _time.second() );

			// add finally the item to the list
			m_list->addItem( _strTime + " " +_actions.at( i )->getFileName() );
		}
	}
}

void DetailedCalendar::setCurrentPage( int year, int month ) {
	m_displayedMonth = month;
}