#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "editor.h"

MainWindow::MainWindow(Editor *editor, QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, editor(editor)
{
	ui->setupUi(this);

	vp = ui->viewport;
	pw = ui->previewLabel;
	ft = ui->frameTimeline;
	lt = ui->layerPlacer;

	//Window title
	this->setWindowTitle("Pixel Editor");

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

	//Pencil Button Image
	QPixmap eraserPixmap(":/Images/eraser.png");
	QSize eraserImageSize(50,50);
	ui->EraserButton->setIcon(eraserPixmap);
	ui->EraserButton->setIconSize(eraserImageSize);

	this->createActions();
	this->createMenus();

	connect(vp, &Viewport::mouseMoved, this, [this](QPoint pos) {
		ui->coordInfoText->setText(QString::number(pos.x()) + ", " + QString::number(pos.y()));
	});

	connect(vp, &Viewport::spriteSizeChanged, this, [this](QPoint size) {
		ui->sizeInfoText->setText(QString::number(size.x()) + "x" + QString::number(size.y()));
	});

	/*== TIMELINE PANEL ==*/

	connect(ui->addFrameButton, &QPushButton::clicked
			, ft, &TimelinePanel::addFrame);

	connect(ui->deleteFrameButton, &QPushButton::clicked
			, ft, &TimelinePanel::removeFrame);

	connect(ft, &TimelinePanel::frameButtonSelected
			, editor, &Editor::selectFrame);

	connect(ui->addFrameButton, &QPushButton::clicked
			, editor, &Editor::addNewFrame);

	connect(ui->deleteFrameButton, &QPushButton::clicked
			, editor, &Editor::removeFrame);

	connect(editor, &Editor::newSprite
			, ft, &TimelinePanel::setupFrameButtons);

	connect(ui->moveFrameLeftButton, &QPushButton::clicked
			, editor, &Editor::moveFrameLeft);

	connect(ui->moveFrameRightButton, &QPushButton::clicked
			, editor, &Editor::moveFrameRight);

	/*== LAYERS PANEL ==*/

	connect(ui->addLayerButton, &QPushButton::clicked
			, lt, &LayersPanel::addLayer);

	connect(ui->removeLayerButton, &QPushButton::clicked
			, lt, &LayersPanel::removeLayer);

	connect(lt, &LayersPanel::layerButtonSelected
			, editor, &Editor::selectLayer);

	connect(ui->addLayerButton, &QPushButton::clicked
			, editor, &Editor::addNewLayer);

	connect(ui->removeLayerButton, &QPushButton::clicked
			, editor, &Editor::removeLayer);

	connect(editor, &Editor::newFrameSelection
			, lt, &LayersPanel::setupLayerButtons);

	/*====== MODEL <--> VIEW ======*/

	// this <--> Editor
	connect(this, &MainWindow::newSpriteRequested
			, editor, &Editor::createNewSprite);

	connect(this, &MainWindow::loadRequested
			, editor, &Editor::deserializeSprite);

	connect(this, &MainWindow::saveRequested
			, editor, &Editor::serializeSprite);

	connect(editor, &Editor::spriteSaveStatusChanged
			, this, &MainWindow::updateTitle);

	connect(editor, &Editor::needSaveFilenameToSerialize
			, this, &MainWindow::initializeSaveProcessWithDialogue);

	connect(editor, &Editor::readyCreateNewSprite
			, this, &MainWindow::handleCreateNewSprite);

	connect(editor, &Editor::readyOpenSprite
			, this, &MainWindow::handleOpenSprite);

	connect(editor, &Editor::newSpriteSize
			, vp, &Viewport::setupNewSpriteDisplay);

	connect(editor, &Editor::displayDataUpdated
			, vp, &Viewport::updateSpriteDisplay);

	connect(vp, &Viewport::colorPainted
			, editor, &Editor::paintAt);

	/* VIEW <--> VIEW */

	//On color palette button clicked, choose a color
	connect(ui->ColorPaletteButton, &QPushButton::clicked
			, this, &MainWindow::changeColor);

	// Send chosen color to the frame window to be used
	connect(this, &MainWindow::colorChanged
			, vp, &Viewport::setDrawingColor);

	// enable and disable brush
	connect(ui->PencilButton, &QPushButton::clicked
			, vp, &Viewport::setBrushEnabled);

	// enable and disable eraser
	connect(ui->EraserButton, &QPushButton::clicked
			, vp, &Viewport::setEraserEnabled);

	// frame window tells main that penicl button is to be disabled or enabled.
	connect(vp, &Viewport::informViewOfPencilEnabled
			, ui->PencilButton, &QPushButton::setEnabled);

    /* HIGHLIGHT BUTTON CLICKED */

    connect(ui->PencilButton, &QPushButton::clicked, this, [this]() {
        highlightButton(ui->PencilButton);
    });

    connect(ui->EraserButton, &QPushButton::clicked, this, [this]() {
        highlightButton(ui->EraserButton);
    });

    connect(ui->addFrameButton, &QPushButton::clicked, this, [this]() {
        highlightButton(ui->addFrameButton);
    });

    connect(ui->deleteFrameButton, &QPushButton::clicked, this, [this]() {
        highlightButton(ui->deleteFrameButton);
    });

    connect(ui->addLayerButton, &QPushButton::clicked, this, [this]() {
        highlightButton(ui->addLayerButton);
    });

    connect(ui->removeLayerButton, &QPushButton::clicked, this, [this]() {
        highlightButton(ui->removeLayerButton);
    });

    connect(ui->playAnimationButton, &QPushButton::clicked, this, [this]() {
        highlightButton(ui->playAnimationButton);
    });

    connect(ui->stopAnimationButton, &QPushButton::clicked, this, [this]() {
        highlightButton(ui->stopAnimationButton);
    });

	//Send pixmap data to the preview window to mirror drawing.
    connect(vp,
			&Viewport::sendPixmapData,
			pw,
            &PreviewWindow::recievePixmapData);
    //Send sprite data to the preview window
    connect(editor,
            &Editor::sendSpriteData,
            pw,
            &PreviewWindow::recieveSpriteData);

}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::changeColor()
{
    // Store the current color
    QColor previousColor = currentColor;

    // Show the color change (for example, by temporarily changing the palette button's background color)
    ui->ColorPaletteButton->setStyleSheet("background-color: white;");

    // Create a QTimer to open the color picker after a short delay
    QTimer::singleShot(200, this, [this, previousColor]() {
        // Restore the original color of the palette button
        ui->ColorPaletteButton->setStyleSheet("");

        // Open the color picker dialog with the previous color selected
        QColor newColor = QColorDialog::getColor(previousColor, this, tr("Select Color"), QColorDialog::ShowAlphaChannel);

        // Emit the signal with the new color
        emit colorChanged(newColor);
    });
}

void MainWindow::updateTitle(const QString &spriteName, bool showStar)
{
	if (showStar)
	{
		this->setWindowTitle(spriteName + "* // Pixel Editor");
	}
	else
	{
		this->setWindowTitle(spriteName + " // Pixel Editor");
	}
}

void MainWindow::handleCreateNewSprite(bool askUserToSave)
{
	if (askUserToSave)
	{
		QMessageBox::StandardButton reply;
		reply = QMessageBox::question(this, "Unsaved Changes", "You have unsaved changes. Would you like to save?",
									  QMessageBox::Yes | QMessageBox::No);

		if (reply == QMessageBox::Yes)
		{
			this->initializeSaveProcess();
		}
	}

	emit newSpriteRequested();
}

void MainWindow::handleOpenSprite(bool askUserToSave)
{
	if (askUserToSave)
	{
		QMessageBox::StandardButton reply;
		reply = QMessageBox::question(this, "Unsaved Changes", "You have unsaved changes. Would you like to save?",
									  QMessageBox::Yes | QMessageBox::No);

		if (reply == QMessageBox::Yes)
		{
			this->initializeSaveProcess();
		}
	}

	QString filename = QFileDialog::getOpenFileName(this, tr("Open"), "", tr("Sprite (*.ssp)"));

	if (!filename.isEmpty()&& !filename.isNull())
	{
		emit loadRequested(filename);
	}
}

void MainWindow::initializeSaveProcess()
{
	emit saveRequested("");
}

void MainWindow::initializeSaveProcessWithDialogue()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Save as"), "", tr("Sprite (*.ssp)"));

	if (!filename.isEmpty()&& !filename.isNull())
	{
		emit saveRequested(filename);
	}
}

