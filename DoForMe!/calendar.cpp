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
	qDebug( "ActionsCalendar::setRepetition()" );

	if( !action->isXDays() && action->getDays() == 0 ) return;

	// how many days has the current month
	//int _daysNumber = date.daysInMonth();

	int _XDays = 0;
	// if the user set "every X days" option get its value
	if( action->isXDays() ) {
		 _XDays = action->getXDays();
	}

	// get selected days of week
	int _days = action->getDays();

	// go through all days from current date to the end of month
	// (balance is for previous and next month, because there are some days that are still visible)
	// because at beginning of calendar there are visible some days of previous month
	// we need to multiply balance in a loop because we subtract it later
	int _otherMonth = 31;
	for( int i = date.day(); i <= 3 * _otherMonth; ++i ) {
		// we will shift date about +1 day per iteration
		// it is necessary to add days if we have chosen further month on the calendar
		int _toNextMonths = date.daysTo( QDate( m_displayedYear, m_displayedMonth, 1 ) );
		
		// we need to correct it to not go before selected date
		_toNextMonths = _toNextMonths < 0 ? 0 : _toNextMonths;
		//qDebug( "_toNextMonth: %d", _toNextMonths );
		int _shift = i - date.day() + _toNextMonths - _otherMonth;
		//qDebug( "_shift: %d", _shift );
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

int ActionsCalendar::findIndexOf( Action* action ) {
	int _index = -1;

	// go through all actions for day
	auto _actions = m_actionsAll.find( action->getMainDate() ).value();
	int _actionsNumber = _actions.size();
	for( _index = 0; _index < _actionsNumber; ++_index ) {
		if( _actions.at( _index )->getId() == m_pCurrAction->getId() ) 
			return _index;
	}

	return _index;
}

void ActionsCalendar::moveExcludedDates( Action* action, const int days ) {
	qDebug( "ActionsCalendar::moveExcludedDates()" );

	QVector<QDate> _movedExcludedDates;

	// get vector of excluded dates
	auto _excludedDates = action->getExcludedDates();
	// if we want to move our actions up, we have to add -7 days, down -> 7 days, left -> -1, right -> 1.
	int _datesNumber = _excludedDates.size();
	for( int i = 0; i < _datesNumber; ++i ) {
		QDate _movedDate = _excludedDates.at( i ).addDays( days );
		_movedExcludedDates.push_back( _movedDate );
	}

	// set moved excluded dates into the action
	action->setExcludedDates( _movedExcludedDates );
}

ActionsCalendar::ActionsCalendar( QWidget* pParent ) : m_selectedDate( QDate::currentDate() ), m_displayedMonth( 0 ),
													   m_displayedYear( 0 ), m_pCurrAction( NULL ) {
	qDebug( "ActionsCalendar::ActionsCalendar()" );

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

	// load all actions from database
	loadData();

	// select current date
	selectDate( QDate::currentDate() );

	
}

ActionsCalendar::~ActionsCalendar() {
	qDebug( "ActionsCalendar::~ActionsCalendar()" );

	removeAllActions();
}

void ActionsCalendar::addAction( QDate date, Action* action ) {
	qDebug( "ActionsCalendar::addAction()" );

	// add new action for a specified date and repaint cells
	// and container with actions for a selected month
	if( !action->isExcluded( date ) )
		m_actionsInMonth[date].push_back( action );
	// add the action to the container with all actions
	m_actionsAll[date].push_back( action );

	// if an action has options 'every X days' or on 'Monday' etc.
	// we have to set it to the calendar too (to the current month only, because it would be infinite)
	setRepetition( date, action );
}

Action* ActionsCalendar::getActionById( int id, bool forSelectedDate ) const {
	qDebug( "ActionsCalendar::getActionById()" );

	if( forSelectedDate ) {
		if( m_actionsInMonth.find( m_selectedDate ) != m_actionsInMonth.end() ) {
			auto _actions = m_actionsInMonth.find( m_selectedDate ).value();
			int _actionsNumber = _actions.size();
			for( int i = 0; i < _actionsNumber; ++i ) {
				Action* _pAction = _actions.at( i );
				if( _pAction->getId() == id )
					return _pAction;
			}
		}
	} else {
		QMapIterator<QDate, QVector<Action*>> it( m_actionsAll );
		while( it.hasNext() ) {
			it.next();
			int _actionsNumber = it.value().size();
			for( int i = 0; i < _actionsNumber; ++i ) {
				Action* _pAction = it.value().at( i );
				if( _pAction->getId() == id )
					return _pAction;
			}
		}
	}

	return NULL;
}

Action* ActionsCalendar::getCurrentAction() const {
	qDebug( "ActionsCalendar::getCurrentAction()" );

	return m_pCurrAction;
}

void ActionsCalendar::detachCurrentAction() {
	qDebug( "ActionsCalendar::detachCurrentAction()" );

	if( !m_pCurrAction ) return;
	if( !( m_pCurrAction->isXDays() || m_pCurrAction->getDays() ) ) return;

	m_pCurrAction->setHighlight( false );

	// exclude date from the action
	m_pCurrAction->excludeDate( m_selectedDate );

	// create new action and add it to calendar
	Action* _newAction = new Action( m_pCurrAction );
	_newAction->setMainDate( m_selectedDate );
	addAction( m_selectedDate, _newAction );
	setCurrentAction( _newAction );

	refreshRepetitions();

	// highlight detached action (it is neccessary to do that after addAction and
	// refreshRepetitions methods, because they calls selectDate method which
	// resets selection in some cases
	_newAction->setHighlight( true );
}

void ActionsCalendar::removeCurrentAction() {
	qDebug( "ActionsCalendar::removeCurrentAction()" );

	if( m_pCurrAction == NULL ) return;

	// exclude date from the action
	m_pCurrAction->excludeDate( m_selectedDate );

	refreshRepetitions();
}

void ActionsCalendar::removeCurrentActions() {
	qDebug( "ActionsCalendar::removeCurrentActions()" );

	// go through all actions and choose the actions with repetitions
	// notice that we only need to remove it from m_actionsAll, because
	// refreshRepetition called at the bottom calls setRepetition method
	// that creates repetitions (m_actionsInMonth) on the grounds of m_actionsAll

	// go through all actions for day
	auto _actions = & m_actionsAll.find( m_pCurrAction->getMainDate() ).value();

	// remove the action from the map of actions
	_actions->remove( findIndexOf( m_pCurrAction ) );

	delete m_pCurrAction;
	m_pCurrAction = NULL;

	refreshRepetitions();
}

void ActionsCalendar::removeAllActions() {
	qDebug( "ActionsCalendar::removeAllActions()" );

	// go through all actions and choose the actions with repetitions
	QMapIterator<QDate, QVector<Action*> > it( m_actionsAll );
	while( it.hasNext() ) {
		it.next();
		// go through all actions for a day
		int _actionsNumber = it.value().size();
		for( int i = 0; i < _actionsNumber; ++i ) {
			delete it.value().at( i );
		}
	}

	m_actionsAll.clear();
	m_actionsInMonth.clear();
}

void ActionsCalendar::moveCurrAction( int direction ) {
	qDebug( "ActionsCalendar::moveCurrAction()" );

	if( !m_pCurrAction ) return;

	// find the index where the actions resides at in the vector
	int _index = findIndexOf( m_pCurrAction );

	QDate _movedDate;
	int _days = 0;
	switch( direction ) {
		case UP:
			_days = -7;
			break;
		case DOWN:
			_days = 7;
			break;
		case LEFT:
			_days = -1;
			break;
		case RIGHT:
			_days = 1;
			break;
	}

	// get date for main action
	_movedDate = m_pCurrAction->getMainDate().addDays( _days );

	// remove and reinsert the action at the appropriate index
	m_actionsAll.find( m_pCurrAction->getMainDate() ).value().remove( _index );
	m_actionsAll[_movedDate].push_back( m_pCurrAction );
	moveExcludedDates( m_pCurrAction, _days );

	// get id to select the action after moving (there can be more than one actions in a day)
	// that will cause to make currently active action as inactive
	int _id = m_pCurrAction->getId();

	// set main date for newly positioned action
	m_pCurrAction->setMainDate( _movedDate );

	// keep tracking the action and refresh
	selectDate( m_selectedDate.addDays( _days ) );
	refreshRepetitions();

	setCurrentAction( getActionById( _id ) );
	
	updateCells();
}

void ActionsCalendar::setCurrentAction( Action* action ) {
	qDebug( "ActionsCalendar::setCurrentAction()" );

	if( !action ) return;

	m_pCurrAction = action;
	m_pCurrAction->setHighlight( true );
	
	// enable calendar tools
	CalendarTools::enableForAction( m_pCurrAction );
}

QVector<Action*> ActionsCalendar::getActionsForDate( QDate date ) const {
	qDebug( "ActionsCalendar::getActionsForDate()" );

	QVector<Action*> _actions;

	if( m_actionsInMonth.contains( date ) )
		return m_actionsInMonth.find( date ).value();
	else
		return _actions;
}

void ActionsCalendar::setList( QTableWidget* list ) {
	m_list = list;
}

QDate ActionsCalendar::getSelectedDate() const {
	qDebug( "ActionsCalendar::getSelectedDate()" );

	return m_selectedDate;
}

void ActionsCalendar::refreshRepetitions() {
	qDebug( "ActionsCalendar::refreshRepetitions()" );

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

void ActionsCalendar::saveData() const {
	qDebug( "ActionsCalendar::saveData()" );

	// open database
	Database _db( "actions" );
	// if the table for actions doesn't exists it creates new one,
	// otherwise it clears the current table content
	_db.prepareTableForActions();

	// insert all actions
	QMapIterator<QDate, QVector<Action*> > it( m_actionsAll );
	while( it.hasNext() ) {
		it.next();
		// go through all actions for day
		int _actionsNumber = it.value().size();
		for( int i = 0; i < _actionsNumber; ++i ) {
			Action* _pAction = it.value().at( i );
			_db.insertAction( it.key(), _pAction );
		}
	}
}

void ActionsCalendar::loadData() {
	qDebug( "ActionsCalendar::loadData()" );

	// open database
	Database* _db = new Database( "actions" );

	auto _actions = _db->selectActions();

	int _actionsNumber = _actions.size();
	for( int i = 0; i < _actionsNumber; ++i ) {
		QDate _date = _actions.at( i ).first;
		Action* _pAction = _actions.at( i ).second;
		addAction( _date, _pAction );
	}

	delete _db;
}

bool ActionsCalendar::isScriptUsed( Script* pScript ) const {
	QMapIterator<QDate, QVector<Action*>> _it( m_actionsAll );
	while( _it.hasNext() ) {
		_it.next();

		auto _actions = _it.value();
		int _actionsNumber = _actions.size();
		for( int i = 0; i < _actionsNumber; ++i ) {
			Action* _pAction = _actions.at( i );
			if( _pAction->getScript()->getFileName() == pScript->getFileName() )
				return true;
		}
	}

	return false;
}

void ActionsCalendar::removeActionsUsingScript( Script* pScript ) {
	QMapIterator<QDate, QVector<Action*>> _it( m_actionsAll );
	while( _it.hasNext() ) {
		_it.next();

		// get vector of actions
		auto _actions = & _it.value();
		int _actionsNumber = _actions->size();
		// go through all actions
		for( int i = 0; i < _actionsNumber; ++i ) {
			Action* _pAction = _actions->at( i );
			if( _pAction->getScript() == pScript ) {
				delete _actions->at( i );
				m_actionsAll[_it.key()].remove( i );
			}	
		}
	}

	refreshRepetitions();
}

void ActionsCalendar::paintCell( QPainter* painter, const QRect& rect, const QDate& date ) const {
	// called for every cell, too much - bad for debugging
	//qDebug( "ActionsCalendar::paintCell()" );

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
	qDebug( "ActionsCalendar::selectDate()" );

	// remember values by which the user sorts the elements
	int _column = m_list->horizontalHeader()->sortIndicatorSection();
	Qt::SortOrder _order  = m_list->horizontalHeader()->sortIndicatorOrder();

	// we need to disable sorting for putting elements
	m_list->setSortingEnabled( false );

	// remove current highlights to set up new one
	if( m_pCurrAction ) {
		m_pCurrAction->setHighlight( false );
	}

	// if there is only one action for that day, we will hightlight it
	// without selecting it on the actions list
	if( m_actionsInMonth.contains( date ) ) {
		if( m_actionsInMonth.find( date ).value().size() == 1 ) {
			setCurrentAction( m_actionsInMonth.find( date ).value().at( 0 ) );
		} else {
			m_pCurrAction = NULL;
			CalendarTools::disableForAction();
		}
	} else {
		m_pCurrAction = NULL;
		CalendarTools::disableForAction();
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
			Action* _pAction = _actions.at( i );

			// item on the list is displayed in "HH:MM:SS Name" form, so we get time here
			QString _strTime = _pAction->getHoursHH() + ":" + _pAction->getMinutesMM() + ":" + _pAction->getSecondsSS();

			// add finally the item to the list
			QTableWidgetItem* _no     = new QTableWidgetItem();
			_no->setData( Qt::DisplayRole, _pAction->getId() + 1 );
			QTableWidgetItem* _time   = new QTableWidgetItem( _strTime );
			QTableWidgetItem* _script = new QTableWidgetItem( _pAction->getScript()->getFileName() );
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

	// original method uses setCurrentPage and we need to change page if the selected date is out of current month
	QCalendarWidget::setSelectedDate( date );

	// when selectedDate it called it invokes automatically updateCell() for current cell
	// but we need to update all cells to change theirs colors if necessary
	updateCells();
}

void ActionsCalendar::setCurrentPage( int year, int month ) {
	qDebug( "ActionsCalendar::setCurrentPage()" );

	m_displayedMonth = month;
	m_displayedYear = year;

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

	updateCells();
}