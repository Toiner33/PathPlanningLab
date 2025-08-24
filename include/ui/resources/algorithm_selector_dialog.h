/********************************************************************************
** Form generated from reading UI file 'algorithm_selector_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef ALGORITHM_SELECTOR_DIALOG_H
#define ALGORITHM_SELECTOR_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_algorithmsDialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *AStarSettingsBt;
    QFrame *TitleSeparator;
    QRadioButton *AStarRadioBt;
    QLabel *AStarLabel;
    QRadioButton *DijkstraRadioBt;
    QPushButton *DijkstraSettingsBt;

    void setupUi(QDialog *algorithmsDialog)
    {
        if (algorithmsDialog->objectName().isEmpty())
            algorithmsDialog->setObjectName(QString::fromUtf8("algorithmsDialog"));
        algorithmsDialog->setEnabled(true);
        algorithmsDialog->resize(329, 100);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(algorithmsDialog->sizePolicy().hasHeightForWidth());
        algorithmsDialog->setSizePolicy(sizePolicy);
        algorithmsDialog->setLayoutDirection(Qt::LeftToRight);
        gridLayout = new QGridLayout(algorithmsDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        AStarSettingsBt = new QPushButton(algorithmsDialog);
        AStarSettingsBt->setObjectName(QString::fromUtf8("AStarSettingsBt"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(AStarSettingsBt->sizePolicy().hasHeightForWidth());
        AStarSettingsBt->setSizePolicy(sizePolicy1);
        AStarSettingsBt->setMinimumSize(QSize(145, 23));
        AStarSettingsBt->setAutoDefault(false);

        gridLayout->addWidget(AStarSettingsBt, 2, 1, 1, 1);

        TitleSeparator = new QFrame(algorithmsDialog);
        TitleSeparator->setObjectName(QString::fromUtf8("TitleSeparator"));
        sizePolicy1.setHeightForWidth(TitleSeparator->sizePolicy().hasHeightForWidth());
        TitleSeparator->setSizePolicy(sizePolicy1);
        TitleSeparator->setFrameShape(QFrame::HLine);
        TitleSeparator->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(TitleSeparator, 1, 0, 1, 2);

        AStarRadioBt = new QRadioButton(algorithmsDialog);
        AStarRadioBt->setObjectName(QString::fromUtf8("AStarRadioBt"));
        sizePolicy1.setHeightForWidth(AStarRadioBt->sizePolicy().hasHeightForWidth());
        AStarRadioBt->setSizePolicy(sizePolicy1);
        AStarRadioBt->setMinimumSize(QSize(160, 21));
        AStarRadioBt->setChecked(true);

        gridLayout->addWidget(AStarRadioBt, 2, 0, 1, 1);

        AStarLabel = new QLabel(algorithmsDialog);
        AStarLabel->setObjectName(QString::fromUtf8("AStarLabel"));
        sizePolicy1.setHeightForWidth(AStarLabel->sizePolicy().hasHeightForWidth());
        AStarLabel->setSizePolicy(sizePolicy1);
        AStarLabel->setMinimumSize(QSize(311, 15));
        AStarLabel->setAutoFillBackground(false);
        AStarLabel->setFrameShape(QFrame::NoFrame);

        gridLayout->addWidget(AStarLabel, 0, 0, 1, 2);

        DijkstraRadioBt = new QRadioButton(algorithmsDialog);
        DijkstraRadioBt->setObjectName(QString::fromUtf8("DijkstraRadioBt"));

        gridLayout->addWidget(DijkstraRadioBt, 3, 0, 1, 1);

        DijkstraSettingsBt = new QPushButton(algorithmsDialog);
        DijkstraSettingsBt->setObjectName(QString::fromUtf8("DijkstraSettingsBt"));
        DijkstraSettingsBt->setAutoDefault(false);

        gridLayout->addWidget(DijkstraSettingsBt, 3, 1, 1, 1);


        retranslateUi(algorithmsDialog);

        AStarSettingsBt->setDefault(false);


        QMetaObject::connectSlotsByName(algorithmsDialog);
    } // setupUi

    void retranslateUi(QDialog *algorithmsDialog)
    {
        algorithmsDialog->setWindowTitle(QCoreApplication::translate("algorithmsDialog", "Algorithm Selection", nullptr));
        AStarSettingsBt->setText(QCoreApplication::translate("algorithmsDialog", "Settings", nullptr));
        AStarRadioBt->setText(QCoreApplication::translate("algorithmsDialog", "AStar", nullptr));
        AStarLabel->setText(QCoreApplication::translate("algorithmsDialog", "Available algorithms", nullptr));
        DijkstraRadioBt->setText(QCoreApplication::translate("algorithmsDialog", "Dijkstra", nullptr));
        DijkstraSettingsBt->setText(QCoreApplication::translate("algorithmsDialog", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class algorithmsDialog: public Ui_algorithmsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ALGORITHM_SELECTOR_DIALOG_H