void MainWindow::createActions()
{
	newAct = new QAction(tr("&New"), this);
	newAct->setShortcuts(QKeySequence::New);
	newAct->setStatusTip(tr("Create a new sprite"));
	connect(newAct, &QAction::triggered
			, editor, &Editor::setupCreateNewSprite);

	openAct = new QAction(tr("&Open"), this);
	openAct->setShortcuts(QKeySequence::Open);
	openAct->setStatusTip(tr("Open an existing sprite"));
	connect(openAct, &QAction::triggered
			, editor, &Editor::setupOpenSprite);

	saveAct = new QAction(tr("&Save"), this);
	saveAct->setShortcuts(QKeySequence::Save);
	saveAct->setStatusTip(tr("Save an opened sprite"));
	connect(saveAct, &QAction::triggered
			, this, &MainWindow::initializeSaveProcess);

	saveAsAct = new QAction(tr("&Save as"), this);
	saveAsAct->setShortcuts(QKeySequence::SaveAs);
	saveAsAct->setStatusTip(tr("Specify directory and save an opened sprite"));
	connect(saveAsAct, &QAction::triggered
			, this, &MainWindow::initializeSaveProcessWithDialogue);
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAct);
	fileMenu->addAction(openAct);
	fileMenu->addSeparator();
	fileMenu->addAction(saveAct);
	fileMenu->addAction(saveAsAct);
}

void MainWindow::highlightButton(QPushButton *button) {
    // Store the original style sheet of the button
    QString originalStyleSheet = button->styleSheet();

    // Highlight the button by changing its style temporarily
    button->setStyleSheet("background-color: white;"); // You can customize the highlighting style here

    // Create a QTimer to restore the original style after a short duration
    QTimer::singleShot(200, this, [button, originalStyleSheet]() {
        // Restore the original style sheet of the button
        button->setStyleSheet(originalStyleSheet);
    });
}
