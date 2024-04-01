#include "editor.h"

Editor::Editor(QObject *parent)
	: QObject{parent}

	, sprite{nullptr}
	, currentSavePath{""}
	, currentSaveName{""}
	, isSpriteSaved{true}

	, isAnimationPlaying{false}
	, frameDuration{0}

	, currentTool{Tool::None}
	, drawingColor{Qt::black}

	, brushSize{1}
	, eraserSize{1}
{
	animationTimerLambda = [](Editor *editor, int currentPlayedFrame)
	{
		if (currentPlayedFrame == editor->sprite->getFrameCount() - 1)
			currentPlayedFrame = -1;

		emit editor->animationDisplayDataUpdated(editor->sprite->getFrame(++currentPlayedFrame).getDisplayData());

		if (editor->isAnimationPlaying)
			QTimer::singleShot(editor->frameDuration, editor, std::bind(editor->animationTimerLambda, editor, currentPlayedFrame));
	};
}

Editor::~Editor()
{
	delete sprite;
}

void Editor::paintAt(int x, int y)
{
	if (currentTool == Tool::Brush)
		sprite->currentFrame().paintAt(x, y, drawingColor, brushSize);
	else if (currentTool == Tool::Eraser)
		sprite->currentFrame().paintAt(x, y, Qt::transparent, eraserSize);

	this->setIsSpriteSaved(false);
	emit displayDataUpdated(sprite->currentFrame().getDisplayData());
}

void Editor::createNewSprite()
{
	sprite = new Sprite(SPRITE_WIDTH_DEFAULT, SPRITE_HEIGHT_DEFAULT);
	currentSavePath = "";
	currentSaveName = "UNTITLED";
	frameDuration = 1000 / sprite->getFPS();
	this->setIsSpriteSaved(true);

	this->emitNewSpriteSignals();
}

void Editor::serializeSprite(const QString &filename)
{
	QString saveFilepath, saveName;

	if (filename.isEmpty())
	{
		if (currentSaveName.isEmpty() || currentSavePath.isEmpty())
		{
			emit needSaveFilenameToSerialize();

			return;
		}

		saveFilepath = currentSavePath;
		saveName = currentSaveName;
	}
	else
	{
		this->splitFilename(filename, saveFilepath, saveName);
	}

	QFile jsonFile(saveFilepath + saveName);

	if (!jsonFile.open(QIODevice::WriteOnly))
	{
		qWarning("Unable to open file.");
		return;
	}

	QJsonObject jsonSprite = sprite->toJson();
	jsonFile.write(QJsonDocument(jsonSprite).toJson());

	if (!filename.isEmpty())
	{
		currentSaveName = saveName;
		currentSavePath = saveFilepath;
	}

	this->setIsSpriteSaved(true);
	emit spriteSaveStatusChanged(currentSaveName, false);
}

void Editor::deserializeSprite(const QString &filename)
{
	QString saveFilepath, saveName;
	this->splitFilename(filename, saveFilepath, saveName);

	QFile jsonFile(saveFilepath + saveName);

	if (!jsonFile.open(QIODevice::ReadOnly))
	{
		qWarning("Unable to open file.");
		return;
	}

	QByteArray jsonData = jsonFile.readAll();
	QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));

	Sprite *newSprite = Sprite::fromJson(jsonDoc.object());

	if (!newSprite)
	{
		qWarning("Unable to deserialize.");
		return;
	}

	delete sprite;
	sprite = newSprite;

	currentSaveName = saveName;
	currentSavePath = saveFilepath;
	frameDuration = 1000 / sprite->getFPS();

	this->setIsSpriteSaved(true);
	this->emitNewSpriteSignals();
}

void Editor::setupCreateNewSprite()
{
	emit readyCreateNewSprite(!isSpriteSaved);
}

void Editor::setupOpenSprite()
{
	emit readyOpenSprite(!isSpriteSaved);
}

void Editor::selectFrame(int frameIndex)
{
	sprite->selectFrame(frameIndex);
	QTextStream(stdout) << "\nCurrent Frame Index: " << sprite->getCurrentFrameIndex();

	emit newFrameSelection(sprite->currentFrame().getLayerCount());
	emit displayDataUpdated(sprite->currentFrame().getDisplayData());
}

