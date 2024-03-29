#include "editor.h"

Editor::Editor(QObject *parent)
	: QObject{parent}
	, sprite{nullptr}
	, saveFilepath{""}
{

}

Editor::~Editor()
{
	delete sprite;
}

void Editor::createNewSprite()
{
	sprite = new Sprite(SPRITE_WIDTH_DEFAULT, SPRITE_HEIGHT_DEFAULT);
	emit spriteCreated(sprite->getCurrentFrame().getMergedLayerImage(), sprite->getWidth(), sprite->getHeight());
}

void Editor::setPixel(int x, int y, QColor color)
{
	sprite->getCurrentFrame().getCurrentLayer().drawColor(x, y, color);

	emit pixelSet(x, y, sprite->getCurrentFrame().getMergedPixel(x, y));
}

void Editor::serializeSprite(const QString &filename)
{
	/*if (sprite.getName().isEmpty())
	{
		emit filenameNeeded();
		return;
	}
	else if (!filename.isEmpty()) // FIXME
	{
		QFileInfo info(filename);
		QString name = info.fileName();
		QDir dir = info.dir();
		sprite.setName(name.left(name.lastIndexOf(".")));
		saveFilepath = dir.path() + "/";
	}*/

	QFile jsonFile(saveFilepath + sprite->getName());

	if (jsonFile.open(QIODevice::ReadOnly))
	{
		qWarning("Unable to open file.");
		return;
	}

	QByteArray jsonData = jsonFile.readAll();
	QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));

	sprite = Sprite::fromJson(jsonDoc.object());
}

void Editor::deserializeSprite(const QString &filename)
{
	/*QFileInfo info(filename);
	QString name = info.fileName();
	QDir dir = info.dir();
	sprite.setName(name.left(name.lastIndexOf(".")));
	saveFilepath = dir.path() + "/";

	if (saveFilepath.isEmpty())
	{
		if (saveFilePath.isEmpty())
			return false;
	}
	else
	{
		saveFilepath = spriteFilePath;
	}*/

	QFile jsonFile(saveFilepath + sprite->getName());

	if (jsonFile.open(QIODevice::WriteOnly))
	{
		qWarning("Unable to open file.");
		return;
	}

	QJsonObject jsonSprite = sprite->toJson();
	jsonFile.write(QJsonDocument(jsonSprite).toJson());
}
