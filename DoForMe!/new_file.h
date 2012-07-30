#include <qobject.h>
#include <qdialog.h>
#include <qlayout.h>
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qfile.h>
#include <qmessagebox.h>

class NewFile : public QDialog {
	Q_OBJECT

private:
	QVBoxLayout* m_layout;
	QHBoxLayout* m_buttonLayout;

	QPushButton* m_ok;
	QPushButton* m_cancel;

	QLineEdit* m_title;
	QLineEdit* m_filename;
	QTextEdit* m_desc;

public:
	NewFile();
	~NewFile();

	QString getTitle() const;
	QString getFileName() const;
	QString getDescription() const;

public slots:
	void createFileNameFromTitle( const QString& );
	void clickedOk();

};