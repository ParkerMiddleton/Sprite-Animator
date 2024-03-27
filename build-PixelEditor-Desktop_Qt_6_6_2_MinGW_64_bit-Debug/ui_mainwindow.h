/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <framewindow.h>
#include <previewwindow.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *editWindowGrid;
    QFrame *editWindowFrame;
    FrameWindow *canvas;
    QGroupBox *ToolsGroupBox;
    QPushButton *EraserButton;
    QPushButton *PencilButton;
    QPushButton *ColorPaletteButton;
    QSlider *pencilSlider;
    QSlider *eraserSlider;
    QLabel *pencilSizeText;
    QLabel *EraserSizeText;
    QLabel *currentColorDisplay;
    QLabel *currentColorText;
    QLineEdit *eraserSizeTextBox;
    QLineEdit *pencilSizeTextBox;
    QFrame *previewFrame;
    QWidget *gridLayoutWidget_2;
    QGridLayout *previewGrid;
    PreviewWindow *previewLabel;
    QPushButton *playAnimationButton;
    QPushButton *stopAnimationButton;
    QLabel *currentLayerText;
    QLabel *previewLableText;
    QFrame *layerFrame;
    QWidget *gridLayoutWidget_3;
    QGridLayout *layerViewGrid;
    QPushButton *addLayer;
    QPushButton *removeLayer;
    QWidget *gridLayoutWidget_4;
    QGridLayout *layersGrid;
    QLabel *layersText;
    QFrame *frameTimelineFrame;
    QPushButton *addFrameButton;
    QLabel *frameTimelineText;
    QPushButton *deleteFrameButton;
    QPushButton *moveFrameLeftButton;
    QPushButton *moveFrameRightButton;
    QWidget *gridLayoutWidget_5;
    QGridLayout *frameTimelineGrid;
    QFrame *positionFrame;
    QLabel *xCoordText;
    QLabel *yCoordText;
    QLineEdit *xCpprdTextBpx;
    QLineEdit *yCoordTextBox;
    QLabel *positionText;
    QLabel *segFaultLogo;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(968, 652);
        MainWindow->setStyleSheet(QString::fromUtf8("color:white;\n"
"background-color:rgb(37, 37, 37)"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(100, 30, 621, 461));
        editWindowGrid = new QGridLayout(gridLayoutWidget);
        editWindowGrid->setObjectName("editWindowGrid");
        editWindowGrid->setSizeConstraint(QLayout::SetNoConstraint);
        editWindowGrid->setContentsMargins(0, 0, 0, 0);
        editWindowFrame = new QFrame(gridLayoutWidget);
        editWindowFrame->setObjectName("editWindowFrame");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(editWindowFrame->sizePolicy().hasHeightForWidth());
        editWindowFrame->setSizePolicy(sizePolicy);
        editWindowFrame->setAutoFillBackground(false);
        editWindowFrame->setStyleSheet(QString::fromUtf8(" border-radius: 0px;\n"
"    border: 1px ridge #fff; \n"
"  background-image: url(':/Images/transparent.png')"));
        editWindowFrame->setFrameShape(QFrame::Box);
        editWindowFrame->setFrameShadow(QFrame::Plain);
        editWindowFrame->setLineWidth(11);
        editWindowFrame->setMidLineWidth(0);
        canvas = new FrameWindow(editWindowFrame);
        canvas->setObjectName("canvas");
        canvas->setGeometry(QRect(0, 0, 621, 461));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(canvas->sizePolicy().hasHeightForWidth());
        canvas->setSizePolicy(sizePolicy1);
        canvas->setCursor(QCursor(Qt::ArrowCursor));

        editWindowGrid->addWidget(editWindowFrame, 0, 0, 1, 1);

        ToolsGroupBox = new QGroupBox(centralwidget);
        ToolsGroupBox->setObjectName("ToolsGroupBox");
        ToolsGroupBox->setGeometry(QRect(10, 50, 81, 441));
        ToolsGroupBox->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
" border-radius: 5px;\n"
"    border: 2px ridge #fff; "));
        ToolsGroupBox->setAlignment(Qt::AlignCenter);
        ToolsGroupBox->setFlat(false);
        EraserButton = new QPushButton(ToolsGroupBox);
        EraserButton->setObjectName("EraserButton");
        EraserButton->setGeometry(QRect(10, 70, 61, 50));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(EraserButton->sizePolicy().hasHeightForWidth());
        EraserButton->setSizePolicy(sizePolicy2);
        EraserButton->setMaximumSize(QSize(16777215, 50));
        PencilButton = new QPushButton(ToolsGroupBox);
        PencilButton->setObjectName("PencilButton");
        PencilButton->setGeometry(QRect(10, 20, 61, 50));
        sizePolicy2.setHeightForWidth(PencilButton->sizePolicy().hasHeightForWidth());
        PencilButton->setSizePolicy(sizePolicy2);
        PencilButton->setMaximumSize(QSize(16777215, 50));
        PencilButton->setStyleSheet(QString::fromUtf8("border-color: rgb(255, 255, 255);"));
        ColorPaletteButton = new QPushButton(ToolsGroupBox);
        ColorPaletteButton->setObjectName("ColorPaletteButton");
        ColorPaletteButton->setGeometry(QRect(10, 120, 61, 51));
        ColorPaletteButton->setStyleSheet(QString::fromUtf8(""));
        ColorPaletteButton->setIconSize(QSize(40, 40));
        pencilSlider = new QSlider(ToolsGroupBox);
        pencilSlider->setObjectName("pencilSlider");
        pencilSlider->setGeometry(QRect(10, 310, 61, 16));
        pencilSlider->setStyleSheet(QString::fromUtf8("border:none;"));
        pencilSlider->setOrientation(Qt::Horizontal);
        eraserSlider = new QSlider(ToolsGroupBox);
        eraserSlider->setObjectName("eraserSlider");
        eraserSlider->setGeometry(QRect(10, 390, 61, 16));
        eraserSlider->setStyleSheet(QString::fromUtf8("border:none;"));
        eraserSlider->setOrientation(Qt::Horizontal);
        pencilSizeText = new QLabel(ToolsGroupBox);
        pencilSizeText->setObjectName("pencilSizeText");
        pencilSizeText->setGeometry(QRect(10, 290, 61, 16));
        pencilSizeText->setStyleSheet(QString::fromUtf8("border:none;\n"
"color: rgb(255, 255, 255);"));
        EraserSizeText = new QLabel(ToolsGroupBox);
        EraserSizeText->setObjectName("EraserSizeText");
        EraserSizeText->setGeometry(QRect(10, 370, 61, 16));
        EraserSizeText->setStyleSheet(QString::fromUtf8("border:none;\n"
"color: rgb(255, 255, 255);"));
        currentColorDisplay = new QLabel(ToolsGroupBox);
        currentColorDisplay->setObjectName("currentColorDisplay");
        currentColorDisplay->setGeometry(QRect(10, 200, 61, 61));
        currentColorText = new QLabel(ToolsGroupBox);
        currentColorText->setObjectName("currentColorText");
        currentColorText->setGeometry(QRect(20, 180, 31, 20));
        currentColorText->setStyleSheet(QString::fromUtf8("border:none;"));
        eraserSizeTextBox = new QLineEdit(ToolsGroupBox);
        eraserSizeTextBox->setObjectName("eraserSizeTextBox");
        eraserSizeTextBox->setGeometry(QRect(10, 410, 61, 20));
        pencilSizeTextBox = new QLineEdit(ToolsGroupBox);
        pencilSizeTextBox->setObjectName("pencilSizeTextBox");
        pencilSizeTextBox->setGeometry(QRect(10, 330, 61, 20));
        previewFrame = new QFrame(centralwidget);
        previewFrame->setObjectName("previewFrame");
        previewFrame->setGeometry(QRect(730, 30, 221, 191));
        previewFrame->setStyleSheet(QString::fromUtf8("\n"
" border-radius: 5px;\n"
"    border: 2px ridge #fff; \n"
" "));
        previewFrame->setFrameShape(QFrame::Box);
        previewFrame->setFrameShadow(QFrame::Plain);
        previewFrame->setLineWidth(3);
        previewFrame->setMidLineWidth(3);
        gridLayoutWidget_2 = new QWidget(previewFrame);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(9, 9, 201, 151));
        previewGrid = new QGridLayout(gridLayoutWidget_2);
        previewGrid->setObjectName("previewGrid");
        previewGrid->setContentsMargins(0, 0, 0, 0);
        previewLabel = new PreviewWindow(gridLayoutWidget_2);
        previewLabel->setObjectName("previewLabel");

        previewGrid->addWidget(previewLabel, 0, 0, 1, 1);

        playAnimationButton = new QPushButton(previewFrame);
        playAnimationButton->setObjectName("playAnimationButton");
        playAnimationButton->setGeometry(QRect(10, 160, 71, 18));
        playAnimationButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color:rgb(228, 232, 255);\n"
