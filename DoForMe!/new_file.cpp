#include "new_file.h"

QString NewFile::DIR = "scripts/";

NewFile::NewFile() : m_layout( new QVBoxLayout() ), m_buttonLayout( new QHBoxLayout() ),
					 m_ok( new QPushButton( "Finish" ) ), m_cancel( new QPushButton( "Cancel" ) ),
					 m_desc( new QTextEdit() ), m_filename( new QLineEdit ), m_title( new QLineEdit() ) {
	
	connect( m_ok,     SIGNAL( clicked() ), SLOT( clickedOk() ) );
	connect( m_cancel, SIGNAL( clicked() ), SLOT( reject() ) );
	connect( m_title,  SIGNAL( textChanged( const QString& ) ), SLOT( createFileNameFromTitle( const QString& ) ) );
						 
	// dialog can't be resized vertically
	setMaximumHeight( height() );

	// text field for description (needed to write it here, to resize it)
	m_desc->setMaximumHeight( 60 );

	m_buttonLayout->addWidget( m_ok );
	m_buttonLayout->addWidget( m_cancel );

	m_layout->addWidget( new QLabel( "Title:" ) );
	m_layout->addWidget( m_title );
	m_layout->addWidget( new QLabel( "File name:" ) );
	m_layout->addWidget( m_filename );
	m_layout->addWidget( new QLabel( "Description (optional):" ) );
	m_layout->addWidget( m_desc );
	m_layout->addLayout( m_buttonLayout );

	// set main layout for the dialog
	setLayout( m_layout );
}

NewFile::~NewFile() {
	delete m_title;
	delete m_filename;
	delete m_desc;
	delete m_ok;
	delete m_cancel;
	delete m_buttonLayout;
	delete m_layout;
}

QString NewFile::getTitle() const {
	return m_title->text();
}

QString NewFile::getFileName() const {
	return m_filename->text();
}

QString NewFile::getDescription() const {
	return m_desc->toPlainText();
}

void NewFile::createFileNameFromTitle( const QString& text ) {
	QString _modifiedTitle = text;

	// chars excluded from name for a file (0x127 - delete key)
	char _invalidChars[] = { 0x127, ' ', '"', '*', '/', ':', '<', '>', '?', '\\', '[', ']', '|' };

	// replace all invalid chars with _
	int _len = strlen( _invalidChars );
	for( int i = 0; i < _len; ++i ) {
		_modifiedTitle.replace( _invalidChars[i], "_" );
	}

	// add .apc at the end of the string
	_modifiedTitle += ".apc";

	// set the second edit field
	m_filename->setText( _modifiedTitle );
}

void NewFile::clickedOk() {
	/*QString _strFileName = m_filename->text();

	if( !ScriptsManager::addScript( new Script( DIR + _strFileName ) ) ) {
		QMessageBox _msg( QMessageBox::Critical, "Error", "Script with such title already exists. Rename it.",
						QMessageBox::Ok );
		_msg.exec();

		return;
	}

	// if such file already exists show error
	if( QFile::exists( "scripts/" + _strFileName ) ) {
		QMessageBox _msg( QMessageBox::Critical, "Error", "File with such name already exists. Rename it.",
						QMessageBox::Ok );
		_msg.exec();

		return;
	}

	accept();*/
}