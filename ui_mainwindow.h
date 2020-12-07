/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "xtablewidget.h"
#include "xtreewidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    xTreeWidget *ptree;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEditLocalpwd;
    QLabel *m_pLabelState;
    QLabel *label;
    QLineEdit *lineEditHostpwd;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_3;
    xTableWidget *ptablelocal;
    xTableWidget *ptableRemote;
    QTextBrowser *textBrowser;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1877, 1041);
        QFont font;
        font.setFamily(QStringLiteral("DejaVu Sans Mono"));
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        ptree = new xTreeWidget(centralWidget);
        ptree->setObjectName(QStringLiteral("ptree"));
        ptree->setMinimumSize(QSize(300, 300));
        ptree->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_4->addWidget(ptree);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(9);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font1;
        font1.setFamily(QStringLiteral("DejaVu Sans Mono"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);

        horizontalLayout->addWidget(label_2);

        lineEditLocalpwd = new QLineEdit(centralWidget);
        lineEditLocalpwd->setObjectName(QStringLiteral("lineEditLocalpwd"));
        QFont font2;
        font2.setFamily(QStringLiteral("DejaVu Sans Mono"));
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        lineEditLocalpwd->setFont(font2);

        horizontalLayout->addWidget(lineEditLocalpwd);

        m_pLabelState = new QLabel(centralWidget);
        m_pLabelState->setObjectName(QStringLiteral("m_pLabelState"));
        m_pLabelState->setMinimumSize(QSize(0, 0));

        horizontalLayout->addWidget(m_pLabelState);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font1);

        horizontalLayout->addWidget(label);

        lineEditHostpwd = new QLineEdit(centralWidget);
        lineEditHostpwd->setObjectName(QStringLiteral("lineEditHostpwd"));
        lineEditHostpwd->setFont(font2);

        horizontalLayout->addWidget(lineEditHostpwd);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        ptablelocal = new xTableWidget(centralWidget);
        ptablelocal->setObjectName(QStringLiteral("ptablelocal"));
        ptablelocal->setMinimumSize(QSize(222, 600));

        horizontalLayout_3->addWidget(ptablelocal);

        ptableRemote = new xTableWidget(centralWidget);
        ptableRemote->setObjectName(QStringLiteral("ptableRemote"));
        ptableRemote->setMinimumSize(QSize(222, 600));

        horizontalLayout_3->addWidget(ptableRemote);


        verticalLayout->addLayout(horizontalLayout_3);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setMaximumSize(QSize(16777215, 200));
        textBrowser->setFont(font1);

        verticalLayout->addWidget(textBrowser);


        horizontalLayout_4->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_4);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1877, 23));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label_2->setText(QApplication::translate("MainWindow", "\346\234\254\345\234\260\345\275\223\345\211\215\350\267\257\345\276\204:", 0));
        m_pLabelState->setText(QString());
        label->setText(QApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\345\275\223\345\211\215\350\267\257\345\276\204:", 0));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
