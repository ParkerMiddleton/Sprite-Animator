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

	void playAnimation();
	void stopAnimation();

	void setBrushSize(int size);

signals:
	void newSprite(int framesCount);
	void newSpriteSize(int width, int height);
	void newFrameSelection(int layersCount);
	void displayDataUpdated(const QPixmap &displayData);
	void animationDisplayDataUpdated(const QPixmap &displayData);

	void spriteSaveStatusChanged(const QString &spriteName, bool isModified);

	void readyCreateNewSprite(bool askUserToSave);
	void readyOpenSprite(bool askUserToSave);
	void needSaveFilenameToSerialize();

	void animationPlayerToggled();

private:
	static const int SPRITE_WIDTH_DEFAULT = 70;
	static const int SPRITE_HEIGHT_DEFAULT = 50;

	std::function<void(Editor*,
					   QList<std::reference_wrapper<const QPixmap>>,
					   int,
					   int)> animationTimerLambda;

	Sprite *sprite;
	QString currentSavePath;
	QString currentSaveName;
	bool isSpriteSaved;

	bool isAnimationPlaying;
	int brushSize;

	void setIsSpriteSaved(bool state);
	void splitFilename(const QString &filename, QString &path, QString &name);
	void emitNewSpriteSignals();

};

#endif // EDITOR_H
