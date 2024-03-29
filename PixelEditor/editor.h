#ifndef EDITOR_H
#define EDITOR_H

#include "spritemodel.h"

#include <QObject>

class Editor : public QObject
{
	Q_OBJECT

public: // methods
	explicit Editor(QObject *parent = nullptr);
	~Editor();

public slots:
	void createNewSprite();
	void setPixel(int x, int y, QColor color);

	void serializeSprite(const QString &filename = "");
	void deserializeSprite(const QString &filename = "");

signals:
	void spriteCreated(const QImage &image, int width, int height);
	void pixelSet(int x, int y, QColor color);

	void filenameNeeded();

private:
	static const int SPRITE_WIDTH_DEFAULT = 32;
	static const int SPRITE_HEIGHT_DEFAULT = 64;

	Sprite *sprite;
	QString saveFilepath;

};

#endif // EDITOR_H
