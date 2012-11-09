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

/**
	\class ScreenSaver screen_saver.h "screen_saver.h"
	\brief Provides functionality of selecting a fragment of the desktop and save it to a file.
	\details Object of the class is a singleton which provides a form (with attribute 'always on top')
	which the snapshot of the entire desktop resides on.
	\author Jacek Topolski
	\version 1.0
	\date 4.09.2012
*/
class ScreenSaver : public QDialog {
private:
	/**
		\brief Value for the left point of the rectangle.
	*/
	int m_sx;
	/**
		\brief Value for the top point of the rectangle.
	*/
	int m_sy;
	/**
		\brief Value for the right point of the rectangle.
	*/
	int m_ex;
	/**
		\brief Value for the bottom point of the rectangle.
	*/
	int m_ey;

	/**
		\brief Field which keeps image of the entire desktop.
	*/
	QImage desktop;

	/**
		\brief The instance of the singleton.
	*/
	static ScreenSaver* object;
	/**
		\brief Private constructor to make the class a singleton.
		\details Also initializes values for left top point of the rectangle.
	*/
	ScreenSaver();

public:
	/**
		\brief Gets the only isntance of the object.
	*/
	static ScreenSaver* getInstance();
	/**
		\brief Sets starting point - left top point of the rectangle.
		\param[in] x Distance from left side of the screen.
		\param[in] y Distance from top side of the screen.
	*/
	void setStartPoint( int x, int y );
	/**
		\brief Sets ending point - right bottom point of the rectangle.
		\param[in] x Distance from left side of the screen.
		\param[in] y Distance from top side of the screen.
	*/
	void setEndPoint( int x, int y );
	/**
		\brief Gets snapshot of the current desktop and displays it (actually it is displayed in ScreenSaver::paintEvent method).
	*/
	void setCurrentDesktop();
	/**
		\brief Saves selected fragment to a file.
		\details All of the saved files are kept in scripts/pic/ directory where each of them is named picX.bmp,
		where X is an incremental number like pic0.bmp, pic1.bmp and so on.
	*/
	QString saveSelectedFragment();
	/**
		\brief Sets all of the coordinates fields (m_sx etc.) to -1 which causes to not draw a red rectangle.
	*/
	void resetPoints();
	/**
		\brief Engine for drawing snapshots and the red rectangle.
	*/
	void paintEvent( QPaintEvent* p );
};