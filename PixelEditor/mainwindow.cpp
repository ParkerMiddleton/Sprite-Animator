#include "mainwindow.h"

#include "ui_mainwindow.h"
#include "previewwindow.h"
#include "viewport.h"

#include "editormodel.h"

MainWindow::MainWindow(EditorModel *editor, QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, editor(editor)
{
	ui->setupUi(this);

	Viewport *vp = ui->viewport;
	PreviewWindow *pw = ui->previewLabel;
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

	/* MODEL <--> VIEW */

	connect(this,
			&MainWindow::spriteCreationRequested,
			editor,
			&EditorModel::createNewSprite);

	connect(editor,
			&EditorModel::spriteCreated,
			vp,
			&Viewport::setupSprite);

	connect(vp,
			&Viewport::colorPainted,
			editor,
			&EditorModel::setPixel);

	connect(editor,
			&EditorModel::pixelSet,
			vp,
			&Viewport::setPixelColor);

	/* VIEW <--> VIEW */

	//On color palette button clicked, choose a color
	connect(ui->ColorPaletteButton,
			&QPushButton::clicked,
			this,
			&MainWindow::changeColor);


	// Send chosen color to the frame window to be used
	connect(this,
			&MainWindow::colorChanged,
			vp,
			&Viewport::setDrawingColor);

	// enable and disable brush
	connect(ui->PencilButton,
			&QPushButton::clicked,
			vp,
			&Viewport::setBrushEnabled);

	// enable and disable eraser
	connect(ui->EraserButton,
			&QPushButton::clicked,
			vp,
			&Viewport::setEraserEnabled);

	// frame window tells main that penicl button is to be disabled or enabled.
	connect(vp,
			&Viewport::informViewOfPencilEnabled,
			ui->PencilButton,
			&QPushButton::setEnabled);


	//Send pixmap data to the preview window to mirror drawing.
	connect(vp,
			&Viewport::sendPixmapData,
			pw,
			&PreviewWindow::recievePixmapData);
}


void MainWindow::changeColor()
{
	// The colorSelected signal will now be connected to the handleColorSelected slot.
	currentColor = QColorDialog::getColor(Qt::black, this, tr("Select Color"));

	emit colorChanged(currentColor);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionOpenSprite_triggered()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open"), "", tr("Sprite (*.ssp)"));
	emit openClicked(QFileInfo(filename));
}

void MainWindow::on_actionSaveSprite_triggered()
{
	emit saveClicked();
}

void MainWindow::on_actionSaveSpriteAs_triggered()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Save as"), "", tr("Sprite (*.ssp)"));
	emit saveAsClicked(QFileInfo(filename));
}

void MainWindow::on_actionNew_triggered()
{
	emit spriteCreationRequested();
}

