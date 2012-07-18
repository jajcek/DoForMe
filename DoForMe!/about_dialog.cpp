#include "about_dialog.h"

AboutDialog::AboutDialog() : m_iWidth( 500 ), m_iHeight( 200 ) {
	ui.setupUi( this );

	QDesktopWidget screen;
	setGeometry( ( screen.width() - m_iWidth ) / 2, ( screen.height() - m_iHeight ) / 2, m_iWidth, m_iHeight );

	setWindowIcon( QIcon( ":/mainWin/logo.png" ) );

	logo.load( ":/mainWin/logo.png" );
}

void AboutDialog::paintEvent( QPaintEvent* p ) {
	QPainter painter( this );

	QLinearGradient fade( 0, m_iHeight, 200, 0 );
    fade.setColorAt( 0, QColor( 0, 0, 0, 255 ) );
    fade.setColorAt( 1, QColor( 0, 0, 0, 0 ) );
    painter.fillRect( 0, 0, 180, 200 , fade );

	painter.drawImage( 0, 0, logo );
}