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
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QPushButton *sceneClearBt;
    QPushButton *stopDrawingBt;
    QGroupBox *drawingToolsBox;
    QPushButton *eraseBt;
    QPushButton *drawBt;
    QGroupBox *drawingAreaBox;
    QPushButton *drivableBt;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(826, 696);
        MainWindow->setTabShape(QTabWidget::Rounded);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMouseTracking(true);
        graphicsView->setRenderHints(QPainter::Antialiasing);
        graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

        gridLayout->addWidget(graphicsView, 0, 0, 14, 1);

        sceneClearBt = new QPushButton(centralwidget);
        sceneClearBt->setObjectName(QString::fromUtf8("sceneClearBt"));
        sceneClearBt->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(sceneClearBt, 0, 1, 1, 1);

        stopDrawingBt = new QPushButton(centralwidget);
        stopDrawingBt->setObjectName(QString::fromUtf8("stopDrawingBt"));
        stopDrawingBt->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(stopDrawingBt, 1, 1, 1, 1);

        drawingToolsBox = new QGroupBox(centralwidget);
        drawingToolsBox->setObjectName(QString::fromUtf8("drawingToolsBox"));
        eraseBt = new QPushButton(drawingToolsBox);
        eraseBt->setObjectName(QString::fromUtf8("eraseBt"));
        eraseBt->setGeometry(QRect(10, 70, 91, 31));
        eraseBt->setFocusPolicy(Qt::NoFocus);
        eraseBt->setCheckable(true);
        eraseBt->setChecked(false);
        drawBt = new QPushButton(drawingToolsBox);
        drawBt->setObjectName(QString::fromUtf8("drawBt"));
        drawBt->setGeometry(QRect(10, 30, 91, 31));
        drawBt->setFocusPolicy(Qt::NoFocus);
        drawBt->setCheckable(true);
        drawBt->setChecked(false);

        gridLayout->addWidget(drawingToolsBox, 2, 1, 3, 1);

        drawingAreaBox = new QGroupBox(centralwidget);
        drawingAreaBox->setObjectName(QString::fromUtf8("drawingAreaBox"));
        drivableBt = new QPushButton(drawingAreaBox);
        drivableBt->setObjectName(QString::fromUtf8("drivableBt"));
        drivableBt->setGeometry(QRect(10, 30, 91, 31));
        drivableBt->setFocusPolicy(Qt::NoFocus);
        drivableBt->setCheckable(true);
        drivableBt->setChecked(false);

        gridLayout->addWidget(drawingAreaBox, 5, 1, 2, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 826, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        sceneClearBt->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        stopDrawingBt->setText(QCoreApplication::translate("MainWindow", "StopDrawing", nullptr));
        drawingToolsBox->setTitle(QCoreApplication::translate("MainWindow", "Drawing Tools", nullptr));
        eraseBt->setText(QCoreApplication::translate("MainWindow", "Erase", nullptr));
        drawBt->setText(QCoreApplication::translate("MainWindow", "Draw", nullptr));
        drawingAreaBox->setTitle(QCoreApplication::translate("MainWindow", "Drawing Area", nullptr));
        drivableBt->setText(QCoreApplication::translate("MainWindow", "Drivable", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
