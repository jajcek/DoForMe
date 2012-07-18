#pragma once

#include <qcalendarwidget.h>
#include <qpainter.h>
#include <qmap.h>

class DetailedCalendar : public QCalendarWidget {
	Q_OBJECT

private:
	QDate m_selectedDate;
	int m_displayedMonth;
	// date & script file name
	QMap<QDate, QVector<QString> > m_actions;

private:
	void drawActions( QPainter* painter, const QRect& rect, unsigned actionsNumber ) const;

public:
	DetailedCalendar( QWidget* pParent );

protected:
	void paintCell( QPainter* painter, const QRect& rect, const QDate& date ) const;

protected slots:
	void select( const QDate& );
	void setCurrentPage( int year, int month );
};