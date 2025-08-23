/********************************************************************************
** Form generated from reading UI file 'ui_main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionDraw;
    QAction *actionErase;
    QAction *actionTools;
    QAction *actionAreas;
    QAction *actionDrivable;
    QAction *actionActions;
    QAction *actionClear;
    QAction *actionStop;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(858, 713);
        MainWindow->setTabShape(QTabWidget::Rounded);
        actionDraw = new QAction(MainWindow);
        actionDraw->setObjectName(QString::fromUtf8("actionDraw"));
        actionDraw->setCheckable(true);
        actionDraw->setChecked(false);
        actionErase = new QAction(MainWindow);
        actionErase->setObjectName(QString::fromUtf8("actionErase"));
        actionErase->setCheckable(true);
        actionErase->setChecked(false);
        actionTools = new QAction(MainWindow);
        actionTools->setObjectName(QString::fromUtf8("actionTools"));
        actionTools->setEnabled(false);
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(true);
        actionTools->setFont(font);
        actionAreas = new QAction(MainWindow);
        actionAreas->setObjectName(QString::fromUtf8("actionAreas"));
        actionAreas->setEnabled(false);
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        actionAreas->setFont(font1);
        actionDrivable = new QAction(MainWindow);
        actionDrivable->setObjectName(QString::fromUtf8("actionDrivable"));
        actionDrivable->setCheckable(true);
        actionActions = new QAction(MainWindow);
        actionActions->setObjectName(QString::fromUtf8("actionActions"));
        actionActions->setEnabled(false);
        actionActions->setFont(font1);
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QString::fromUtf8("actionClear"));
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMouseTracking(true);
        graphicsView->setRenderHints(QPainter::Antialiasing);
        graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

        gridLayout->addWidget(graphicsView, 0, 0, 6, 1);

        MainWindow->setCentralWidget(centralwidget);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(toolBar->sizePolicy().hasHeightForWidth());
        toolBar->setSizePolicy(sizePolicy);
        MainWindow->addToolBar(Qt::RightToolBarArea, toolBar);

        toolBar->addSeparator();
        toolBar->addAction(actionActions);
        toolBar->addSeparator();
        toolBar->addAction(actionClear);
        toolBar->addAction(actionStop);
        toolBar->addSeparator();
        toolBar->addAction(actionTools);
        toolBar->addSeparator();
        toolBar->addAction(actionDraw);
        toolBar->addAction(actionErase);
        toolBar->addSeparator();
        toolBar->addAction(actionAreas);
        toolBar->addSeparator();
        toolBar->addAction(actionDrivable);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionDraw->setText(QCoreApplication::translate("MainWindow", "Draw", nullptr));
#if QT_CONFIG(tooltip)
        actionDraw->setToolTip(QCoreApplication::translate("MainWindow", "Use this tool for drawing", nullptr));
#endif // QT_CONFIG(tooltip)
        actionErase->setText(QCoreApplication::translate("MainWindow", "Erase", nullptr));
#if QT_CONFIG(tooltip)
        actionErase->setToolTip(QCoreApplication::translate("MainWindow", "Use this tool to erase", nullptr));
#endif // QT_CONFIG(tooltip)
        actionTools->setText(QCoreApplication::translate("MainWindow", "Tools   ", nullptr));
#if QT_CONFIG(tooltip)
        actionTools->setToolTip(QCoreApplication::translate("MainWindow", "This are the tool options", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAreas->setText(QCoreApplication::translate("MainWindow", "Areas", nullptr));
#if QT_CONFIG(tooltip)
        actionAreas->setToolTip(QCoreApplication::translate("MainWindow", "These are the possilble areas you can draw", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDrivable->setText(QCoreApplication::translate("MainWindow", "Drivable", nullptr));
#if QT_CONFIG(tooltip)
        actionDrivable->setToolTip(QCoreApplication::translate("MainWindow", "This is the most basic area where a path can be found", nullptr));
#endif // QT_CONFIG(tooltip)
        actionActions->setText(QCoreApplication::translate("MainWindow", "Actions", nullptr));
#if QT_CONFIG(tooltip)
        actionActions->setToolTip(QCoreApplication::translate("MainWindow", "Actions to interact with the whole scene", nullptr));
#endif // QT_CONFIG(tooltip)
        actionClear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
#if QT_CONFIG(tooltip)
        actionClear->setToolTip(QCoreApplication::translate("MainWindow", "Clear all drawings from the scene", nullptr));
#endif // QT_CONFIG(tooltip)
        actionStop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
#if QT_CONFIG(tooltip)
        actionStop->setToolTip(QCoreApplication::translate("MainWindow", "Stop drawing", nullptr));
#endif // QT_CONFIG(tooltip)
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
