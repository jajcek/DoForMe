#pragma once

#include <qcalendarwidget.h>
#include <qpainter.h>
#include <qvector.h>
#include <qmap.h>
#include <qlistwidget.h>
#include "action.h"
#include "action_settings.h"
#include "database.h"

class ActionsCalendar : public QCalendarWidget {
	Q_OBJECT

private:
	QDate m_selectedDate;
	int m_displayedMonth;
	int m_displayedYear;
	static QTableWidget* m_list;
	Action* m_pCurrAction;
	QVector<QDate> m_datesOrder;
	QVector<Action*> m_actionsOrder;

	// actions (date => vector of actions)
	QMap<QDate, QVector<Action*> > m_actionsAll;
	QMap<QDate, QVector<Action*> > m_actionsInMonth;

private:
	void drawActionsNum( QPainter* painter, const QRect& rect, unsigned actionsNumber ) const;
	void drawExclamation( QPainter* painter, const QRect& rect ) const;
	void setRepetition( QDate date, Action* action );

public:
	ActionsCalendar( QWidget* pParent );
	// remember to free actions later ~ActionsCalendar();
	void addAction( QDate, Action* );
	Action* getAction( int itemNumber ) const;
	Action* getCurrentAction() const;
	void detachCurrentAction();
	void removeCurrentAction();
	void removeCurrentActions();
	// only for the current month!
	QVector<Action*> getActionsForDate( QDate date ) const;
	void setCurrentAction( Action* action );
	static void setList( QTableWidget* list );
	QDate getSelectedDate() const;
	void refreshRepetitions();
	void saveData() const;
	void loadData();

protected:
	void paintCell( QPainter* painter, const QRect& rect, const QDate& date ) const;

protected slots:
	void selectDate( const QDate& );
	void setCurrentPage( int year, int month );
};