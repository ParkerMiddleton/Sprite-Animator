#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
//#include "framewindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    FrameWindow *fw = ui->label;
    colorDialog = new QColorDialog();

    //Window title
    setWindowTitle("Segmentation Fault Pixel Editor");
    //Color Palette Button Image
    QPixmap palettePixmap(":/Images/artistpaletteicon.jpg");
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

    //VIEW -----> MODEL
    connect(ui->ColorPaletteButton,&QPushButton::clicked,this,&MainWindow::on_colorPicker_clicked);
    connect(this->colorDialog, &QColorDialog::colorSelected, this, &MainWindow::handleColorSelected);

    connect(this, &MainWindow::colorChanged, fw, &FrameWindow::setDrawingColor);

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

    /**Model to View**/
    connect(fw,
            &FrameWindow::informViewOfPencilEnabled,
            ui->PencilButton,
            &QPushButton::setEnabled);
}

void MainWindow::handleColorSelected(const QColor &color) {
    //qDebug() << color;
    //emit colorChanged(color);
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