void Editor::addNewFrame()
{
	sprite->addFrame();
	QTextStream(stdout) << "\nCurrent Frame Index: " << sprite->getCurrentFrameIndex();

	this->setIsSpriteSaved(false);
	emit newFrameSelection(sprite->currentFrame().getLayerCount());
	emit displayDataUpdated(sprite->currentFrame().getDisplayData());
}

void Editor::removeFrame()
{
	sprite->removeCurrentFrame();
	QTextStream(stdout) << "\nCurrent Frame Index: " << sprite->getCurrentFrameIndex();

	this->setIsSpriteSaved(false);
	emit newFrameSelection(sprite->currentFrame().getLayerCount());
	emit displayDataUpdated(sprite->currentFrame().getDisplayData());
}

void Editor::moveFrameLeft()
{
	sprite->moveCurrentFrameLeft();
	QTextStream(stdout) << "\nCurrent Frame Index: " << sprite->getCurrentFrameIndex();

	this->setIsSpriteSaved(false);
	emit displayDataUpdated(sprite->currentFrame().getDisplayData());
}

void Editor::moveFrameRight()
{
	sprite->moveCurrentFrameRight();
	QTextStream(stdout) << "\nCurrent Frame Index: " << sprite->getCurrentFrameIndex();

	this->setIsSpriteSaved(false);
	emit displayDataUpdated(sprite->currentFrame().getDisplayData());
}

void Editor::selectLayer(int layerIndex)
{
	sprite->currentFrame().selectLayer(layerIndex);
	QTextStream(stdout) << "\nCurrent Layer Index: " << sprite->currentFrame().getCurrentLayerIndex();

	emit displayDataUpdated(sprite->currentFrame().getDisplayData());
}

void Editor::addNewLayer()
{
	sprite->currentFrame().addLayer();
	QTextStream(stdout) << "\nCurrent Layer Index: " << sprite->currentFrame().getCurrentLayerIndex();

	this->setIsSpriteSaved(false);
	emit displayDataUpdated(sprite->currentFrame().getDisplayData());
}

void Editor::removeLayer()
{
	sprite->currentFrame().removeCurrentLayer();
	QTextStream(stdout) << "\nCurrent Layer Index: " << sprite->currentFrame().getCurrentLayerIndex();

	this->setIsSpriteSaved(false);
	emit displayDataUpdated(sprite->currentFrame().getDisplayData());
}

void Editor::setAnimationFramerate(int fps)
{
    qDebug() << fps;
	frameDuration = 1000 / fps;
	sprite->setFPS(fps);

	this->setIsSpriteSaved(false);
}

void Editor::playAnimation()
{
    qDebug() << sprite->getFPS();
	isAnimationPlaying = true;
	emit animationPlayerToggled();

	QTimer::singleShot(frameDuration, this, std::bind(animationTimerLambda, this, -1));
}

void Editor::stopAnimation()
{
	isAnimationPlaying = false;

	emit animationPlayerToggled();
	emit displayDataUpdated(sprite->currentFrame().getDisplayData());
}

void Editor::setBrushEnabled()
{
	currentTool = Tool::Brush;
}

void Editor::setEraserEnabled()
{
	currentTool = Tool::Eraser;
}

void Editor::setDrawingColor(QColor color)
{
	drawingColor = color;
}

void Editor::setBrushSize(int size)
{
	brushSize = size;
}

void Editor::setEraserSize(int size)
{
	eraserSize = size;
}

void Editor::setIsSpriteSaved(bool state)
{
	if (!state && isSpriteSaved)
	{
		isSpriteSaved = state;
		emit spriteSaveStatusChanged(currentSaveName, true);
	}
	else if (state && !isSpriteSaved)
	{
		isSpriteSaved = state;
		emit spriteSaveStatusChanged(currentSaveName, false);
	}
}

void Editor::splitFilename(const QString &filename, QString &path, QString &name)
{
	QFileInfo info(filename);
	path = info.dir().path() + "/";
	name = info.fileName();
}

void Editor::emitNewSpriteSignals()
{
	emit newSprite(sprite->getFrameCount());
	emit newSpriteSize(sprite->getWidth(), sprite->getHeight());
	emit newFrameSelection(sprite->currentFrame().getLayerCount());
	emit displayDataUpdated(sprite->currentFrame().getDisplayData());
	emit spriteSaveStatusChanged(currentSaveName, false);
}
