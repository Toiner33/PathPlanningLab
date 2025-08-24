/********************************************************************************
** Form generated from reading UI file 'algorithm_settings_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef ALGORITHM_SETTINGS_DIALOG_H
#define ALGORITHM_SETTINGS_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *SettingsTitleLabel;
    QComboBox *comboBox;
    QFrame *TitleSeparator;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QString::fromUtf8("SettingsDialog"));
        SettingsDialog->setEnabled(true);
        SettingsDialog->resize(338, 71);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SettingsDialog->sizePolicy().hasHeightForWidth());
        SettingsDialog->setSizePolicy(sizePolicy);
        SettingsDialog->setLayoutDirection(Qt::LeftToRight);
        gridLayout = new QGridLayout(SettingsDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(SettingsDialog);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(166, 15));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        SettingsTitleLabel = new QLabel(SettingsDialog);
        SettingsTitleLabel->setObjectName(QString::fromUtf8("SettingsTitleLabel"));
        sizePolicy1.setHeightForWidth(SettingsTitleLabel->sizePolicy().hasHeightForWidth());
        SettingsTitleLabel->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(SettingsTitleLabel, 0, 0, 1, 1);

        comboBox = new QComboBox(SettingsDialog);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);
        comboBox->setMinimumSize(QSize(148, 23));

        gridLayout->addWidget(comboBox, 2, 1, 1, 1);

        TitleSeparator = new QFrame(SettingsDialog);
        TitleSeparator->setObjectName(QString::fromUtf8("TitleSeparator"));
        TitleSeparator->setLineWidth(10);
        TitleSeparator->setFrameShape(QFrame::HLine);
        TitleSeparator->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(TitleSeparator, 1, 0, 1, 2);


        retranslateUi(SettingsDialog);

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QCoreApplication::translate("SettingsDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SettingsDialog", "Discretization method", nullptr));
        SettingsTitleLabel->setText(QCoreApplication::translate("SettingsDialog", "Settings", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("SettingsDialog", "Occupancy Grid", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("SettingsDialog", "Triangulation", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("SettingsDialog", "Quadtree", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("SettingsDialog", "None", nullptr));

    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ALGORITHM_SETTINGS_DIALOG_H
