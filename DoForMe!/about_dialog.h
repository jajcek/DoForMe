#pragma once

#include <qdialog.h>
#include <qimage.h>
#include <qdesktopwidget.h>
#include <qpainter.h>
#include <qicon.h>
#include <qlabel.h>
#include "ui_about.h"

/**
	\class AboutDialog about_dialog.h "about_dialog.h"
	\brief "About" dialog.
	\details Layout for the dialog has been made in Qt Designer.
	The only thing that is generated in this code is a gradient background for a logo.
	\author Jacek Topolski
	\version 1.0
	\date 6.07.2012
*/
class AboutDialog : public QDialog {
private:
	/**
		\brief Width of the dialog.
	*/
	unsigned m_iWidth;
	/**
		\brief Height of the dialog.
	*/
	unsigned m_iHeight;

	/**
		\brief Object containing logo image.
		\details The path to the image is ":/mainWin/logo.png".
	*/
	QImage logo;

	/**
		\brief Object containing all controls of the dialog.
	*/
	Ui::aboutDialog ui;

public:
	/**
		\brief Initializes size, image and icon.
		\details Initializes size of the window in the initialization list as well as sets icon for the window and loads logo image.
		Moreover position the window to the center of the screen.
	*/
	AboutDialog();

protected:
	/**
		\brief Function which draws gradient background behind the logo image.
	*/
	void paintEvent( QPaintEvent* p );
};