"border: none;"));
        stopAnimationButton = new QPushButton(previewFrame);
        stopAnimationButton->setObjectName("stopAnimationButton");
        stopAnimationButton->setGeometry(QRect(130, 160, 80, 18));
        stopAnimationButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color:rgb(228, 232, 255);\n"
"border: none;"));
        currentLayerText = new QLabel(centralwidget);
        currentLayerText->setObjectName("currentLayerText");
        currentLayerText->setGeometry(QRect(100, 10, 81, 16));
        currentLayerText->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        previewLableText = new QLabel(centralwidget);
        previewLableText->setObjectName("previewLableText");
        previewLableText->setGeometry(QRect(730, 10, 101, 16));
        previewLableText->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        layerFrame = new QFrame(centralwidget);
        layerFrame->setObjectName("layerFrame");
        layerFrame->setGeometry(QRect(730, 250, 221, 231));
        layerFrame->setStyleSheet(QString::fromUtf8("\n"
" border-radius: 5px;\n"
"    border: 2px ridge #fff; \n"
" "));
        layerFrame->setFrameShape(QFrame::Box);
        layerFrame->setFrameShadow(QFrame::Plain);
        layerFrame->setLineWidth(3);
        gridLayoutWidget_3 = new QWidget(layerFrame);
        gridLayoutWidget_3->setObjectName("gridLayoutWidget_3");
        gridLayoutWidget_3->setGeometry(QRect(10, 10, 201, 131));
        layerViewGrid = new QGridLayout(gridLayoutWidget_3);
        layerViewGrid->setObjectName("layerViewGrid");
        layerViewGrid->setContentsMargins(0, 0, 0, 0);
        addLayer = new QPushButton(layerFrame);
        addLayer->setObjectName("addLayer");
        addLayer->setGeometry(QRect(10, 150, 80, 18));
        addLayer->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color:rgb(228, 232, 255);\n"
