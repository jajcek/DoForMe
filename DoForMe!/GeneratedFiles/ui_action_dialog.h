/********************************************************************************
** Form generated from reading UI file 'action_dialog.ui'
**
** Created: Mon 13. Aug 19:08:37 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACTION_DIALOG_H
#define UI_ACTION_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_actionSettingsDialog
{
public:
    QGroupBox *groupBox_8;
    QCheckBox *runEveryXDaysCheck;
    QLabel *label_4;
    QSpinBox *daysSpin;
    QGroupBox *timeGroupBox;
    QSpinBox *hourSpin;
    QSpinBox *minSpin;
    QSpinBox *secSpin;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupBox;
    QCheckBox *mondayCheck;
    QCheckBox *tuesdayCheck;
    QCheckBox *wednesdayCheck;
    QCheckBox *thursdayCheck;
    QCheckBox *fridayCheck;
    QCheckBox *saturdayCheck;
    QCheckBox *sundayCheck;
    QCheckBox *everydayCheck;
    QPushButton *applyButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *actionSettingsDialog)
    {
        if (actionSettingsDialog->objectName().isEmpty())
            actionSettingsDialog->setObjectName(QString::fromUtf8("actionSettingsDialog"));
        actionSettingsDialog->resize(331, 201);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/mainWin/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSettingsDialog->setWindowIcon(icon);
        groupBox_8 = new QGroupBox(actionSettingsDialog);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(10, 70, 201, 51));
        runEveryXDaysCheck = new QCheckBox(groupBox_8);
        runEveryXDaysCheck->setObjectName(QString::fromUtf8("runEveryXDaysCheck"));
        runEveryXDaysCheck->setGeometry(QRect(10, 22, 101, 17));
        label_4 = new QLabel(groupBox_8);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(160, 25, 31, 16));
        daysSpin = new QSpinBox(groupBox_8);
        daysSpin->setObjectName(QString::fromUtf8("daysSpin"));
        daysSpin->setEnabled(false);
        daysSpin->setGeometry(QRect(112, 20, 42, 22));
        daysSpin->setMinimum(1);
        daysSpin->setMaximum(999);
        timeGroupBox = new QGroupBox(actionSettingsDialog);
        timeGroupBox->setObjectName(QString::fromUtf8("timeGroupBox"));
        timeGroupBox->setGeometry(QRect(10, 10, 201, 51));
        hourSpin = new QSpinBox(timeGroupBox);
        hourSpin->setObjectName(QString::fromUtf8("hourSpin"));
        hourSpin->setGeometry(QRect(10, 20, 42, 22));
        hourSpin->setMaximum(23);
        minSpin = new QSpinBox(timeGroupBox);
        minSpin->setObjectName(QString::fromUtf8("minSpin"));
        minSpin->setGeometry(QRect(60, 20, 42, 22));
        minSpin->setMaximum(59);
        secSpin = new QSpinBox(timeGroupBox);
        secSpin->setObjectName(QString::fromUtf8("secSpin"));
        secSpin->setGeometry(QRect(110, 20, 42, 22));
        secSpin->setMaximum(59);
        label = new QLabel(timeGroupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(54, 22, 3, 16));
        label_2 = new QLabel(timeGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(105, 22, 2, 16));
        groupBox = new QGroupBox(actionSettingsDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(220, 10, 101, 181));
        mondayCheck = new QCheckBox(groupBox);
        mondayCheck->setObjectName(QString::fromUtf8("mondayCheck"));
        mondayCheck->setGeometry(QRect(10, 20, 71, 17));
        tuesdayCheck = new QCheckBox(groupBox);
        tuesdayCheck->setObjectName(QString::fromUtf8("tuesdayCheck"));
        tuesdayCheck->setGeometry(QRect(10, 40, 71, 17));
        wednesdayCheck = new QCheckBox(groupBox);
        wednesdayCheck->setObjectName(QString::fromUtf8("wednesdayCheck"));
        wednesdayCheck->setGeometry(QRect(10, 60, 81, 17));
        thursdayCheck = new QCheckBox(groupBox);
        thursdayCheck->setObjectName(QString::fromUtf8("thursdayCheck"));
        thursdayCheck->setGeometry(QRect(10, 80, 71, 17));
        fridayCheck = new QCheckBox(groupBox);
        fridayCheck->setObjectName(QString::fromUtf8("fridayCheck"));
        fridayCheck->setGeometry(QRect(10, 100, 71, 17));
        saturdayCheck = new QCheckBox(groupBox);
        saturdayCheck->setObjectName(QString::fromUtf8("saturdayCheck"));
        saturdayCheck->setGeometry(QRect(10, 120, 71, 17));
        sundayCheck = new QCheckBox(groupBox);
        sundayCheck->setObjectName(QString::fromUtf8("sundayCheck"));
        sundayCheck->setGeometry(QRect(10, 140, 71, 17));
        everydayCheck = new QCheckBox(groupBox);
        everydayCheck->setObjectName(QString::fromUtf8("everydayCheck"));
        everydayCheck->setGeometry(QRect(10, 160, 111, 17));
        applyButton = new QPushButton(actionSettingsDialog);
        applyButton->setObjectName(QString::fromUtf8("applyButton"));
        applyButton->setGeometry(QRect(10, 160, 75, 23));
        cancelButton = new QPushButton(actionSettingsDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(90, 160, 75, 23));

        retranslateUi(actionSettingsDialog);
        QObject::connect(cancelButton, SIGNAL(clicked()), actionSettingsDialog, SLOT(reject()));
        QObject::connect(runEveryXDaysCheck, SIGNAL(toggled(bool)), daysSpin, SLOT(setEnabled(bool)));
        QObject::connect(everydayCheck, SIGNAL(toggled(bool)), mondayCheck, SLOT(toggle()));
        QObject::connect(everydayCheck, SIGNAL(toggled(bool)), tuesdayCheck, SLOT(toggle()));
        QObject::connect(everydayCheck, SIGNAL(toggled(bool)), wednesdayCheck, SLOT(toggle()));
        QObject::connect(everydayCheck, SIGNAL(toggled(bool)), thursdayCheck, SLOT(toggle()));
        QObject::connect(everydayCheck, SIGNAL(toggled(bool)), fridayCheck, SLOT(toggle()));
        QObject::connect(everydayCheck, SIGNAL(toggled(bool)), saturdayCheck, SLOT(toggle()));
        QObject::connect(everydayCheck, SIGNAL(toggled(bool)), sundayCheck, SLOT(toggle()));

        QMetaObject::connectSlotsByName(actionSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *actionSettingsDialog)
    {
        actionSettingsDialog->setWindowTitle(QApplication::translate("actionSettingsDialog", "Action settings", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("actionSettingsDialog", "Every X days", 0, QApplication::UnicodeUTF8));
        runEveryXDaysCheck->setText(QApplication::translate("actionSettingsDialog", "Run script every", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("actionSettingsDialog", "days.", 0, QApplication::UnicodeUTF8));
        timeGroupBox->setTitle(QApplication::translate("actionSettingsDialog", "Time settings", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("actionSettingsDialog", ":", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("actionSettingsDialog", ":", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("actionSettingsDialog", "Run on", 0, QApplication::UnicodeUTF8));
        mondayCheck->setText(QApplication::translate("actionSettingsDialog", "Monday", 0, QApplication::UnicodeUTF8));
        tuesdayCheck->setText(QApplication::translate("actionSettingsDialog", "Tuesday", 0, QApplication::UnicodeUTF8));
        wednesdayCheck->setText(QApplication::translate("actionSettingsDialog", "Wednesday", 0, QApplication::UnicodeUTF8));
        thursdayCheck->setText(QApplication::translate("actionSettingsDialog", "Thursday", 0, QApplication::UnicodeUTF8));
        fridayCheck->setText(QApplication::translate("actionSettingsDialog", "Friday", 0, QApplication::UnicodeUTF8));
        saturdayCheck->setText(QApplication::translate("actionSettingsDialog", "Saturday", 0, QApplication::UnicodeUTF8));
        sundayCheck->setText(QApplication::translate("actionSettingsDialog", "Sunday", 0, QApplication::UnicodeUTF8));
        everydayCheck->setText(QApplication::translate("actionSettingsDialog", "Every day", 0, QApplication::UnicodeUTF8));
        applyButton->setText(QApplication::translate("actionSettingsDialog", "Apply", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("actionSettingsDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class actionSettingsDialog: public Ui_actionSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACTION_DIALOG_H
