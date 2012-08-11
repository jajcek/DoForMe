#include "calendar.h"

QTableWidget* ActionsCalendar::m_list = NULL;

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

void ActionsCalendar::drawExclamation( QPainter* painter, const QRect& rect ) const {
	QPoint trianglePoints[3];
	trianglePoints[0].setX( rect.left() + rect.width() - 16 );
	trianglePoints[0].setY( rect.top() + 10 );
	trianglePoints[1].setX( rect.left() + rect.width() - 10 );
	trianglePoints[1].setY( rect.top() + 10 );
	trianglePoints[2].setX( rect.left() + rect.width() - 13 );
	trianglePoints[2].setY( rect.top() + rect.height() - 5 );

	painter->drawPolygon( trianglePoints, 3 );
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

ActionsCalendar::ActionsCalendar( QWidget* pParent ) : m_selectedDate( QDate::currentDate() ), m_displayedMonth( 0 ),
													   m_displayedYear( 0 ), m_pCurrAction( NULL ) {
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

	// repaint all cells
	updateCells();

	// select date that the action was added from (to show action instantly in the actions list)
	selectDate( date );
}

Action* ActionsCalendar::getAction( int itemNumber ) const {
	// get time values from actions list
	/*int _hours   = m_list->item( itemNumber )->text().left( 2 ).toInt();
	int _minutes = m_list->item( itemNumber )->text().mid( 3, 2 ).toInt();
	int _seconds = m_list->item( itemNumber )->text().mid( 6, 2 ).toInt();

	// go through actions in that day (if this method is called it mean that a user has selected date already
	// so we can use m_selectedDate field of this class
	QVector<Action*> _actionsVec = m_actionsInMonth[m_selectedDate];
	int _actionsNumber = _actionsVec.size();
	for( int i = 0; i < _actionsNumber; ++i ) {
		// find the appropriate action by time
		int _itHours   = _actionsVec.at( i )->getHours();
		int _itMinutes = _actionsVec.at( i )->getMinutes();
		int _itSeconds = _actionsVec.at( i )->getSeconds();

		if( _itHours == _hours && _itMinutes == _minutes && _itSeconds == _seconds ) {
			if( itemNumber == 0 )
				return _actionsVec.at( i );
			else
				--itemNumber;
		}
	}
	*/
	return NULL;
}

Action* ActionsCalendar::getCurrentAction() const {
	return m_pCurrAction;
}

void ActionsCalendar::setCurrentAction( Action* action ) {
	m_pCurrAction = action;
}

QVector<Action*> ActionsCalendar::getActionsForDate( QDate date ) const {
	return m_actionsInMonth.find( date ).value();
}

void ActionsCalendar::setList( QTableWidget* list ) {
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

	// check if on this date there are any highlighted actions (for repetition purposes)
	// we will change color for that cell then (check loop below too)
	bool _isAnyHighlighted = false;
	bool _isConflict = false;
	if( m_actionsInMonth.find( date ) != m_actionsInMonth.end() ) {
		QVector<Action*> _pActions = m_actionsInMonth.find( date ).value();
		int _actionsNumber = _pActions.size();
		for( int i = 0; i < _actionsNumber; ++i ) {
			if( _pActions.at( i )->isHighlighted() ) {
				_isAnyHighlighted = true;
				break;
			}
		}

		// find conflicts (two actions at the same time, it can be possible with repetitions)
		if( _actionsNumber > 1 )
			for( int i = 0; i < _actionsNumber; ++i ) {
				if( _pActions.at( i )->getTime() == _pActions.at( i + 1 )->getTime() ) {
					_isConflict = true;
					break;
				}
			}
	}

	// if action for the date exists
	if( m_actionsInMonth.contains( date ) ) {
		// there would be black border (because of above)
		// but we want to draw the black border only if it is selected, otherwise draw gray border
		QColor _color = QColor( 230, 230, 230 );
		if( _isConflict ) {
			_color = QColor( 255, 201, 14 );
			drawExclamation( painter, rect );
		}
		if( _isAnyHighlighted )
			_color = QColor( 184, 221, 239 );
		if( date != m_selectedDate ) painter->setPen( QPen( _color, 2 ) );
		painter->setBrush( _color );
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
	// remove current highlights to set up new
	if( m_pCurrAction ) {
		m_pCurrAction->setHighlight( false );
	}

	// if there is only one action for that day, we will hightlight it
	// without selecting it on the actions list
	if( m_actionsInMonth.contains( date ) ) {
		if( m_actionsInMonth.find( date ).value().size() == 1 ) {
			m_pCurrAction = m_actionsInMonth.find( date ).value().at( 0 );
			m_pCurrAction->setHighlight( true );
		}
	}

	// set new selected date
	m_selectedDate = date;

	// clear the list to prepare it for another day
	m_list->clearContents();

	// fill up the list with new actions
	if( m_actionsInMonth.contains( date ) ) {
		QVector<Action*> _actions = m_actionsInMonth.find( date ).value();

		// go through all actions
		int _actionsNumber = _actions.size();
		m_list->setRowCount( _actionsNumber );
		for( int i = 0; i < _actions.size();  ++i ) {
			Action* _action = _actions.at( i );

			// item on the list is displayed in "HH:MM:SS Name" form, so we get time here and modify value to 2-numbers, except for hour
			int _hour = _action->getHours();
			int _minute = _action->getMinutes();
			int _second = _action->getSeconds();
			QString _strHour = QString::number( _hour );
			QString _strMinute = QString::number( _minute );
			QString _strSecond = QString::number( _second );

			if( _hour < 10 ) {
				_strHour = "0" + _strHour;
			}
			if( _minute < 10 ) {
				_strMinute = "0" + _strMinute;
			}
			if( _second < 10 ) {
				_strSecond = "0" + _strSecond;
			}
			QString _strTime = _strHour + ":" + _strMinute + ":" + _strSecond;

			// add finally the item to the list
			QTableWidgetItem* _no     = new QTableWidgetItem( QString::number( m_list->rowCount() ) );
			QTableWidgetItem* _time   = new QTableWidgetItem( _strTime );
			QTableWidgetItem* _script = new QTableWidgetItem( _actions.at( i )->getScript()->getFileName() );
			m_list->setItem( i, 0, _no );
			m_list->setItem( i, 1, _time );
			m_list->setItem( i, 2, _script );
		}
	}

	// when selectedDate it called it invokes automatically updateCell() for current cell
	// but we need to update all cells to change theirs colors if necessary
	updateCells();
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