"border: none;"));
        removeLayer = new QPushButton(layerFrame);
        removeLayer->setObjectName("removeLayer");
        removeLayer->setGeometry(QRect(130, 150, 80, 18));
        removeLayer->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color:rgb(228, 232, 255);\n"
"border: none;"));
        gridLayoutWidget_4 = new QWidget(layerFrame);
        gridLayoutWidget_4->setObjectName("gridLayoutWidget_4");
        gridLayoutWidget_4->setGeometry(QRect(10, 170, 201, 51));
        layersGrid = new QGridLayout(gridLayoutWidget_4);
        layersGrid->setObjectName("layersGrid");
        layersGrid->setContentsMargins(0, 0, 0, 0);
        layersText = new QLabel(centralwidget);
        layersText->setObjectName("layersText");
        layersText->setGeometry(QRect(730, 230, 71, 16));
        layersText->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        frameTimelineFrame = new QFrame(centralwidget);
        frameTimelineFrame->setObjectName("frameTimelineFrame");
        frameTimelineFrame->setGeometry(QRect(10, 500, 711, 91));
        frameTimelineFrame->setStyleSheet(QString::fromUtf8("\n"
" border-radius: 5px;\n"
"    border: 2px ridge #fff; \n"
" "));
        frameTimelineFrame->setFrameShape(QFrame::Box);
        frameTimelineFrame->setFrameShadow(QFrame::Plain);
        frameTimelineFrame->setLineWidth(3);
        addFrameButton = new QPushButton(frameTimelineFrame);
        addFrameButton->setObjectName("addFrameButton");
        addFrameButton->setGeometry(QRect(10, 30, 41, 18));
        addFrameButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color:rgb(228, 232, 255);\n"
"border: none;"));
        frameTimelineText = new QLabel(frameTimelineFrame);
        frameTimelineText->setObjectName("frameTimelineText");
        frameTimelineText->setGeometry(QRect(10, 10, 81, 21));
        frameTimelineText->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"border: none;"));
        deleteFrameButton = new QPushButton(frameTimelineFrame);
        deleteFrameButton->setObjectName("deleteFrameButton");
        deleteFrameButton->setGeometry(QRect(50, 30, 41, 18));
        deleteFrameButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color:rgb(228, 232, 255);\n"
"border: none;"));
        moveFrameLeftButton = new QPushButton(frameTimelineFrame);
        moveFrameLeftButton->setObjectName("moveFrameLeftButton");
        moveFrameLeftButton->setGeometry(QRect(10, 50, 41, 18));
        moveFrameLeftButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color:rgb(228, 232, 255);\n"
"border: none;"));
        moveFrameRightButton = new QPushButton(frameTimelineFrame);
        moveFrameRightButton->setObjectName("moveFrameRightButton");
        moveFrameRightButton->setGeometry(QRect(50, 50, 41, 18));
        moveFrameRightButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color:rgb(228, 232, 255);\n"
