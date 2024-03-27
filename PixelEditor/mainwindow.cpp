#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "previewwindow.h"
#include <QPainter>
//#include "framewindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    FrameWindow *fw = ui->canvas;
    PreviewWindow *pw = ui->previewLabel;
    FrameTimeline *ft = ui->frameTimeline;
     colorDialog = new QColorDialog();

    //Window title
    setWindowTitle("Seg Fault Sprite Editor");

    //Color Palette Button Image
    QPixmap palettePixmap(":/Images/pal2.png");
    QSize palettePixmapSize(50,50);
    ui->ColorPaletteButton->setIcon(palettePixmap);
    ui->ColorPaletteButton->setIconSize(palettePixmapSize);

    //Pencil Button Image
    QPixmap pencilPixmap(":/Images/pencil.png");
    QSize pencilImageSize(50,50);
    ui->PencilButton->setIcon(pencilPixmap);
    ui->PencilButton->setIconSize(pencilImageSize);

    //Eraser Button Image
    QPixmap eraserPixmap(":/Images/eraser.png");
    QSize eraserImageSize(40,40);
    ui->EraserButton->setIcon(eraserPixmap);
    ui->EraserButton->setIconSize(eraserImageSize);

    //VIEW -----> VIEW
    //On color palette button clicked, chose a color
    connect(ui->ColorPaletteButton,
            &QPushButton::clicked,
            this,
            &MainWindow::on_colorPicker_clicked);


    // Send chosen color to the frame window to be used
    connect(this,
            &MainWindow::colorChanged,
            fw,
            &FrameWindow::setDrawingColor);

    // enable and disable brush
    connect(ui->PencilButton,
            &QPushButton::clicked,
            fw,
            &FrameWindow::setBrushEnabled);

    // enable and disable eraser
    connect(ui->EraserButton,
            &QPushButton::clicked,
            fw,
            &FrameWindow::setEraserEnabled);

    // frame window tells main that penicl button is to be disabled or enabled.
    connect(fw,
            &FrameWindow::informViewOfPencilEnabled,
            ui->PencilButton,
            &QPushButton::setEnabled);


    //Send pixmap data to the preview window to mirror drawing.
    connect(fw,
            &FrameWindow::sendPixmapData,
            pw,
            &PreviewWindow::recievePixmapData);

    //adds a frame to the timeline
    connect(ui->addFrameButton,
            &QPushButton::clicked,
            ft,
            &FrameTimeline::addFrame);
}


void MainWindow::on_colorPicker_clicked()
{
    // The colorSelected signal will now be connected to the handleColorSelected slot.
    QColor selectedColor = QColorDialog::getColor(Qt::black, this, tr("Select Color"));
    emit colorChanged(selectedColor);
    currentColor = selectedColor;
}

MainWindow::~MainWindow()
{
    delete ui;
}
