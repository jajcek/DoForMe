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

	// get number of actions
	QString _actionsNumber;
	_actionsNumber.setNum( actionsNumber );

	// set font size (ang get current font size to get back to it later)
	QFont _font = painter->font();
	int _oldSize = _font.pointSize();
	_font.setPointSize( 7 );
	painter->setFont( _font );

	// draw text which specifies number of actions
	painter->drawText( rect.adjusted( 3, rect.height() - 12, -2, 0 ), Qt::AlignRight , _actionsNumber + " action(s)" );

	// return back to the old font size
	_font.setPointSize( _oldSize );
	painter->setFont( _font );
}

void ActionsCalendar::setRepetition( QDate date, Action* action ) {
	if( !action->isXDays() && action->getDays() == 0 ) return;

	// how many days has the current month
	int _daysNumber = date.daysInMonth();

	int _XDays = 0;
	// if the user set "every X days" option get its value
	if( action->isXDays() ) {
		 _XDays = action->getXDays();
	}

	// get selected days of week
	int _days = action->getDays();

	// go through all days from current date to the end of month
	// (balance is for previous and next month, because there are some days still visible (max ~15))
	// because at beginning of calendar there are visible some days of previous month
	// we need to multiply balance in a loop because we subtract it later, so we need to... balance the balance
	int _iBalance = 31;
	for( int i = date.day(); i <= _daysNumber + 2  *_iBalance; ++i ) {
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

bool ActionsCalendar::checkTimeCorrectness( QDate date, Action* action ) {
	QDate _currentDate = QDate::currentDate();
	QTime _currentTime = QTime::currentTime();

	if( date == _currentDate ) {
		if( action->getTime() <= _currentTime ) {
			return false;
		}
	}

	return true;
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
	// inform user that the time passed already
	if( !checkTimeCorrectness( date, action ) ) {
		QMessageBox _msg( QMessageBox::Information, "Information", "The time passed already. Do you still want to add the action?",
			QMessageBox::Yes | QMessageBox::No );
		if( _msg.exec() == QMessageBox::No )
			return;
	}

	// add new action for a specified date and repaint cells
	// and container with actions for a selected month
	m_actionsInMonth[date].push_back( action );
	// add the action to the container with all actions
	m_actionsAll[date].push_back( action );

	// if an action has options 'every X days' or on 'Monday' etc.
	// we have to set it to the calendar too (to the current month only, because it would be infinite)
	setRepetition( date, action );

	// repaint all cells
	updateCells();

	// select date that the action was added from (to show action instatnly in the actions list)
	selectDate( date );
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
		QColor _grayColor = QColor( 230, 230, 230 );
		if( date != m_selectedDate ) painter->setPen( QPen( _grayColor, 2 ) );
		painter->setBrush( _grayColor );
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

			// item on the list is displayed in "H:MM:SS Name" form, so we get time here and modify value to 2-numbers, except for hour
			QString _strHour = QString::number( _action->getHours() );
			QString _strMinute = "";
			QString _strSecond = "";
			int _minute = _action->getMinutes();
			if( _minute < 10 ) {
				_strMinute = "0" + QString::number( _minute );
			}
			int _second = _action->getSeconds();
			if( _second < 10 ) {
				_strSecond = "0" + QString::number( _second );
			}
			QString _strTime = _strHour + ":" + _strMinute + ":" + _strSecond;

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
			m_actionsInMonth[it.key()].push_back( _pAction );
			setRepetition( it.key(), _pAction );
		}
	}
}