"border: none;"));
        gridLayoutWidget_5 = new QWidget(frameTimelineFrame);
        gridLayoutWidget_5->setObjectName("gridLayoutWidget_5");
        gridLayoutWidget_5->setGeometry(QRect(100, 10, 601, 71));
        frameTimelineGrid = new QGridLayout(gridLayoutWidget_5);
        frameTimelineGrid->setObjectName("frameTimelineGrid");
        frameTimelineGrid->setContentsMargins(0, 0, 0, 0);
        positionFrame = new QFrame(centralwidget);
        positionFrame->setObjectName("positionFrame");
        positionFrame->setGeometry(QRect(730, 500, 221, 91));
        positionFrame->setStyleSheet(QString::fromUtf8("\n"
" border-radius: 5px;\n"
"    border: 2px ridge #fff; \n"
" "));
        positionFrame->setFrameShape(QFrame::StyledPanel);
        positionFrame->setFrameShadow(QFrame::Raised);
        xCoordText = new QLabel(positionFrame);
        xCoordText->setObjectName("xCoordText");
        xCoordText->setGeometry(QRect(10, 30, 81, 16));
        xCoordText->setStyleSheet(QString::fromUtf8("border: none;\n"
""));
        yCoordText = new QLabel(positionFrame);
        yCoordText->setObjectName("yCoordText");
        yCoordText->setGeometry(QRect(10, 50, 81, 16));
        yCoordText->setStyleSheet(QString::fromUtf8("border: none;\n"
""));
        xCpprdTextBpx = new QLineEdit(positionFrame);
        xCpprdTextBpx->setObjectName("xCpprdTextBpx");
        xCpprdTextBpx->setGeometry(QRect(90, 30, 113, 20));
        xCpprdTextBpx->setStyleSheet(QString::fromUtf8("border:none;"));
        yCoordTextBox = new QLineEdit(positionFrame);
        yCoordTextBox->setObjectName("yCoordTextBox");
        yCoordTextBox->setGeometry(QRect(90, 50, 113, 20));
        yCoordTextBox->setStyleSheet(QString::fromUtf8("border: none;"));
        positionText = new QLabel(positionFrame);
        positionText->setObjectName("positionText");
        positionText->setGeometry(QRect(10, 10, 191, 16));
        positionText->setStyleSheet(QString::fromUtf8("border: none;\n"
"text-align: center;"));
        segFaultLogo = new QLabel(centralwidget);
        segFaultLogo->setObjectName("segFaultLogo");
        segFaultLogo->setGeometry(QRect(10, 10, 81, 31));
        segFaultLogo->setStyleSheet(QString::fromUtf8("   text-align: center;\n"
"    font-weight: bold;\n"
"    font-size: 16px;"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 968, 21));
        menubar->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(2, 2, 2);"));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName("menuEdit");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuHelp->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        canvas->setText(QString());
        ToolsGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Tools", nullptr));
        EraserButton->setText(QString());
        PencilButton->setText(QString());
        ColorPaletteButton->setText(QString());
        pencilSizeText->setText(QCoreApplication::translate("MainWindow", "Pencil Size", nullptr));
        EraserSizeText->setText(QCoreApplication::translate("MainWindow", "Eraser Size", nullptr));
        currentColorDisplay->setText(QString());
        currentColorText->setText(QCoreApplication::translate("MainWindow", "Color", nullptr));
        previewLabel->setText(QString());
        playAnimationButton->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
        stopAnimationButton->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        currentLayerText->setText(QCoreApplication::translate("MainWindow", "Current Frame", nullptr));
        previewLableText->setText(QCoreApplication::translate("MainWindow", "Preview ", nullptr));
        addLayer->setText(QCoreApplication::translate("MainWindow", "Add Layer", nullptr));
        removeLayer->setText(QCoreApplication::translate("MainWindow", "Remove Layer", nullptr));
        layersText->setText(QCoreApplication::translate("MainWindow", "Layers", nullptr));
        addFrameButton->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        frameTimelineText->setText(QCoreApplication::translate("MainWindow", "Frame Timeline", nullptr));
        deleteFrameButton->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        moveFrameLeftButton->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
        moveFrameRightButton->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        xCoordText->setText(QCoreApplication::translate("MainWindow", "X Coordinate:", nullptr));
        yCoordText->setText(QCoreApplication::translate("MainWindow", "Y Coordinate:", nullptr));
        positionText->setText(QCoreApplication::translate("MainWindow", "Position", nullptr));
        segFaultLogo->setText(QCoreApplication::translate("MainWindow", "SEG FAULT", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
