/********************************************************************************
** Form generated from reading UI file 'mainwin.ui'
**
** Created: Wed 18. Jul 07:49:37 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIN_H
#define UI_MAINWIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCalendarWidget>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainWinClass
{
public:
    QAction *actionAbout;
    QAction *actionExlude_commands;
    QAction *actionMouse;
    QAction *actionKeyboard;
    QAction *actionCalendar_colours;
    QAction *actionNew_action;
    QAction *actionScript_code;
    QAction *actionRecording;
    QAction *actionTiming;
    QAction *actionRepeating;
    QAction *actionReminding;
    QAction *actionRun_current_action;
    QAction *actionSave_action;
    QWidget *centralWidget;
    QCalendarWidget *calendarWidget;
    QGroupBox *actionsGroupBox;
    QListWidget *actionsList;
    QPushButton *removeButton;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QTextEdit *scriptTextEdit;
    QPushButton *runButton;
    QPushButton *browseScriptButton;
    QLineEdit *scriptPathEdit;
    QLabel *label_5;
    QLabel *label_7;
    QPushButton *externalWindowButton;
    QPushButton *saveButton;
    QPushButton *saveAsButton;
    QWidget *tab_5;
    QPushButton *recordButton;
    QGroupBox *groupBox_3;
    QPushButton *mouseButton;
    QPushButton *keyboardButton;
    QCheckBox *keyboardCheck;
    QCheckBox *mouseCheck;
    QGroupBox *groupBox_4;
    QCheckBox *actionWindowCheck;
    QGroupBox *groupBox_6;
    QWidget *positionWidget;
    QRadioButton *leftRadio;
    QRadioButton *middleLeftRadio;
    QRadioButton *rightRadio;
    QRadioButton *downRadio;
    QRadioButton *topRadio;
    QRadioButton *middleRightRadio;
    QFrame *frame;
    QGroupBox *groupBox_13;
    QSlider *transparencySlider;
    QGroupBox *groupBox_7;
    QCheckBox *trayCheck;
    QWidget *tab_3;
    QGroupBox *groupBox;
    QCheckBox *mondayCheck;
    QCheckBox *tuesdayCheck;
    QCheckBox *wednesdayCheck;
    QCheckBox *thursdayCheck;
    QCheckBox *fridayCheck;
    QCheckBox *saturdayCheck;
    QCheckBox *sundayCheck;
    QCheckBox *everydayCheck;
    QGroupBox *groupBox_8;
    QRadioButton *runEveryDaysRadio;
    QLineEdit *daysEdit;
    QLabel *label_4;
    QGroupBox *groupBox_9;
    QCheckBox *showOnCalendarCheck;
    QGroupBox *timeGroupBox;
    QSpinBox *hourSpin;
    QSpinBox *minSpin;
    QSpinBox *secSpin;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupBox_2;
    QSpinBox *intervalSpin;
    QRadioButton *msRadio;
    QRadioButton *secRadio;
    QRadioButton *minRadio;
    QWidget *tab_4;
    QGroupBox *groupBox_10;
    QCheckBox *signalCheck;
    QLineEdit *signalEdit;
    QLabel *label_8;
    QGroupBox *groupBox_11;
    QCheckBox *msgCheck;
    QGroupBox *groupBox_12;
    QCheckBox *soundCheck;
    QPushButton *browseSoundButton;
    QLineEdit *soundPathEdit;
    QPushButton *playSoundButton;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QMenu *menuExecuting;
    QMenu *menuCustomize;
    QMenu *menuActions;
    QMenu *menuView;

    void setupUi(QMainWindow *mainWinClass)
    {
        if (mainWinClass->objectName().isEmpty())
            mainWinClass->setObjectName(QString::fromUtf8("mainWinClass"));
        mainWinClass->resize(700, 480);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/mainWin/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        mainWinClass->setWindowIcon(icon);
        mainWinClass->setDocumentMode(false);
        mainWinClass->setTabShape(QTabWidget::Rounded);
        actionAbout = new QAction(mainWinClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionExlude_commands = new QAction(mainWinClass);
        actionExlude_commands->setObjectName(QString::fromUtf8("actionExlude_commands"));
        actionMouse = new QAction(mainWinClass);
        actionMouse->setObjectName(QString::fromUtf8("actionMouse"));
        actionKeyboard = new QAction(mainWinClass);
        actionKeyboard->setObjectName(QString::fromUtf8("actionKeyboard"));
        actionCalendar_colours = new QAction(mainWinClass);
        actionCalendar_colours->setObjectName(QString::fromUtf8("actionCalendar_colours"));
        actionNew_action = new QAction(mainWinClass);
        actionNew_action->setObjectName(QString::fromUtf8("actionNew_action"));
        actionScript_code = new QAction(mainWinClass);
        actionScript_code->setObjectName(QString::fromUtf8("actionScript_code"));
        actionScript_code->setCheckable(true);
        actionRecording = new QAction(mainWinClass);
        actionRecording->setObjectName(QString::fromUtf8("actionRecording"));
        actionRecording->setCheckable(true);
        actionTiming = new QAction(mainWinClass);
        actionTiming->setObjectName(QString::fromUtf8("actionTiming"));
        actionTiming->setCheckable(true);
        actionRepeating = new QAction(mainWinClass);
        actionRepeating->setObjectName(QString::fromUtf8("actionRepeating"));
        actionRepeating->setCheckable(true);
        actionReminding = new QAction(mainWinClass);
        actionReminding->setObjectName(QString::fromUtf8("actionReminding"));
        actionReminding->setCheckable(true);
        actionRun_current_action = new QAction(mainWinClass);
        actionRun_current_action->setObjectName(QString::fromUtf8("actionRun_current_action"));
        actionSave_action = new QAction(mainWinClass);
        actionSave_action->setObjectName(QString::fromUtf8("actionSave_action"));
        centralWidget = new QWidget(mainWinClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        calendarWidget = new QCalendarWidget(centralWidget);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        calendarWidget->setGeometry(QRect(0, 250, 700, 211));
        calendarWidget->setGridVisible(true);
        actionsGroupBox = new QGroupBox(centralWidget);
        actionsGroupBox->setObjectName(QString::fromUtf8("actionsGroupBox"));
        actionsGroupBox->setGeometry(QRect(10, 10, 171, 231));
        actionsList = new QListWidget(actionsGroupBox);
        QFont font;
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStyleStrategy(QFont::PreferDefault);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(actionsList);
        __qlistwidgetitem->setFont(font);
        new QListWidgetItem(actionsList);
        actionsList->setObjectName(QString::fromUtf8("actionsList"));
        actionsList->setGeometry(QRect(10, 20, 151, 171));
        actionsList->setStyleSheet(QString::fromUtf8("QListWidget::item::selected {\n"
"	background-color: rgb( 51, 153, 255 );\n"
"}"));
        actionsList->setFrameShadow(QFrame::Sunken);
        actionsList->setLineWidth(1);
        actionsList->setMovement(QListView::Static);
        actionsList->setFlow(QListView::TopToBottom);
        actionsList->setProperty("isWrapping", QVariant(false));
        actionsList->setResizeMode(QListView::Fixed);
        actionsList->setLayoutMode(QListView::SinglePass);
        actionsList->setSpacing(0);
        actionsList->setViewMode(QListView::ListMode);
        actionsList->setSelectionRectVisible(false);
        actionsList->setSortingEnabled(true);
        removeButton = new QPushButton(actionsGroupBox);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setGeometry(QRect(10, 200, 151, 20));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(190, 10, 501, 231));
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        scriptTextEdit = new QTextEdit(tab_2);
        scriptTextEdit->setObjectName(QString::fromUtf8("scriptTextEdit"));
        scriptTextEdit->setGeometry(QRect(10, 80, 471, 91));
        scriptTextEdit->setFrameShape(QFrame::StyledPanel);
        scriptTextEdit->setFrameShadow(QFrame::Sunken);
        scriptTextEdit->setLineWidth(1);
        scriptTextEdit->setMidLineWidth(0);
        runButton = new QPushButton(tab_2);
        runButton->setObjectName(QString::fromUtf8("runButton"));
        runButton->setGeometry(QRect(10, 178, 91, 20));
        browseScriptButton = new QPushButton(tab_2);
        browseScriptButton->setObjectName(QString::fromUtf8("browseScriptButton"));
        browseScriptButton->setGeometry(QRect(10, 30, 75, 20));
        scriptPathEdit = new QLineEdit(tab_2);
        scriptPathEdit->setObjectName(QString::fromUtf8("scriptPathEdit"));
        scriptPathEdit->setEnabled(true);
        scriptPathEdit->setGeometry(QRect(90, 30, 391, 20));
        scriptPathEdit->setReadOnly(true);
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 10, 111, 16));
        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 60, 111, 16));
        externalWindowButton = new QPushButton(tab_2);
        externalWindowButton->setObjectName(QString::fromUtf8("externalWindowButton"));
        externalWindowButton->setGeometry(QRect(350, 177, 131, 20));
        saveButton = new QPushButton(tab_2);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(110, 178, 91, 20));
        saveAsButton = new QPushButton(tab_2);
        saveAsButton->setObjectName(QString::fromUtf8("saveAsButton"));
        saveAsButton->setGeometry(QRect(210, 178, 91, 20));
        tabWidget->addTab(tab_2, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        recordButton = new QPushButton(tab_5);
        recordButton->setObjectName(QString::fromUtf8("recordButton"));
        recordButton->setGeometry(QRect(10, 10, 211, 20));
        groupBox_3 = new QGroupBox(tab_5);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 40, 211, 71));
        mouseButton = new QPushButton(groupBox_3);
        mouseButton->setObjectName(QString::fromUtf8("mouseButton"));
        mouseButton->setGeometry(QRect(90, 20, 111, 20));
        keyboardButton = new QPushButton(groupBox_3);
        keyboardButton->setObjectName(QString::fromUtf8("keyboardButton"));
        keyboardButton->setGeometry(QRect(90, 40, 111, 20));
        keyboardCheck = new QCheckBox(groupBox_3);
        keyboardCheck->setObjectName(QString::fromUtf8("keyboardCheck"));
        keyboardCheck->setGeometry(QRect(10, 40, 70, 17));
        mouseCheck = new QCheckBox(groupBox_3);
        mouseCheck->setObjectName(QString::fromUtf8("mouseCheck"));
        mouseCheck->setGeometry(QRect(10, 20, 70, 17));
        groupBox_4 = new QGroupBox(tab_5);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(230, 10, 251, 191));
        actionWindowCheck = new QCheckBox(groupBox_4);
        actionWindowCheck->setObjectName(QString::fromUtf8("actionWindowCheck"));
        actionWindowCheck->setGeometry(QRect(10, 20, 41, 17));
        groupBox_6 = new QGroupBox(groupBox_4);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(10, 78, 231, 101));
        positionWidget = new QWidget(groupBox_6);
        positionWidget->setObjectName(QString::fromUtf8("positionWidget"));
        positionWidget->setGeometry(QRect(10, 20, 70, 70));
        positionWidget->setStyleSheet(QString::fromUtf8("QWidget {\n"
"	border: 1px solid black;\n"
"	background-color: white;\n"
"}"));
        leftRadio = new QRadioButton(groupBox_6);
        leftRadio->setObjectName(QString::fromUtf8("leftRadio"));
        leftRadio->setGeometry(QRect(100, 20, 41, 17));
        middleLeftRadio = new QRadioButton(groupBox_6);
        middleLeftRadio->setObjectName(QString::fromUtf8("middleLeftRadio"));
        middleLeftRadio->setGeometry(QRect(100, 45, 61, 17));
        rightRadio = new QRadioButton(groupBox_6);
        rightRadio->setObjectName(QString::fromUtf8("rightRadio"));
        rightRadio->setGeometry(QRect(100, 70, 61, 17));
        downRadio = new QRadioButton(groupBox_6);
        downRadio->setObjectName(QString::fromUtf8("downRadio"));
        downRadio->setGeometry(QRect(170, 70, 61, 17));
        topRadio = new QRadioButton(groupBox_6);
        topRadio->setObjectName(QString::fromUtf8("topRadio"));
        topRadio->setGeometry(QRect(170, 20, 41, 17));
        middleRightRadio = new QRadioButton(groupBox_6);
        middleRightRadio->setObjectName(QString::fromUtf8("middleRightRadio"));
        middleRightRadio->setGeometry(QRect(170, 45, 61, 17));
        frame = new QFrame(groupBox_6);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(80, 19, 20, 71));
        frame->setFrameShape(QFrame::VLine);
        frame->setFrameShadow(QFrame::Raised);
        groupBox_13 = new QGroupBox(groupBox_4);
        groupBox_13->setObjectName(QString::fromUtf8("groupBox_13"));
        groupBox_13->setGeometry(QRect(60, 20, 181, 51));
        transparencySlider = new QSlider(groupBox_13);
        transparencySlider->setObjectName(QString::fromUtf8("transparencySlider"));
        transparencySlider->setGeometry(QRect(10, 20, 211, 20));
        transparencySlider->setOrientation(Qt::Horizontal);
        transparencySlider->setTickPosition(QSlider::NoTicks);
        groupBox_7 = new QGroupBox(tab_5);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(10, 120, 211, 61));
        trayCheck = new QCheckBox(groupBox_7);
        trayCheck->setObjectName(QString::fromUtf8("trayCheck"));
        trayCheck->setGeometry(QRect(10, 20, 191, 31));
        trayCheck->setTristate(false);
        tabWidget->addTab(tab_5, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        groupBox = new QGroupBox(tab_3);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(380, 0, 101, 191));
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
        groupBox_8 = new QGroupBox(tab_3);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(10, 10, 361, 51));
        runEveryDaysRadio = new QRadioButton(groupBox_8);
        runEveryDaysRadio->setObjectName(QString::fromUtf8("runEveryDaysRadio"));
        runEveryDaysRadio->setGeometry(QRect(10, 20, 101, 17));
        daysEdit = new QLineEdit(groupBox_8);
        daysEdit->setObjectName(QString::fromUtf8("daysEdit"));
        daysEdit->setGeometry(QRect(113, 20, 41, 20));
        label_4 = new QLabel(groupBox_8);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(160, 23, 46, 13));
        groupBox_9 = new QGroupBox(tab_3);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setGeometry(QRect(180, 70, 191, 51));
        showOnCalendarCheck = new QCheckBox(groupBox_9);
        showOnCalendarCheck->setObjectName(QString::fromUtf8("showOnCalendarCheck"));
        showOnCalendarCheck->setGeometry(QRect(10, 15, 151, 31));
        timeGroupBox = new QGroupBox(tab_3);
        timeGroupBox->setObjectName(QString::fromUtf8("timeGroupBox"));
        timeGroupBox->setGeometry(QRect(10, 70, 161, 51));
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
        groupBox_2 = new QGroupBox(tab_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 130, 361, 51));
        intervalSpin = new QSpinBox(groupBox_2);
        intervalSpin->setObjectName(QString::fromUtf8("intervalSpin"));
        intervalSpin->setGeometry(QRect(10, 20, 111, 21));
        intervalSpin->setMaximum(24);
        msRadio = new QRadioButton(groupBox_2);
        msRadio->setObjectName(QString::fromUtf8("msRadio"));
        msRadio->setGeometry(QRect(130, 20, 41, 17));
        secRadio = new QRadioButton(groupBox_2);
        secRadio->setObjectName(QString::fromUtf8("secRadio"));
        secRadio->setGeometry(QRect(190, 20, 41, 17));
        minRadio = new QRadioButton(groupBox_2);
        minRadio->setObjectName(QString::fromUtf8("minRadio"));
        minRadio->setGeometry(QRect(250, 20, 41, 17));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        groupBox_10 = new QGroupBox(tab_4);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        groupBox_10->setGeometry(QRect(10, 10, 471, 51));
        signalCheck = new QCheckBox(groupBox_10);
        signalCheck->setObjectName(QString::fromUtf8("signalCheck"));
        signalCheck->setGeometry(QRect(10, 20, 81, 17));
        signalEdit = new QLineEdit(groupBox_10);
        signalEdit->setObjectName(QString::fromUtf8("signalEdit"));
        signalEdit->setGeometry(QRect(92, 20, 41, 20));
        label_8 = new QLabel(groupBox_10);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(139, 21, 131, 16));
        groupBox_11 = new QGroupBox(tab_4);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        groupBox_11->setGeometry(QRect(10, 70, 81, 51));
        msgCheck = new QCheckBox(groupBox_11);
        msgCheck->setObjectName(QString::fromUtf8("msgCheck"));
        msgCheck->setGeometry(QRect(10, 20, 41, 17));
        groupBox_12 = new QGroupBox(tab_4);
        groupBox_12->setObjectName(QString::fromUtf8("groupBox_12"));
        groupBox_12->setGeometry(QRect(100, 70, 381, 51));
        soundCheck = new QCheckBox(groupBox_12);
        soundCheck->setObjectName(QString::fromUtf8("soundCheck"));
        soundCheck->setGeometry(QRect(10, 20, 41, 17));
        browseSoundButton = new QPushButton(groupBox_12);
        browseSoundButton->setObjectName(QString::fromUtf8("browseSoundButton"));
        browseSoundButton->setGeometry(QRect(50, 19, 75, 20));
        soundPathEdit = new QLineEdit(groupBox_12);
        soundPathEdit->setObjectName(QString::fromUtf8("soundPathEdit"));
        soundPathEdit->setEnabled(true);
        soundPathEdit->setGeometry(QRect(130, 19, 211, 20));
        soundPathEdit->setReadOnly(true);
        playSoundButton = new QPushButton(groupBox_12);
        playSoundButton->setObjectName(QString::fromUtf8("playSoundButton"));
        playSoundButton->setGeometry(QRect(343, 17, 31, 23));
        tabWidget->addTab(tab_4, QString());
        mainWinClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(mainWinClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 700, 21));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        menuExecuting = new QMenu(menuBar);
        menuExecuting->setObjectName(QString::fromUtf8("menuExecuting"));
        menuCustomize = new QMenu(menuBar);
        menuCustomize->setObjectName(QString::fromUtf8("menuCustomize"));
        menuActions = new QMenu(menuBar);
        menuActions->setObjectName(QString::fromUtf8("menuActions"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        mainWinClass->setMenuBar(menuBar);

        menuBar->addAction(menuActions->menuAction());
        menuBar->addAction(menuExecuting->menuAction());
        menuBar->addAction(menuCustomize->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionAbout);
        menuExecuting->addAction(actionExlude_commands);
        menuCustomize->addAction(actionCalendar_colours);
        menuActions->addAction(actionNew_action);
        menuActions->addSeparator();
        menuActions->addAction(actionRun_current_action);
        menuActions->addAction(actionSave_action);
        menuView->addAction(actionScript_code);
        menuView->addAction(actionRecording);
        menuView->addAction(actionTiming);
        menuView->addAction(actionRepeating);
        menuView->addAction(actionReminding);

        retranslateUi(mainWinClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(mainWinClass);
    } // setupUi

    void retranslateUi(QMainWindow *mainWinClass)
    {
        mainWinClass->setWindowTitle(QApplication::translate("mainWinClass", "DoForMe!", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("mainWinClass", "About...", 0, QApplication::UnicodeUTF8));
        actionExlude_commands->setText(QApplication::translate("mainWinClass", "Exclude...", 0, QApplication::UnicodeUTF8));
        actionMouse->setText(QApplication::translate("mainWinClass", "Mouse...", 0, QApplication::UnicodeUTF8));
        actionKeyboard->setText(QApplication::translate("mainWinClass", "Keyboard...", 0, QApplication::UnicodeUTF8));
        actionCalendar_colours->setText(QApplication::translate("mainWinClass", "Calendar colors...", 0, QApplication::UnicodeUTF8));
        actionNew_action->setText(QApplication::translate("mainWinClass", "New action...", 0, QApplication::UnicodeUTF8));
        actionScript_code->setText(QApplication::translate("mainWinClass", "Script code", 0, QApplication::UnicodeUTF8));
        actionRecording->setText(QApplication::translate("mainWinClass", "Recording", 0, QApplication::UnicodeUTF8));
        actionTiming->setText(QApplication::translate("mainWinClass", "Timing", 0, QApplication::UnicodeUTF8));
        actionRepeating->setText(QApplication::translate("mainWinClass", "Repeating", 0, QApplication::UnicodeUTF8));
        actionReminding->setText(QApplication::translate("mainWinClass", "Reminding", 0, QApplication::UnicodeUTF8));
        actionRun_current_action->setText(QApplication::translate("mainWinClass", "Run current action...", 0, QApplication::UnicodeUTF8));
        actionSave_action->setText(QApplication::translate("mainWinClass", "Save action...", 0, QApplication::UnicodeUTF8));
        actionsGroupBox->setTitle(QApplication::translate("mainWinClass", "Actions for 30.06.2012", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = actionsList->isSortingEnabled();
        actionsList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = actionsList->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("mainWinClass", "13:50:00 - asd", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem1 = actionsList->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("mainWinClass", "13:52:00 - zxc", 0, QApplication::UnicodeUTF8));
        actionsList->setSortingEnabled(__sortingEnabled);

        removeButton->setText(QApplication::translate("mainWinClass", "Remove", 0, QApplication::UnicodeUTF8));
        scriptTextEdit->setHtml(QApplication::translate("mainWinClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:8pt;\">sendText( &quot;asdzxc&quot; )</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        runButton->setText(QApplication::translate("mainWinClass", "Run", 0, QApplication::UnicodeUTF8));
        browseScriptButton->setText(QApplication::translate("mainWinClass", "Browse...", 0, QApplication::UnicodeUTF8));
        scriptPathEdit->setText(QApplication::translate("mainWinClass", "D:\\dupa.apc", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("mainWinClass", "Load script from file:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("mainWinClass", "or write the script:", 0, QApplication::UnicodeUTF8));
        externalWindowButton->setText(QApplication::translate("mainWinClass", "Show in external editor", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("mainWinClass", "Save script", 0, QApplication::UnicodeUTF8));
        saveAsButton->setText(QApplication::translate("mainWinClass", "Save script as...", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("mainWinClass", "Script code", 0, QApplication::UnicodeUTF8));
        recordButton->setText(QApplication::translate("mainWinClass", "Start recording", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("mainWinClass", "Record", 0, QApplication::UnicodeUTF8));
        mouseButton->setText(QApplication::translate("mainWinClass", "Keys to record", 0, QApplication::UnicodeUTF8));
        keyboardButton->setText(QApplication::translate("mainWinClass", "Keys to record", 0, QApplication::UnicodeUTF8));
        keyboardCheck->setText(QApplication::translate("mainWinClass", "Keyboard", 0, QApplication::UnicodeUTF8));
        mouseCheck->setText(QApplication::translate("mainWinClass", "Mouse", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("mainWinClass", "Recording window", 0, QApplication::UnicodeUTF8));
        actionWindowCheck->setText(QApplication::translate("mainWinClass", "On", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("mainWinClass", "Positioning", 0, QApplication::UnicodeUTF8));
        leftRadio->setText(QApplication::translate("mainWinClass", "Left", 0, QApplication::UnicodeUTF8));
        middleLeftRadio->setText(QApplication::translate("mainWinClass", "Middle", 0, QApplication::UnicodeUTF8));
        rightRadio->setText(QApplication::translate("mainWinClass", "Right", 0, QApplication::UnicodeUTF8));
        downRadio->setText(QApplication::translate("mainWinClass", "Down", 0, QApplication::UnicodeUTF8));
        topRadio->setText(QApplication::translate("mainWinClass", "Top", 0, QApplication::UnicodeUTF8));
        middleRightRadio->setText(QApplication::translate("mainWinClass", "Middle", 0, QApplication::UnicodeUTF8));
        groupBox_13->setTitle(QApplication::translate("mainWinClass", "Transparency", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("mainWinClass", "Tray", 0, QApplication::UnicodeUTF8));
        trayCheck->setText(QApplication::translate("mainWinClass", "Hide program into tray while\n"
"recording.", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("mainWinClass", "Recording", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("mainWinClass", "Run on", 0, QApplication::UnicodeUTF8));
        mondayCheck->setText(QApplication::translate("mainWinClass", "Monday", 0, QApplication::UnicodeUTF8));
        tuesdayCheck->setText(QApplication::translate("mainWinClass", "Tuesday", 0, QApplication::UnicodeUTF8));
        wednesdayCheck->setText(QApplication::translate("mainWinClass", "Wednesday", 0, QApplication::UnicodeUTF8));
        thursdayCheck->setText(QApplication::translate("mainWinClass", "Thursday", 0, QApplication::UnicodeUTF8));
        fridayCheck->setText(QApplication::translate("mainWinClass", "Friday", 0, QApplication::UnicodeUTF8));
        saturdayCheck->setText(QApplication::translate("mainWinClass", "Saturday", 0, QApplication::UnicodeUTF8));
        sundayCheck->setText(QApplication::translate("mainWinClass", "Sunday", 0, QApplication::UnicodeUTF8));
        everydayCheck->setText(QApplication::translate("mainWinClass", "Every day", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("mainWinClass", "Every X days", 0, QApplication::UnicodeUTF8));
        runEveryDaysRadio->setText(QApplication::translate("mainWinClass", "Run script every", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("mainWinClass", "days.", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QApplication::translate("mainWinClass", "Calendar", 0, QApplication::UnicodeUTF8));
        showOnCalendarCheck->setText(QApplication::translate("mainWinClass", "Show repeated actions on\n"
"calendar.", 0, QApplication::UnicodeUTF8));
        timeGroupBox->setTitle(QApplication::translate("mainWinClass", "Time settings", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("mainWinClass", ":", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("mainWinClass", ":", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("mainWinClass", "Commands time interval", 0, QApplication::UnicodeUTF8));
        msRadio->setText(QApplication::translate("mainWinClass", "ms", 0, QApplication::UnicodeUTF8));
        secRadio->setText(QApplication::translate("mainWinClass", "sec", 0, QApplication::UnicodeUTF8));
        minRadio->setText(QApplication::translate("mainWinClass", "min", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("mainWinClass", "Timing/Repeating", 0, QApplication::UnicodeUTF8));
        groupBox_10->setTitle(QApplication::translate("mainWinClass", "Reminder", 0, QApplication::UnicodeUTF8));
        signalCheck->setText(QApplication::translate("mainWinClass", "Signal action", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("mainWinClass", "minutes before execution.", 0, QApplication::UnicodeUTF8));
        groupBox_11->setTitle(QApplication::translate("mainWinClass", "Message box", 0, QApplication::UnicodeUTF8));
        msgCheck->setText(QApplication::translate("mainWinClass", "On", 0, QApplication::UnicodeUTF8));
        groupBox_12->setTitle(QApplication::translate("mainWinClass", "Sound", 0, QApplication::UnicodeUTF8));
        soundCheck->setText(QApplication::translate("mainWinClass", "On", 0, QApplication::UnicodeUTF8));
        browseSoundButton->setText(QApplication::translate("mainWinClass", "Browse...", 0, QApplication::UnicodeUTF8));
        soundPathEdit->setText(QApplication::translate("mainWinClass", "D:\\dupa.apc", 0, QApplication::UnicodeUTF8));
        playSoundButton->setText(QApplication::translate("mainWinClass", "Play", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("mainWinClass", "Reminding", 0, QApplication::UnicodeUTF8));
        menuMenu->setTitle(QApplication::translate("mainWinClass", "Help", 0, QApplication::UnicodeUTF8));
        menuExecuting->setTitle(QApplication::translate("mainWinClass", "Commands", 0, QApplication::UnicodeUTF8));
        menuCustomize->setTitle(QApplication::translate("mainWinClass", "Customize", 0, QApplication::UnicodeUTF8));
        menuActions->setTitle(QApplication::translate("mainWinClass", "Action", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("mainWinClass", "View", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainWinClass: public Ui_mainWinClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIN_H
