#include "filesystem.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

FileSystem::FileSystem()
	: currentSpriteFilePath("")
{

}

bool FileSystem::serializeSprite(Sprite *spriteAddress, const QString &spriteName, const QString &spriteFilePath)
{
	QFile jsonFile(spriteFilePath + spriteName);

	if (jsonFile.open(QIODevice::ReadOnly))
	{
		qWarning("Unable to open file.");
		return false;
	}

	currentSpriteFilePath = spriteFilePath;

	QByteArray jsonData = jsonFile.readAll();
	QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));

	spriteAddress = Sprite::fromJson(jsonDoc.object());

	if (spriteAddress)
		return true;
	else
		return false;
}

bool FileSystem::deserializeSprite(Sprite &sprite, const QString &spriteFilePath)
{
	if (spriteFilePath.isEmpty())
	{
		if (currentSpriteFilePath.isEmpty())
			return false;
	}
	else
	{
		currentSpriteFilePath = spriteFilePath;
	}

	QFile jsonFile(currentSpriteFilePath + sprite.getName());

	if (jsonFile.open(QIODevice::WriteOnly))
	{
		qWarning("Unable to open file.");
		return false;
	}

	QJsonObject jsonSprite = sprite.toJson();
	jsonFile.write(QJsonDocument(jsonSprite).toJson());

	return true;
}
