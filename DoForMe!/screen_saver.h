#include <qstring.h>
#include <qvector.h>
#include <qdialog.h>
#include <qpixmap.h>
#include <qapplication.h>
#include <qdesktopwidget.h>
#include <qpaintengine.h>
#include <qdir.h>
#include <Windows.h>
#include "conf.h"

class ScreenSaver : public QDialog {
private:
	int m_sx;
	int m_sy;
	int m_ex;
	int m_ey;
	QVector<COLORREF> m_topLine;
	QVector<COLORREF> m_leftLine;
	QVector<COLORREF> m_bottomLine;
	QVector<COLORREF> m_rightLine;

	QImage desktop;

	static ScreenSaver* object;

	ScreenSaver();

public:
	static ScreenSaver* getInstance();

	void setStartPoint( int x, int y );

	void setEndPoint( int x, int y );

	void setCurrentDesktop();

	QString saveSelectedFragment();

	void resetPoints();

	void paintEvent( QPaintEvent* p );
};