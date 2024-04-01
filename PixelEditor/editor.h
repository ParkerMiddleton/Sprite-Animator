#ifndef EDITOR_H
#define EDITOR_H

#include "spritemodel.h"

#include <functional>

class Editor : public QObject
{
	Q_OBJECT

public:
	explicit Editor(QObject *parent = nullptr);
	~Editor();

public slots:
	void paintAt(int x, int y);

	void createNewSprite();
	void serializeSprite(const QString &filename);
	void deserializeSprite(const QString &filename);

	void setupCreateNewSprite();
	void setupOpenSprite();

	void selectFrame(int frameIndex);
	void addNewFrame();
	void removeFrame();

	void moveFrameLeft();
	void moveFrameRight();

	void selectLayer(int layerIndex);
	void addNewLayer();
	void removeLayer();

	void setAnimationFramerate(int fps);
	void playAnimation();
	void stopAnimation();

	void setDrawingColor(QColor color);
	void setBrushEnabled();
	void setEraserEnabled();

	void setBrushSize(int size);
	void setEraserSize(int size);

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
	enum class Tool { None, Brush, Eraser };

	static const int SPRITE_WIDTH_DEFAULT = 70;
	static const int SPRITE_HEIGHT_DEFAULT = 50;

	std::function<void(Editor*, int)> animationTimerLambda;

	Sprite *sprite;
	QString currentSavePath;
	QString currentSaveName;
	bool isSpriteSaved;

	bool isAnimationPlaying;
	int frameDuration;

	Tool currentTool;
	QColor drawingColor;

	int brushSize;
	int eraserSize;

	void setIsSpriteSaved(bool state);
	void splitFilename(const QString &filename, QString &path, QString &name);
	void emitNewSpriteSignals();

};

#endif // EDITOR_H
