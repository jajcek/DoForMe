#include "calendar.h"

QTableWidget* ActionsCalendar::m_list = NULL;

void ActionsCalendar::drawActionsNum( QPainter* painter, const QRect& rect, unsigned actionsNumber ) const {
	painter->setPen( Qt::black );
	// get number of actions
	QString _actionsNumber;
	_actionsNumber.setNum( actionsNumber );

	// set font size (and get current font size to get back to it later)
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
	QImage _exclamationImage( ":/mainWin/Resources/exclamation.png" );
	QRect _rect( rect.left() + rect.width() - 16, rect.top() + 1, 12, 12 );
	painter->drawImage( _rect, _exclamationImage );
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
		
		// if the date has been excluded from repetitions
		if( action->isExcluded( _shiftedDate ) ) {
			continue;
		}

		// set repetition for every X days
		if( _XDays != 0 ) {
			if( _shift % _XDays == 0 ) {
				m_actionsInMonth[_shiftedDate].push_back( action );
				continue;
			}
		}
		
		// set necessary days in calendar
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
}

Action* ActionsCalendar::getAction( int itemNumber ) const {
	return m_actionsInMonth.find( m_selectedDate ).value().at( itemNumber );
}

Action* ActionsCalendar::getCurrentAction() const {
	return m_pCurrAction;
}

void ActionsCalendar::detachCurrentAction() {
	if( !m_pCurrAction ) return;

	m_pCurrAction->setHighlight( false );

	// exclude date from the action
	m_pCurrAction->excludeDate( m_selectedDate );

	// create new action and add it to calendar
	Action* _newAction = new Action( m_pCurrAction );
	addAction( m_selectedDate, _newAction );
	setCurrentAction( _newAction );

	refreshRepetitions();

	// highlight detached action (it is neccessary to do that after addAction and
	// refreshRepetitions methods, because they calls selectDate method which
	// resets selection in some cases
	_newAction->setHighlight( true );
}

void ActionsCalendar::removeCurrentAction() {
	if( m_pCurrAction == NULL ) return;

	// exclude date from the action
	m_pCurrAction->excludeDate( m_selectedDate );

	refreshRepetitions();
}

void ActionsCalendar::removeCurrentActions() {
	// go through all actions and choose the actions with repetitions
	// notice that we only need to remove it from m_actionsAll, because
	// refreshRepetition called at the bottom calls setRepetition method
	// that creates repetitions (m_actionsInMonth) on the grounds of m_actionsAll
	QMapIterator<QDate, QVector<Action*> > itAll( m_actionsAll );
	while( itAll.hasNext() ) {
		itAll.next();

		// go through all actions for day
		int _actionsNumber = itAll.value().size();
		for( int i = 0; i < _actionsNumber; ++i ) {
			if( itAll.value().at( i )->getId() == m_pCurrAction->getId() ) {
				// free memory for the action
				delete m_pCurrAction;
				m_pCurrAction = NULL;

				// remove the action from the map of actions
				m_actionsAll.find( itAll.key() ).value().remove( i );

				goto go_out;
			}
		}
	}

go_out:
	refreshRepetitions();
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

void ActionsCalendar::refreshRepetitions() {
	// clear before setting actions again (to prevent summing actions)
	m_actionsInMonth.clear();

	// go through all actions and choose the actions with repetitions
	QMapIterator<QDate, QVector<Action*> > it( m_actionsAll );
	while( it.hasNext() ) {
		it.next();

		// go through all actions for day
		int _actionsNumber = it.value().size();
		for( int i = 0; i < _actionsNumber; ++i ) {
			Action* _pAction = it.value().at( i );
			if( !_pAction->isExcluded( it.key() ) )
				m_actionsInMonth[it.key()].push_back( _pAction );
			setRepetition( it.key(), _pAction );
		}
	}

	// we need to clear list and put everything again
	// we chose the easier way - removing all from the table and recreate it
	// with new action
	m_list->clearContents();
	selectDate( m_selectedDate );

	updateCells();
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
	if( m_actionsInMonth.contains( date ) ) {
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
			for( int i = 0; i < _actionsNumber - 1; ++i ) {
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
		if( _isConflict )
			_color = QColor( 255, 201, 14 );
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
		if( _isConflict ) {
			drawExclamation( painter, rect );
		}
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
	// remember values by which the user sorts the elements
	int _column = m_list->horizontalHeader()->sortIndicatorSection();
	Qt::SortOrder _order  = m_list->horizontalHeader()->sortIndicatorOrder();

	// we need to disable sorting for putting elements
	m_list->setSortingEnabled( false );

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
	m_list->setRowCount( 0 );

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
			QTableWidgetItem* _no     = new QTableWidgetItem( QString::number( i + 1 ) );
			QTableWidgetItem* _time   = new QTableWidgetItem( _strTime );
			QTableWidgetItem* _script = new QTableWidgetItem( _actions.at( i )->getScript()->getFileName() );
			m_list->setItem( i, 0, _no );
			m_list->setItem( i, 1, _time );
			m_list->setItem( i, 2, _script );
		}
	}

	// re-enable sorting and sort items by its number (to keep determining of displaying same script names)
	// and by the user preference
	m_list->setSortingEnabled( true );
	m_list->sortItems( 0, Qt::AscendingOrder );
	m_list->sortItems( _column, _order );

	// when selectedDate it called it invokes automatically updateCell() for current cell
	// but we need to update all cells to change theirs colors if necessary
	updateCells();
}

void ActionsCalendar::setCurrentPage( int year, int month ) {
	m_displayedMonth = month;
	m_displayedYear = year;

	refreshRepetitions();
}