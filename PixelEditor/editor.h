#ifndef EDITOR_H
#define EDITOR_H

#include "spritemodel.h"

class Editor : public QObject
{
	Q_OBJECT

public:
	explicit Editor(QObject *parent = nullptr);
	~Editor();

public slots:
	void createNewSprite();
	void setPixel(int x, int y, QColor color);

	void serializeSprite(const QString &filename);
	void deserializeSprite(const QString &filename);

	void setupCreateNewSprite();
	void setupOpenSprite();

	void addNewFrame();
    void removeFrame();
    void addNewLayer();
    void removeLayer();
	void selectFrame(int frameIndex);
    void selectLayer(int layerIndex);

signals:
	void spriteLoaded(const QImage &image, int width, int height);
	void pixelSet(int x, int y, QColor color);

	void spriteSaveStatusChanged(const QString &spriteName, bool isModified);

	void readyCreateNewSprite(bool askUserToSave);
	void readyOpenSprite(bool askUserToSave);
	void needSaveFilenameToSerialize();

	void frameChanged(const QImage &image);

private:
	static const int SPRITE_WIDTH_DEFAULT = 32;
	static const int SPRITE_HEIGHT_DEFAULT = 64;

	Sprite *sprite;
	QString currentSavePath;
	QString currentSaveName;
	bool isSpriteSaved;

	void setIsSpriteSaved(bool state);
	void splitFilename(const QString &filename, QString &path, QString &name);

};

#endif // EDITOR_H
