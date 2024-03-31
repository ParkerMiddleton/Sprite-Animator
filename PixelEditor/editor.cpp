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

	this->emitNewSpriteSignals();
}

void Editor::paintAt(int x, int y, QColor color)
{
	Frame &currentFrame = sprite->currentFrame();
	currentFrame.paintAt(x, y, color);

	this->setIsSpriteSaved(false);
	emit displayDataUpdated(sprite->currentFrame().getDisplayData());
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
