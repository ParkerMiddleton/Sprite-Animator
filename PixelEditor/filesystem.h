/**
 * This is the header for the serializer
 * @authors Egor Chesnokov and Aditya Mukerjee
 */
#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QString>

#include "spritemodel.h"

class FileSystem
{
public:
	FileSystem();

	bool serializeSprite(Sprite *spriteAddress, const QString &spriteName, const QString &spriteFilePath);
	bool deserializeSprite(Sprite &sprite, const QString &spriteFilePath = "");

private:
	QString currentSpritePath;

};

#endif // FILESYSTEM_H
