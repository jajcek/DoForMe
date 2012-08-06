#include "calendar.h"

QListWidget* ActionsCalendar::m_list = NULL;

void ActionsCalendar::drawActionsNum( QPainter* painter, const QRect& rect, unsigned actionsNumber ) const {
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
	painter->drawText( rect.adjusted( 3, rect.height() - 15, -3, 0 ), Qt::AlignRight , _actionsNumber + " action(s)" );
}

void ActionsCalendar::setRepetition( QDate date, Action* action ) {
	if( !action->isXDays() && action->getDays() == 0 ) return;

	// how many days have current month
	// (+15 is for next month, because there are some days of next month visible (max ~15))
	int _daysNumber = date.daysInMonth() + 15;

	int _XDays = 0;
	// if the user set "every X days" option get its value
	if( action->isXDays() ) {
		 _XDays = action->getXDays();
	}

	// get selected days of week
	int _days = action->getDays();

	// go through all days from current date to the end of month
	// + 1 here is for prevention of double adding action to the current date
	// +10 is here for going for 10 next days, because we will make it earlier about 10 days
	// because at beginning of calendar there are visible some days of previous month
	int _iBalance = 10;
	for( int i = date.day(); i <= _daysNumber + _iBalance; ++i ) {
		// we will shift date about +1 day per iteration
		// it is necessary to add days if we have chosen further month on the calendar
		int _toNextMonths = date.daysTo( QDate( m_displayedYear, m_displayedMonth, 1 ) );

		// we need to correct it to not go before selected date
		_toNextMonths = _toNextMonths < 0 ? 0 : _toNextMonths;
		int _shift = i - date.day() + _toNextMonths - _iBalance;
		// and don't select current day (it is set in addAction() and setCurrentPage() in this class)
		if( _shift <= 0 ) continue;

		QDate _shiftedDate = date.addDays( _shift );
		
		if( _XDays != 0 ) {
			if( _shift % _XDays == 0 ) {
				m_actionsInMonth[_shiftedDate].push_back( action );
				continue;
			}
		}
		
		// set necessary days in calenday
		switch( _shiftedDate.dayOfWeek() ) {
			case 1: // monday
				if( _days & ActionSettings::MONDAY )
					m_actionsInMonth[_shiftedDate].push_back( action );
				break;
			case 2: // tuesday
				if( _days & ActionSettings::TUESDAY )
					m_actionsInMonth[_shiftedDate].push_back( action );
				break;
			case 3: // wednesday
				if( _days & ActionSettings::WEDNESDAY )
					m_actionsInMonth[_shiftedDate].push_back( action );
				break;
			case 4: // thursday
				if( _days & ActionSettings::THURSDAY )
					m_actionsInMonth[_shiftedDate].push_back( action );
				break;
			case 5: // friday
				if( _days & ActionSettings::FRIDAY )
					m_actionsInMonth[_shiftedDate].push_back( action );
				break;
			case 6: // saturday
				if( _days & ActionSettings::SATURDAY )
					m_actionsInMonth[_shiftedDate].push_back( action );
				break;
			case 7: // sunday
				if( _days & ActionSettings::SUNDAY )
					m_actionsInMonth[_shiftedDate].push_back( action );
		}
	}
}

ActionsCalendar::ActionsCalendar( QWidget* pParent ) : m_selectedDate( QDate::currentDate() ), m_displayedMonth( 0 ), m_displayedYear( 0 ) {
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

void ActionsCalendar::addAction( QDate date, Action* action ) {
	// add new action for a specified date and repaint cells
	// and container with actions for a selected month
	m_actionsInMonth[date].push_back( action );
	// add the action to the container with all actions
	m_actionsAll[date].push_back( action );

	// if an action has options 'every X days' or on 'Monday' etc.
	// we have to set it to the calendar too (to the current month only, because it would be infinite)
	setRepetition( date, action );

	updateCells();
}

void ActionsCalendar::setList( QListWidget* list ) {
	m_list = list;
}

QDate ActionsCalendar::getSelectedDate() const {
	return m_selectedDate;
}

void ActionsCalendar::paintCell( QPainter* painter, const QRect& rect, const QDate& date ) const {
	// set brushes for selecting
	if( date == m_selectedDate ) {
		painter->setPen( QPen( Qt::black, 2 ) );
		painter->setBrush( Qt::transparent );
	}

	// if action for the date exists
	if( m_actionsInMonth.contains( date ) ) {
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
	if( date == QDate::currentDate() || date == m_selectedDate || m_actionsInMonth.contains( date ) ) {
		painter->drawRect( rect );
	}

	// draw text that informs how many actions are there
	if( m_actionsInMonth.contains( date ) ) {
		int _actionsNumber = m_actionsInMonth[date].size();
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

void ActionsCalendar::selectDate( const QDate& date ) {
	// set new selected date
	m_selectedDate = date;

	// clear the list to prepare it for another day
	m_list->clear();

	// fill up the list with new actions
	if( m_actionsInMonth.find( date ) != m_actionsInMonth.end() ) {
		QVector<Action*> _actions = m_actionsInMonth.find( date ).value();

		// go through all actions
		int _actionsNumber = _actions.size();
		for( int i = 0; i < _actions.size();  ++i ) {
			Action* _action = _actions.at( i );

			// item on the list is displayed in "0:0:0 Name" form, so we get time here
			QString _strTime = QString::number( _action->getHours() ) + ":"
							 + QString::number( _action->getMinutes() ) + ":"
							 + QString::number( _action->getSeconds() );

			// add finally the item to the list
			m_list->addItem( _strTime + " " +_actions.at( i )->getScript()->getFileName() );
		}
	}
}

void ActionsCalendar::setCurrentPage( int year, int month ) {
	m_displayedMonth = month;
	m_displayedYear = year;

	// clear before setting actions again (to prevent summing actions)
	m_actionsInMonth.clear();

	// go throught all actions (days) and choose the actions with repetitions
	QMapIterator<QDate, QVector<Action*> > it( m_actionsAll );
	while( it.hasNext() ) {
		it.next();

		// go through all actions for day
		int _actionsNumber = it.value().size();
		for( int i = 0; i < _actionsNumber; ++i ) {
			Action* _pAction = it.value().at( i );
			if( _pAction->isXDays() || _pAction->getDays() != 0 ) {
				m_actionsInMonth[it.key()].push_back( _pAction );
				setRepetition( it.key(), _pAction );
			}
		}
	}
}