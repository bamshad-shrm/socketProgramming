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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConnection_messages;
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QScrollArea *connectionScrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout;
    QLabel *connectionLable;
    QPushButton *connectButton;
    QLineEdit *IPlineEdit;
    QPushButton *sendButton;
    QLabel *serverIpLabel;
    QLineEdit *PortlineEdit;
    QPushButton *disconnectButton;
    QScrollArea *msgScrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QLabel *chatLable;
    QLabel *userNameLabel;
    QLineEdit *userNamelineEdit;
    QLabel *serverPortLabel;
    QLineEdit *msgLineEdit;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(685, 488);
        actionConnection_messages = new QAction(MainWindow);
        actionConnection_messages->setObjectName(QStringLiteral("actionConnection_messages"));
        actionConnection_messages->setCheckable(true);
        actionConnection_messages->setChecked(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        connectionScrollArea = new QScrollArea(centralWidget);
        connectionScrollArea->setObjectName(QStringLiteral("connectionScrollArea"));
        connectionScrollArea->setMaximumSize(QSize(16777215, 250));
        connectionScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 665, 188));
        gridLayout = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        connectionLable = new QLabel(scrollAreaWidgetContents_2);
        connectionLable->setObjectName(QStringLiteral("connectionLable"));
        connectionLable->setMaximumSize(QSize(16777215, 16777215));
        connectionLable->setFrameShape(QFrame::Box);
        connectionLable->setLineWidth(2);

        gridLayout->addWidget(connectionLable, 0, 0, 1, 1);

        connectionScrollArea->setWidget(scrollAreaWidgetContents_2);

        gridLayout_3->addWidget(connectionScrollArea, 2, 0, 1, 8);

        connectButton = new QPushButton(centralWidget);
        connectButton->setObjectName(QStringLiteral("connectButton"));

        gridLayout_3->addWidget(connectButton, 0, 6, 1, 1);

        IPlineEdit = new QLineEdit(centralWidget);
        IPlineEdit->setObjectName(QStringLiteral("IPlineEdit"));

        gridLayout_3->addWidget(IPlineEdit, 0, 1, 1, 1);

        sendButton = new QPushButton(centralWidget);
        sendButton->setObjectName(QStringLiteral("sendButton"));

        gridLayout_3->addWidget(sendButton, 3, 7, 1, 1);

        serverIpLabel = new QLabel(centralWidget);
        serverIpLabel->setObjectName(QStringLiteral("serverIpLabel"));

        gridLayout_3->addWidget(serverIpLabel, 0, 0, 1, 1);

        PortlineEdit = new QLineEdit(centralWidget);
        PortlineEdit->setObjectName(QStringLiteral("PortlineEdit"));

        gridLayout_3->addWidget(PortlineEdit, 0, 3, 1, 1);

        disconnectButton = new QPushButton(centralWidget);
        disconnectButton->setObjectName(QStringLiteral("disconnectButton"));

        gridLayout_3->addWidget(disconnectButton, 0, 7, 1, 1);

        msgScrollArea = new QScrollArea(centralWidget);
        msgScrollArea->setObjectName(QStringLiteral("msgScrollArea"));
        msgScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 665, 188));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        chatLable = new QLabel(scrollAreaWidgetContents);
        chatLable->setObjectName(QStringLiteral("chatLable"));
        chatLable->setMinimumSize(QSize(0, 0));
        chatLable->setFrameShape(QFrame::Box);
        chatLable->setLineWidth(2);
        chatLable->setMargin(0);

        gridLayout_2->addWidget(chatLable, 0, 0, 1, 1);

        msgScrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_3->addWidget(msgScrollArea, 1, 0, 1, 8);

        userNameLabel = new QLabel(centralWidget);
        userNameLabel->setObjectName(QStringLiteral("userNameLabel"));

        gridLayout_3->addWidget(userNameLabel, 0, 4, 1, 1);

        userNamelineEdit = new QLineEdit(centralWidget);
        userNamelineEdit->setObjectName(QStringLiteral("userNamelineEdit"));

        gridLayout_3->addWidget(userNamelineEdit, 0, 5, 1, 1);

        serverPortLabel = new QLabel(centralWidget);
        serverPortLabel->setObjectName(QStringLiteral("serverPortLabel"));

        gridLayout_3->addWidget(serverPortLabel, 0, 2, 1, 1);

        msgLineEdit = new QLineEdit(centralWidget);
        msgLineEdit->setObjectName(QStringLiteral("msgLineEdit"));

        gridLayout_3->addWidget(msgLineEdit, 3, 0, 1, 7);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 685, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuView->addAction(actionConnection_messages);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Client", Q_NULLPTR));
        actionConnection_messages->setText(QApplication::translate("MainWindow", "Connection messages", Q_NULLPTR));
        connectionLable->setText(QString());
        connectButton->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        sendButton->setText(QApplication::translate("MainWindow", "send", Q_NULLPTR));
        serverIpLabel->setText(QApplication::translate("MainWindow", "Server IP:", Q_NULLPTR));
        disconnectButton->setText(QApplication::translate("MainWindow", "Disconnect", Q_NULLPTR));
        chatLable->setText(QString());
        userNameLabel->setText(QApplication::translate("MainWindow", "User name: ", Q_NULLPTR));
        serverPortLabel->setText(QApplication::translate("MainWindow", "Server Port:", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("MainWindow", "View", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
