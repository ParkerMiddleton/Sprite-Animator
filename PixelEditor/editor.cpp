#include "editor.h"
#include <QDebug>

Editor::Editor(QObject *parent)
	: QObject{parent}
	, sprite{nullptr}
	, currentSavePath{""}
	, currentSaveName{""}
	, isSpriteSaved{true}
{

}

Editor::~Editor()
{
	delete sprite;
}

void Editor::createNewSprite()
{
	sprite = new Sprite(SPRITE_WIDTH_DEFAULT, SPRITE_HEIGHT_DEFAULT);
	currentSavePath = "";
	currentSaveName = "UNTITLED";
	this->setIsSpriteSaved(true);

	this->emitSpriteLoadedSignals();
}

void Editor::setPixel(int x, int y, QColor color)
{
	sprite->currentFrame().currentLayer().drawColor(x, y, color);
	this->setIsSpriteSaved(false);

	emit pixelSet(x, y, sprite->currentFrame().getMergedPixel(x, y));
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

	this->setIsSpriteSaved(true);
	this->emitSpriteLoadedSignals();
}

void Editor::setupCreateNewSprite()
{
	emit readyCreateNewSprite(!isSpriteSaved);
}

void Editor::setupOpenSprite()
{
	emit readyOpenSprite(!isSpriteSaved);
}

void Editor::moveFrameLeft()
{
	this->sprite->moveCurrentFrameLeft();
	emit displayImageChanged(sprite->currentFrame().getMergedLayerImage(), false);
}

void Editor::moveFrameRight()
{
	this->sprite->moveCurrentFrameRight();
	emit displayImageChanged(sprite->currentFrame().getMergedLayerImage(), false);
}

void Editor::selectFrame(int frameIndex)
{
	QTextStream(stdout) << "\nFrame selected: " << frameIndex;
	sprite->selectFrame(frameIndex);
	emit displayImageChanged(sprite->currentFrame().getMergedLayerImage(), false);
	emit newFrameSelection(sprite->currentFrame().getLayerCount());
}

void Editor::addNewFrame()
{
	sprite->addFrame();
	emit displayImageChanged(sprite->currentFrame().getMergedLayerImage(), false);
	emit newFrameSelection(sprite->currentFrame().getLayerCount());
}

void Editor::removeFrame()
{
	sprite->removeCurrentFrame();
	emit displayImageChanged(sprite->currentFrame().getMergedLayerImage(), false);
	emit newFrameSelection(sprite->currentFrame().getLayerCount());
}

void Editor::selectLayer(int layerIndex)
{
	QTextStream(stdout) << "\nLayer selected: " << layerIndex;
	sprite->currentFrame().selectLayer(layerIndex);
	emit displayImageChanged(sprite->currentFrame().getMergedLayerImage(), false);
}

void Editor::addNewLayer()
{
	sprite->currentFrame().addLayer();
	emit displayImageChanged(sprite->currentFrame().getMergedLayerImage(), false);
}

void Editor::removeLayer()
{
	sprite->currentFrame().removeCurrentLayer();
	emit displayImageChanged(sprite->currentFrame().getMergedLayerImage(), false);
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

void Editor::emitSpriteLoadedSignals()
{
	emit spriteLoaded(sprite->getFrameCount());
	emit newFrameSelection(sprite->currentFrame().getLayerCount());
	emit displayImageChanged(sprite->currentFrame().getMergedLayerImage(), true);
	emit spriteSaveStatusChanged(currentSaveName, false);
}
