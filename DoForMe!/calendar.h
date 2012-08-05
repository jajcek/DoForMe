#pragma once

#include <qcalendarwidget.h>
#include <qpainter.h>
#include <qmap.h>
#include <qlistwidget.h>
#include "action.h"

class DetailedCalendar : public QCalendarWidget {
	Q_OBJECT

private:
	QDate m_selectedDate;
	int m_displayedMonth;
	static QListWidget* m_list;

	// actions (date => vector of actions)
	QMap<QDate, QVector<Action*> > m_actionsAll;
	QMap<QDate, QVector<Action*> > m_actionsInMonth;

private:
	void drawActionsNum( QPainter* painter, const QRect& rect, unsigned actionsNumber ) const;

public:
	DetailedCalendar( QWidget* pParent );
	// remember to free actions later ~DetailedCalendar();
	void addAction( QDate, Action* );
	static void setList( QListWidget* list );
	QDate getSelectedDate() const;

protected:
	void paintCell( QPainter* painter, const QRect& rect, const QDate& date ) const;

protected slots:
	void selectDate( const QDate& );
	void setCurrentPage( int year, int month );
};