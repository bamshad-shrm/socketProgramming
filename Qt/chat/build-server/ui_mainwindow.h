/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionChat;
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QLineEdit *portlineEdit;
    QPushButton *startButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *stopButton;
    QScrollArea *infoScrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *infoLable;
    QScrollArea *chatScrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout_2;
    QLabel *chatLable;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(686, 544);
        actionChat = new QAction(MainWindow);
        actionChat->setObjectName(QStringLiteral("actionChat"));
        actionChat->setCheckable(true);
        actionChat->setChecked(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        portlineEdit = new QLineEdit(centralWidget);
        portlineEdit->setObjectName(QStringLiteral("portlineEdit"));

        gridLayout_3->addWidget(portlineEdit, 0, 1, 1, 1);

        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));

        gridLayout_3->addWidget(startButton, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(446, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 3, 1, 1);

        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));

        gridLayout_3->addWidget(stopButton, 0, 4, 1, 1);

        infoScrollArea = new QScrollArea(centralWidget);
        infoScrollArea->setObjectName(QStringLiteral("infoScrollArea"));
        infoScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 666, 232));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        infoLable = new QLabel(scrollAreaWidgetContents);
        infoLable->setObjectName(QStringLiteral("infoLable"));
        infoLable->setFrameShape(QFrame::Box);
        infoLable->setLineWidth(2);

        gridLayout->addWidget(infoLable, 0, 0, 1, 1);

        infoScrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_3->addWidget(infoScrollArea, 1, 0, 1, 5);

        chatScrollArea = new QScrollArea(centralWidget);
        chatScrollArea->setObjectName(QStringLiteral("chatScrollArea"));
        chatScrollArea->setMaximumSize(QSize(16777215, 250));
        chatScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 666, 231));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        chatLable = new QLabel(scrollAreaWidgetContents_2);
        chatLable->setObjectName(QStringLiteral("chatLable"));
        chatLable->setFrameShape(QFrame::Box);
        chatLable->setLineWidth(2);

        gridLayout_2->addWidget(chatLable, 0, 0, 1, 1);

        chatScrollArea->setWidget(scrollAreaWidgetContents_2);

        gridLayout_3->addWidget(chatScrollArea, 2, 0, 1, 5);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 686, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuView->addAction(actionChat);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Server", Q_NULLPTR));
        actionChat->setText(QApplication::translate("MainWindow", "Chat", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Port:", Q_NULLPTR));
        startButton->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        stopButton->setText(QApplication::translate("MainWindow", "Stop", Q_NULLPTR));
        infoLable->setText(QString());
        chatLable->setText(QString());
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("MainWindow", "View", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
