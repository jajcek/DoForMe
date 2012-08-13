/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created: Mon 13. Aug 19:08:37 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_aboutDialog
{
public:
    QLabel *licenseLabel;
    QFrame *frame;
    QLabel *license;
    QLabel *descriptionLabel;
    QLabel *description;
    QLabel *titleLabel;
    QLabel *title;
    QLabel *versionLabel;
    QLabel *version;
    QLabel *copy;

    void setupUi(QDialog *aboutDialog)
    {
        if (aboutDialog->objectName().isEmpty())
            aboutDialog->setObjectName(QString::fromUtf8("aboutDialog"));
        aboutDialog->setWindowModality(Qt::NonModal);
        aboutDialog->resize(492, 200);
        licenseLabel = new QLabel(aboutDialog);
        licenseLabel->setObjectName(QString::fromUtf8("licenseLabel"));
        licenseLabel->setGeometry(QRect(400, 10, 41, 16));
        frame = new QFrame(aboutDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 200, 200));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        license = new QLabel(aboutDialog);
        license->setObjectName(QString::fromUtf8("license"));
        license->setGeometry(QRect(420, 30, 51, 16));
        descriptionLabel = new QLabel(aboutDialog);
        descriptionLabel->setObjectName(QString::fromUtf8("descriptionLabel"));
        descriptionLabel->setGeometry(QRect(200, 60, 71, 16));
        description = new QLabel(aboutDialog);
        description->setObjectName(QString::fromUtf8("description"));
        description->setGeometry(QRect(220, 80, 271, 41));
        description->setWordWrap(true);
        titleLabel = new QLabel(aboutDialog);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(200, 10, 41, 16));
        title = new QLabel(aboutDialog);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(220, 30, 81, 16));
        versionLabel = new QLabel(aboutDialog);
        versionLabel->setObjectName(QString::fromUtf8("versionLabel"));
        versionLabel->setGeometry(QRect(310, 10, 41, 16));
        version = new QLabel(aboutDialog);
        version->setObjectName(QString::fromUtf8("version"));
        version->setGeometry(QRect(330, 30, 21, 16));
        copy = new QLabel(aboutDialog);
        copy->setObjectName(QString::fromUtf8("copy"));
        copy->setGeometry(QRect(260, 170, 161, 20));

        retranslateUi(aboutDialog);

        QMetaObject::connectSlotsByName(aboutDialog);
    } // setupUi

    void retranslateUi(QDialog *aboutDialog)
    {
        aboutDialog->setWindowTitle(QApplication::translate("aboutDialog", "About", 0, QApplication::UnicodeUTF8));
        licenseLabel->setText(QApplication::translate("aboutDialog", "<b>License</b>", 0, QApplication::UnicodeUTF8));
        license->setText(QApplication::translate("aboutDialog", "Freeware", 0, QApplication::UnicodeUTF8));
        descriptionLabel->setText(QApplication::translate("aboutDialog", "<b>Description</b>", 0, QApplication::UnicodeUTF8));
        description->setText(QApplication::translate("aboutDialog", "The program provides utilities in working with systems. It is possible to automate whole work with scheduled tasks.", 0, QApplication::UnicodeUTF8));
        titleLabel->setText(QApplication::translate("aboutDialog", "<b>Title</b>", 0, QApplication::UnicodeUTF8));
        title->setText(QApplication::translate("aboutDialog", "DoForMe!", 0, QApplication::UnicodeUTF8));
        versionLabel->setText(QApplication::translate("aboutDialog", "<b>Version</b>", 0, QApplication::UnicodeUTF8));
        version->setText(QApplication::translate("aboutDialog", "1.0", 0, QApplication::UnicodeUTF8));
        copy->setText(QApplication::translate("aboutDialog", "Copyrights \302\251 by Jacek Topolski", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class aboutDialog: public Ui_aboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
