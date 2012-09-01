#include "mainwin.h"
#include <QtGui/QApplication>
#include <qtextcodec.h>


int main( int argc, char* argv[] ) {
	// used to recognize polish symbols like ¹, ê, œ, æ, ñ etc.
	QTextCodec::setCodecForCStrings( QTextCodec::codecForName( "Windows-1250" ) );

	QApplication a( argc, argv );
	a.setQuitOnLastWindowClosed( false );
	mainWin w;
	w.show();
	return a.exec();
}
