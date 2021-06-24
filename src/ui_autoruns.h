/********************************************************************************
** Form generated from reading UI file 'autoruns.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTORUNS_H
#define UI_AUTORUNS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionRefresh;
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *Logon;
    QTableWidget *LogonTable;
    QWidget *Services;
    QTableWidget *ServicesTable;
    QWidget *Drivers;
    QTableWidget *DriversTable;
    QWidget *Tasks;
    QTableWidget *TasksTable;
    QWidget *KnownDlls;
    QTableWidget *DllsTable;
    QWidget *BootExecute;
    QTableWidget *BootExecuteTable;
    QMenuBar *menuBar;
    QMenu *menuHelp;
    QMenu *menurefresh;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(810, 600);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(810, 600));
        MainWindow->setMaximumSize(QSize(810, 600));
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow{\n"
"padding:0px;\n"
"margin:0px;\n"
"}\n"
"\n"
"QScrollBar{\n"
"	width:5px;\n"
"}\n"
"\n"
"QTabWidget{\n"
"	width:100%;\n"
"}"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout->setCheckable(false);
        actionRefresh = new QAction(MainWindow);
        actionRefresh->setObjectName(QString::fromUtf8("actionRefresh"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setLayoutDirection(Qt::LeftToRight);
        centralwidget->setStyleSheet(QString::fromUtf8("QTableWidget{\n"
"border: 0px;\n"
"\n"
"}"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(-1, 0, 810, 580));
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setStyleSheet(QString::fromUtf8("QTabBar{\n"
"width:100%;\n"
"}\n"
"\n"
"QTabBar::tab{width:100%;}"));
        Logon = new QWidget();
        Logon->setObjectName(QString::fromUtf8("Logon"));
        LogonTable = new QTableWidget(Logon);
        if (LogonTable->columnCount() < 5)
            LogonTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        LogonTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        LogonTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        LogonTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        LogonTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        LogonTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        LogonTable->setObjectName(QString::fromUtf8("LogonTable"));
        LogonTable->setGeometry(QRect(0, 0, 811, 531));
        LogonTable->setStyleSheet(QString::fromUtf8(""));
        LogonTable->setLineWidth(1);
        LogonTable->setAutoScrollMargin(4);
        LogonTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        LogonTable->setSelectionMode(QAbstractItemView::SingleSelection);
        LogonTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        LogonTable->setTextElideMode(Qt::ElideLeft);
        LogonTable->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        LogonTable->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        LogonTable->setWordWrap(true);
        LogonTable->horizontalHeader()->setStretchLastSection(true);
        LogonTable->verticalHeader()->setVisible(false);
        LogonTable->verticalHeader()->setCascadingSectionResizes(false);
        tabWidget->addTab(Logon, QString());
        Services = new QWidget();
        Services->setObjectName(QString::fromUtf8("Services"));
        ServicesTable = new QTableWidget(Services);
        if (ServicesTable->columnCount() < 5)
            ServicesTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        ServicesTable->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        ServicesTable->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        ServicesTable->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        ServicesTable->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        ServicesTable->setHorizontalHeaderItem(4, __qtablewidgetitem9);
        ServicesTable->setObjectName(QString::fromUtf8("ServicesTable"));
        ServicesTable->setGeometry(QRect(0, 0, 811, 550));
        ServicesTable->setLineWidth(1);
        ServicesTable->setEditTriggers(QAbstractItemView::DoubleClicked);
        ServicesTable->setSelectionMode(QAbstractItemView::SingleSelection);
        ServicesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        ServicesTable->setTextElideMode(Qt::ElideLeft);
        ServicesTable->setWordWrap(true);
        ServicesTable->setRowCount(0);
        ServicesTable->horizontalHeader()->setStretchLastSection(true);
        ServicesTable->verticalHeader()->setVisible(false);
        ServicesTable->verticalHeader()->setCascadingSectionResizes(false);
        tabWidget->addTab(Services, QString());
        Drivers = new QWidget();
        Drivers->setObjectName(QString::fromUtf8("Drivers"));
        Drivers->setCursor(QCursor(Qt::OpenHandCursor));
        DriversTable = new QTableWidget(Drivers);
        if (DriversTable->columnCount() < 5)
            DriversTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        DriversTable->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        DriversTable->setHorizontalHeaderItem(1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        DriversTable->setHorizontalHeaderItem(2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        DriversTable->setHorizontalHeaderItem(3, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        DriversTable->setHorizontalHeaderItem(4, __qtablewidgetitem14);
        if (DriversTable->rowCount() < 2)
            DriversTable->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        DriversTable->setVerticalHeaderItem(0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        DriversTable->setVerticalHeaderItem(1, __qtablewidgetitem16);
        DriversTable->setObjectName(QString::fromUtf8("DriversTable"));
        DriversTable->setGeometry(QRect(0, 0, 811, 531));
        DriversTable->setStyleSheet(QString::fromUtf8(""));
        DriversTable->setLineWidth(1);
        DriversTable->setAutoScrollMargin(4);
        DriversTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        DriversTable->setSelectionMode(QAbstractItemView::SingleSelection);
        DriversTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        DriversTable->setTextElideMode(Qt::ElideLeft);
        DriversTable->setWordWrap(true);
        DriversTable->horizontalHeader()->setStretchLastSection(true);
        DriversTable->verticalHeader()->setVisible(false);
        DriversTable->verticalHeader()->setCascadingSectionResizes(false);
        tabWidget->addTab(Drivers, QString());
        Tasks = new QWidget();
        Tasks->setObjectName(QString::fromUtf8("Tasks"));
        TasksTable = new QTableWidget(Tasks);
        if (TasksTable->columnCount() < 5)
            TasksTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        TasksTable->setHorizontalHeaderItem(0, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        TasksTable->setHorizontalHeaderItem(1, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        TasksTable->setHorizontalHeaderItem(2, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        TasksTable->setHorizontalHeaderItem(3, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        TasksTable->setHorizontalHeaderItem(4, __qtablewidgetitem21);
        TasksTable->setObjectName(QString::fromUtf8("TasksTable"));
        TasksTable->setGeometry(QRect(0, 0, 811, 550));
        TasksTable->setStyleSheet(QString::fromUtf8(""));
        TasksTable->setLineWidth(1);
        TasksTable->setAutoScrollMargin(4);
        TasksTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        TasksTable->setSelectionMode(QAbstractItemView::SingleSelection);
        TasksTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        TasksTable->setTextElideMode(Qt::ElideLeft);
        TasksTable->setWordWrap(true);
        TasksTable->horizontalHeader()->setStretchLastSection(true);
        TasksTable->verticalHeader()->setVisible(false);
        TasksTable->verticalHeader()->setCascadingSectionResizes(false);
        tabWidget->addTab(Tasks, QString());
        KnownDlls = new QWidget();
        KnownDlls->setObjectName(QString::fromUtf8("KnownDlls"));
        DllsTable = new QTableWidget(KnownDlls);
        if (DllsTable->columnCount() < 5)
            DllsTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        DllsTable->setHorizontalHeaderItem(0, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        DllsTable->setHorizontalHeaderItem(1, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        DllsTable->setHorizontalHeaderItem(2, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        DllsTable->setHorizontalHeaderItem(3, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        DllsTable->setHorizontalHeaderItem(4, __qtablewidgetitem26);
        DllsTable->setObjectName(QString::fromUtf8("DllsTable"));
        DllsTable->setGeometry(QRect(0, 0, 811, 531));
        DllsTable->setStyleSheet(QString::fromUtf8(""));
        DllsTable->setLineWidth(1);
        DllsTable->setAutoScrollMargin(4);
        DllsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        DllsTable->setSelectionMode(QAbstractItemView::SingleSelection);
        DllsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        DllsTable->setTextElideMode(Qt::ElideLeft);
        DllsTable->setWordWrap(true);
        DllsTable->horizontalHeader()->setStretchLastSection(true);
        DllsTable->verticalHeader()->setVisible(false);
        DllsTable->verticalHeader()->setCascadingSectionResizes(false);
        tabWidget->addTab(KnownDlls, QString());
        BootExecute = new QWidget();
        BootExecute->setObjectName(QString::fromUtf8("BootExecute"));
        BootExecuteTable = new QTableWidget(BootExecute);
        if (BootExecuteTable->columnCount() < 4)
            BootExecuteTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        BootExecuteTable->setHorizontalHeaderItem(0, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        BootExecuteTable->setHorizontalHeaderItem(1, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        BootExecuteTable->setHorizontalHeaderItem(2, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        BootExecuteTable->setHorizontalHeaderItem(3, __qtablewidgetitem30);
        BootExecuteTable->setObjectName(QString::fromUtf8("BootExecuteTable"));
        BootExecuteTable->setEnabled(true);
        BootExecuteTable->setGeometry(QRect(0, 0, 811, 550));
        BootExecuteTable->setStyleSheet(QString::fromUtf8(""));
        BootExecuteTable->setLineWidth(1);
        BootExecuteTable->setAutoScrollMargin(4);
        BootExecuteTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        BootExecuteTable->setSelectionMode(QAbstractItemView::SingleSelection);
        BootExecuteTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        BootExecuteTable->setTextElideMode(Qt::ElideLeft);
        BootExecuteTable->setWordWrap(true);
        BootExecuteTable->horizontalHeader()->setStretchLastSection(true);
        BootExecuteTable->verticalHeader()->setVisible(false);
        BootExecuteTable->verticalHeader()->setCascadingSectionResizes(false);
        tabWidget->addTab(BootExecute, QString());
        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 810, 21));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menurefresh = new QMenu(menuBar);
        menurefresh->setObjectName(QString::fromUtf8("menurefresh"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menurefresh->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout);
        menurefresh->addAction(actionRefresh);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Autoruns", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionRefresh->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
        QTableWidgetItem *___qtablewidgetitem = LogonTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = LogonTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = LogonTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Publisher", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = LogonTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Verified", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = LogonTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Image Path", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Logon), QCoreApplication::translate("MainWindow", "Logon", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = ServicesTable->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = ServicesTable->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = ServicesTable->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Publisher", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = ServicesTable->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Verified", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = ServicesTable->horizontalHeaderItem(4);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Image Path", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Services), QCoreApplication::translate("MainWindow", "Services", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = DriversTable->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = DriversTable->horizontalHeaderItem(1);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = DriversTable->horizontalHeaderItem(2);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "Publisher", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = DriversTable->horizontalHeaderItem(3);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "Verified", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = DriversTable->horizontalHeaderItem(4);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "Image Path", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = DriversTable->verticalHeaderItem(0);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = DriversTable->verticalHeaderItem(1);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "New Row", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Drivers), QCoreApplication::translate("MainWindow", "Drivers", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = TasksTable->horizontalHeaderItem(0);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = TasksTable->horizontalHeaderItem(1);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = TasksTable->horizontalHeaderItem(2);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "Publisher", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = TasksTable->horizontalHeaderItem(3);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "Verified", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = TasksTable->horizontalHeaderItem(4);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("MainWindow", "Image Path", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Tasks), QCoreApplication::translate("MainWindow", "Tasks", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = DllsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = DllsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("MainWindow", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = DllsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("MainWindow", "Publisher", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = DllsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("MainWindow", "Verified", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = DllsTable->horizontalHeaderItem(4);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("MainWindow", "Image Path", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(KnownDlls), QCoreApplication::translate("MainWindow", "KnownDlls", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = BootExecuteTable->horizontalHeaderItem(0);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = BootExecuteTable->horizontalHeaderItem(1);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("MainWindow", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = BootExecuteTable->horizontalHeaderItem(2);
        ___qtablewidgetitem29->setText(QCoreApplication::translate("MainWindow", "Publisher", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = BootExecuteTable->horizontalHeaderItem(3);
        ___qtablewidgetitem30->setText(QCoreApplication::translate("MainWindow", "Verified", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(BootExecute), QCoreApplication::translate("MainWindow", "Boot Execute", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
        menurefresh->setTitle(QCoreApplication::translate("MainWindow", "Tools", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTORUNS_H
