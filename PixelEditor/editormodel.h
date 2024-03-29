#ifndef EDITORMODEL_H
#define EDITORMODEL_H

#include "sprite.h"

#include <QObject>

/* for-later:
 * @authors
 * Aditya Mukerjee
 * Charles Wolfgramm-Vave
 * Koby Dato
 * Parker Middleton
 * Tommy Heimer
 * Egor Chesnokov
*/

class EditorModel : public QObject
{
	Q_OBJECT

public: // methods
	explicit EditorModel(QObject *parent = nullptr);
	~EditorModel();

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

#endif // EDITORMODEL_H
