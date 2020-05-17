/********************************************************************************
** Form generated from reading UI file 'serialcurve.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALCURVE_H
#define UI_SERIALCURVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_SerialCurve
{
public:
    QAction *actionSaveImages;
    QAction *actionCharts;
    QAction *actionClear;
    QAction *actionPaused;
    QAction *actionHelpFile;
    QAction *actionCoorTips;
    QAction *actionSelect;
    QAction *actionLBG;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGroupBox *QGBSerialConfig;
    QGridLayout *gridLayout_3;
    QGridLayout *commParam;
    QLabel *lblVerify;
    QComboBox *cbbDataBit;
    QLabel *lblPortNum;
    QLabel *lblStopBit;
    QLabel *lblBaudRate;
    QComboBox *cbbPortNum;
    QComboBox *cbbVerify;
    QComboBox *cbbStopBit;
    QComboBox *cbbBaud;
    QLabel *lblDataBit;
    QPushButton *btnRefresh;
    QPushButton *btnOpenPort;
    QCustomPlot *customPlot;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *rdbMultiPlot;
    QSpinBox *spbNumberG;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *rdbSinglePlot;
    QComboBox *cbbDataType;
    QLineEdit *txtCurveRename;
    QHBoxLayout *horizontalLayout_4;
    QComboBox *btnCurveSel;
    QToolButton *btnColorSel;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SerialCurve)
    {
        if (SerialCurve->objectName().isEmpty())
            SerialCurve->setObjectName(QStringLiteral("SerialCurve"));
        SerialCurve->resize(701, 473);
        actionSaveImages = new QAction(SerialCurve);
        actionSaveImages->setObjectName(QStringLiteral("actionSaveImages"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/general/general/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveImages->setIcon(icon);
        actionCharts = new QAction(SerialCurve);
        actionCharts->setObjectName(QStringLiteral("actionCharts"));
        actionCharts->setCheckable(true);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/general/general/graphsPolyline.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QStringLiteral(":/general/general/graphsHistogram.png"), QSize(), QIcon::Normal, QIcon::On);
        actionCharts->setIcon(icon1);
        actionCharts->setVisible(true);
        actionCharts->setIconVisibleInMenu(true);
        actionClear = new QAction(SerialCurve);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/general/general/Broom.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear->setIcon(icon2);
        actionPaused = new QAction(SerialCurve);
        actionPaused->setObjectName(QStringLiteral("actionPaused"));
        actionPaused->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/general/general/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon3.addFile(QStringLiteral(":/general/general/play.png"), QSize(), QIcon::Normal, QIcon::On);
        actionPaused->setIcon(icon3);
        actionHelpFile = new QAction(SerialCurve);
        actionHelpFile->setObjectName(QStringLiteral("actionHelpFile"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/general/general/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelpFile->setIcon(icon4);
        actionCoorTips = new QAction(SerialCurve);
        actionCoorTips->setObjectName(QStringLiteral("actionCoorTips"));
        actionCoorTips->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/general/general/tips.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCoorTips->setIcon(icon5);
        actionSelect = new QAction(SerialCurve);
        actionSelect->setObjectName(QStringLiteral("actionSelect"));
        actionSelect->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/general/general/selection.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon6.addFile(QStringLiteral(":/general/general/pointer_1.png"), QSize(), QIcon::Normal, QIcon::On);
        actionSelect->setIcon(icon6);
        actionLBG = new QAction(SerialCurve);
        actionLBG->setObjectName(QStringLiteral("actionLBG"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/general/general/Style.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLBG->setIcon(icon7);
        centralWidget = new QWidget(SerialCurve);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        QGBSerialConfig = new QGroupBox(centralWidget);
        QGBSerialConfig->setObjectName(QStringLiteral("QGBSerialConfig"));
        QGBSerialConfig->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QGBSerialConfig->sizePolicy().hasHeightForWidth());
        QGBSerialConfig->setSizePolicy(sizePolicy);
        QGBSerialConfig->setMinimumSize(QSize(171, 211));
        QGBSerialConfig->setMaximumSize(QSize(171, 211));
        QGBSerialConfig->setStyleSheet(QStringLiteral(""));
        QGBSerialConfig->setFlat(false);
        QGBSerialConfig->setCheckable(false);
        gridLayout_3 = new QGridLayout(QGBSerialConfig);
        gridLayout_3->setSpacing(2);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(3, 6, 3, 3);
        commParam = new QGridLayout();
        commParam->setSpacing(6);
        commParam->setObjectName(QStringLiteral("commParam"));
        commParam->setHorizontalSpacing(2);
        commParam->setVerticalSpacing(6);
        lblVerify = new QLabel(QGBSerialConfig);
        lblVerify->setObjectName(QStringLiteral("lblVerify"));

        commParam->addWidget(lblVerify, 3, 0, 1, 1);

        cbbDataBit = new QComboBox(QGBSerialConfig);
        cbbDataBit->setObjectName(QStringLiteral("cbbDataBit"));
        cbbDataBit->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        commParam->addWidget(cbbDataBit, 2, 1, 1, 1);

        lblPortNum = new QLabel(QGBSerialConfig);
        lblPortNum->setObjectName(QStringLiteral("lblPortNum"));

        commParam->addWidget(lblPortNum, 0, 0, 1, 1);

        lblStopBit = new QLabel(QGBSerialConfig);
        lblStopBit->setObjectName(QStringLiteral("lblStopBit"));

        commParam->addWidget(lblStopBit, 4, 0, 1, 1);

        lblBaudRate = new QLabel(QGBSerialConfig);
        lblBaudRate->setObjectName(QStringLiteral("lblBaudRate"));

        commParam->addWidget(lblBaudRate, 1, 0, 1, 1);

        cbbPortNum = new QComboBox(QGBSerialConfig);
        cbbPortNum->setObjectName(QStringLiteral("cbbPortNum"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cbbPortNum->sizePolicy().hasHeightForWidth());
        cbbPortNum->setSizePolicy(sizePolicy1);
        cbbPortNum->setMaxVisibleItems(20);
        cbbPortNum->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        cbbPortNum->setMinimumContentsLength(0);

        commParam->addWidget(cbbPortNum, 0, 1, 1, 1);

        cbbVerify = new QComboBox(QGBSerialConfig);
        cbbVerify->setObjectName(QStringLiteral("cbbVerify"));
        cbbVerify->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        commParam->addWidget(cbbVerify, 3, 1, 1, 1);

        cbbStopBit = new QComboBox(QGBSerialConfig);
        cbbStopBit->setObjectName(QStringLiteral("cbbStopBit"));
        cbbStopBit->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        commParam->addWidget(cbbStopBit, 4, 1, 1, 1);

        cbbBaud = new QComboBox(QGBSerialConfig);
        cbbBaud->setObjectName(QStringLiteral("cbbBaud"));
        cbbBaud->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        commParam->addWidget(cbbBaud, 1, 1, 1, 1);

        lblDataBit = new QLabel(QGBSerialConfig);
        lblDataBit->setObjectName(QStringLiteral("lblDataBit"));

        commParam->addWidget(lblDataBit, 2, 0, 1, 1);


        gridLayout_3->addLayout(commParam, 0, 0, 1, 2);

        btnRefresh = new QPushButton(QGBSerialConfig);
        btnRefresh->setObjectName(QStringLiteral("btnRefresh"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnRefresh->sizePolicy().hasHeightForWidth());
        btnRefresh->setSizePolicy(sizePolicy2);
        btnRefresh->setMinimumSize(QSize(0, 0));
        btnRefresh->setMaximumSize(QSize(60, 41));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/action/action/reload.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnRefresh->setIcon(icon8);
        btnRefresh->setIconSize(QSize(32, 32));

        gridLayout_3->addWidget(btnRefresh, 1, 0, 1, 1);

        btnOpenPort = new QPushButton(QGBSerialConfig);
        btnOpenPort->setObjectName(QStringLiteral("btnOpenPort"));
        btnOpenPort->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(3);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btnOpenPort->sizePolicy().hasHeightForWidth());
        btnOpenPort->setSizePolicy(sizePolicy3);
        btnOpenPort->setMaximumSize(QSize(16777215, 41));
        btnOpenPort->setStyleSheet(QStringLiteral(""));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/general/general/com_disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon9.addFile(QStringLiteral(":/general/general/com_connect_1.png"), QSize(), QIcon::Normal, QIcon::On);
        btnOpenPort->setIcon(icon9);
        btnOpenPort->setIconSize(QSize(32, 32));
        btnOpenPort->setCheckable(true);
        btnOpenPort->setChecked(false);
        btnOpenPort->setAutoDefault(false);
        btnOpenPort->setFlat(false);

        gridLayout_3->addWidget(btnOpenPort, 1, 1, 1, 1);

        gridLayout_3->setColumnMinimumWidth(0, 1);
        gridLayout_3->setColumnMinimumWidth(1, 3);

        gridLayout->addWidget(QGBSerialConfig, 0, 0, 1, 1);

        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));

        gridLayout->addWidget(customPlot, 0, 1, 3, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMaximumSize(QSize(171, 16777215));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        rdbMultiPlot = new QRadioButton(groupBox);
        rdbMultiPlot->setObjectName(QStringLiteral("rdbMultiPlot"));
        rdbMultiPlot->setEnabled(true);

        horizontalLayout->addWidget(rdbMultiPlot);

        spbNumberG = new QSpinBox(groupBox);
        spbNumberG->setObjectName(QStringLiteral("spbNumberG"));
        spbNumberG->setEnabled(false);
        spbNumberG->setMinimum(1);
        spbNumberG->setValue(2);

        horizontalLayout->addWidget(spbNumberG);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        rdbSinglePlot = new QRadioButton(groupBox);
        rdbSinglePlot->setObjectName(QStringLiteral("rdbSinglePlot"));
        rdbSinglePlot->setChecked(true);

        horizontalLayout_2->addWidget(rdbSinglePlot);

        cbbDataType = new QComboBox(groupBox);
        cbbDataType->setObjectName(QStringLiteral("cbbDataType"));

        horizontalLayout_2->addWidget(cbbDataType);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        txtCurveRename = new QLineEdit(groupBox);
        txtCurveRename->setObjectName(QStringLiteral("txtCurveRename"));

        gridLayout_2->addWidget(txtCurveRename, 3, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        btnCurveSel = new QComboBox(groupBox);
        btnCurveSel->setObjectName(QStringLiteral("btnCurveSel"));

        horizontalLayout_4->addWidget(btnCurveSel);

        btnColorSel = new QToolButton(groupBox);
        btnColorSel->setObjectName(QStringLiteral("btnColorSel"));

        horizontalLayout_4->addWidget(btnColorSel);


        gridLayout_2->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 4, 0, 1, 1);


        gridLayout->addWidget(groupBox, 1, 0, 1, 1);

        SerialCurve->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SerialCurve);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 701, 22));
        SerialCurve->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SerialCurve);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SerialCurve->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SerialCurve);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SerialCurve->setStatusBar(statusBar);

        mainToolBar->addAction(actionSaveImages);
        mainToolBar->addAction(actionClear);
        mainToolBar->addAction(actionPaused);
        mainToolBar->addAction(actionSelect);
        mainToolBar->addAction(actionCoorTips);
        mainToolBar->addAction(actionLBG);
        mainToolBar->addAction(actionHelpFile);

        retranslateUi(SerialCurve);

        btnOpenPort->setDefault(false);


        QMetaObject::connectSlotsByName(SerialCurve);
    } // setupUi

    void retranslateUi(QMainWindow *SerialCurve)
    {
        SerialCurve->setWindowTitle(QApplication::translate("SerialCurve", "SerialCurve", Q_NULLPTR));
        actionSaveImages->setText(QApplication::translate("SerialCurve", "\344\277\235\345\255\230", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSaveImages->setToolTip(QApplication::translate("SerialCurve", "\344\277\235\345\255\230\345\233\276\345\203\217", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionCharts->setText(QApplication::translate("SerialCurve", "\346\237\261\347\212\266\345\233\276", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionCharts->setToolTip(QApplication::translate("SerialCurve", "\346\237\261\347\212\266\345\233\276/\346\212\230\347\272\277\345\233\276", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionClear->setText(QApplication::translate("SerialCurve", "\346\270\205\347\251\272\345\233\276\350\241\250", Q_NULLPTR));
        actionPaused->setText(QApplication::translate("SerialCurve", "\346\232\202\345\201\234", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionPaused->setToolTip(QApplication::translate("SerialCurve", "\346\232\202\345\201\234\347\273\230\345\233\276,\344\275\206\344\273\215\347\273\247\347\273\255\346\216\245\346\224\266\346\225\260\346\215\256", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionHelpFile->setText(QApplication::translate("SerialCurve", "\344\275\277\347\224\250\350\257\264\346\230\216", Q_NULLPTR));
        actionCoorTips->setText(QApplication::translate("SerialCurve", "\345\235\220\346\240\207\346\230\276\347\244\272", Q_NULLPTR));
        actionSelect->setText(QApplication::translate("SerialCurve", "\351\200\211\346\213\251\346\224\276\345\244\247", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSelect->setToolTip(QApplication::translate("SerialCurve", "\346\224\276\345\244\247\351\200\211\346\213\251\345\214\272\345\237\237", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionLBG->setText(QApplication::translate("SerialCurve", "\344\272\256\350\211\262\350\203\214\346\231\257", Q_NULLPTR));
        QGBSerialConfig->setTitle(QApplication::translate("SerialCurve", "\344\270\262\345\217\243\350\256\276\347\275\256", Q_NULLPTR));
        lblVerify->setText(QApplication::translate("SerialCurve", "\346\240\241\351\252\214", Q_NULLPTR));
        lblPortNum->setText(QApplication::translate("SerialCurve", "\347\253\257\345\217\243\345\217\267", Q_NULLPTR));
        lblStopBit->setText(QApplication::translate("SerialCurve", "\345\201\234\346\255\242\344\275\215", Q_NULLPTR));
        lblBaudRate->setText(QApplication::translate("SerialCurve", "\346\263\242\347\211\271\347\216\207", Q_NULLPTR));
        lblDataBit->setText(QApplication::translate("SerialCurve", "\346\225\260\346\215\256\344\275\215", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        btnRefresh->setToolTip(QApplication::translate("SerialCurve", "\345\210\267\346\226\260\347\253\257\345\217\243\345\217\267", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btnRefresh->setText(QApplication::translate("SerialCurve", "\345\210\267\346\226\260", Q_NULLPTR));
        btnOpenPort->setText(QApplication::translate("SerialCurve", "\346\211\223\345\274\200\344\270\262\345\217\243", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("SerialCurve", "\346\233\262\347\272\277\350\256\276\347\275\256", Q_NULLPTR));
        rdbMultiPlot->setText(QApplication::translate("SerialCurve", "\345\244\232\346\235\241\346\233\262\347\272\277", Q_NULLPTR));
        rdbSinglePlot->setText(QApplication::translate("SerialCurve", "\345\215\225\344\270\200\346\233\262\347\272\277", Q_NULLPTR));
        cbbDataType->clear();
        cbbDataType->insertItems(0, QStringList()
         << QApplication::translate("SerialCurve", "uint8_t", Q_NULLPTR)
         << QApplication::translate("SerialCurve", "uint16_t", Q_NULLPTR)
         << QApplication::translate("SerialCurve", "uint32_t", Q_NULLPTR)
         << QApplication::translate("SerialCurve", "int8_t", Q_NULLPTR)
         << QApplication::translate("SerialCurve", "int16_t", Q_NULLPTR)
         << QApplication::translate("SerialCurve", "int32_t", Q_NULLPTR)
         << QApplication::translate("SerialCurve", "float", Q_NULLPTR)
        );
#ifndef QT_NO_TOOLTIP
        cbbDataType->setToolTip(QApplication::translate("SerialCurve", "\345\215\225\344\270\252\346\225\260\346\215\256\347\202\271\347\232\204\346\225\260\346\215\256\347\261\273\345\236\213", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        txtCurveRename->setToolTip(QApplication::translate("SerialCurve", "\346\233\262\347\272\277\345\220\215\345\255\227", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        btnColorSel->setToolTip(QApplication::translate("SerialCurve", "\350\256\276\347\275\256\351\242\234\350\211\262", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btnColorSel->setText(QString());
#ifndef QT_NO_TOOLTIP
        mainToolBar->setToolTip(QApplication::translate("SerialCurve", "\344\272\256\350\211\262\350\203\214\346\231\257", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class SerialCurve: public Ui_SerialCurve {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALCURVE_H
