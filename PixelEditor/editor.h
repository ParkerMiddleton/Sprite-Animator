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
	void paintAt(int x, int y, QColor color);

	void serializeSprite(const QString &filename);
	void deserializeSprite(const QString &filename);

	void setupCreateNewSprite();
	void setupOpenSprite();

	void moveFrameLeft();
	void moveFrameRight();

	void selectFrame(int frameIndex);
	void addNewFrame();
	void removeFrame();

	void selectLayer(int layerIndex);
	void addNewLayer();
	void removeLayer();

signals:
	void newSprite(int framesCount);
	void newSpriteSize(int width, int height);
	void newFrameSelection(int layersCount);
	void displayDataUpdated(const QPixmap &displayData);

	void spriteSaveStatusChanged(const QString &spriteName, bool isModified);

	void readyCreateNewSprite(bool askUserToSave);
	void readyOpenSprite(bool askUserToSave);
	void needSaveFilenameToSerialize();

private:
	static const int SPRITE_WIDTH_DEFAULT = 32;
	static const int SPRITE_HEIGHT_DEFAULT = 64;

	Sprite *sprite;
	QString currentSavePath;
	QString currentSaveName;
	bool isSpriteSaved;

	void setIsSpriteSaved(bool state);
	void splitFilename(const QString &filename, QString &path, QString &name);
	void emitNewSpriteSignals();

};

#endif // EDITOR_H
