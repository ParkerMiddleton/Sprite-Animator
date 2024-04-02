#ifndef EDITOR_H
#define EDITOR_H

#include "spritemodel.h"
#include <functional>
/**
 * @authors Tommy Heimer, Egor Chesnokov, Koby Dato, Parker Middleton, Aditya Mukerjee, Charles WolfGramm.
 *
 * @version 1.0
 * @date 4/1/2024
 */

///
/// \brief The Editor class Acts as the main canvas for editing frames.
///
class Editor : public QObject
{
	Q_OBJECT

public:
	explicit Editor(QObject *parent = nullptr);
	~Editor();

public slots:

	void paintAt(int x, int y);


	void createNewSprite(int width, int height);

	void serializeSprite(const QString &filename);
	void deserializeSprite(const QString &filename);

    ///sprite createion and loading
	void setupCreateNewSprite();
	void setupOpenSprite();

    ///frame selection
	void selectFrame(int frameIndex);

    /// rame removal and adding
	void addNewFrame();
	void removeFrame();


    ///Handles frame order manipulation
	void moveFrameLeft();
	void moveFrameRight();

    ///Handles layer manipulaiton
	void selectLayer(int layerIndex);
	void addNewLayer();
	void removeLayer();

    /// sets frame rate
	void setAnimationFramerate(int fps);

    /// starts start and stop for animations
	void playAnimation();
	void stopAnimation();

    /// setting a color
	void setDrawingColor(QColor color);

    /// brush/eraser selection
	void setBrushEnabled();
	void setEraserEnabled();

    /// brush/eraser size manipulation
    void setBrushSize(int size);
	void setEraserSize(int size);

    /// duplicates frame
    void setDuplicateFrame(bool duplicate);

signals:

    /// new sprite
	void newSprite(int framesCount);

    /// set size of sprite
	void newSpriteSize(int width, int height);
    /// frame selection
	void newSpriteFramerate(int fps);
	void newFrameSelection(int layersCount);

    /// display data
	void displayDataUpdated(const QPixmap &displayData);
	void animationDisplayDataUpdated(const QPixmap &displayData);

    /// save sprite
	void spriteSaveStatusChanged(const QString &spriteName, bool isModified);


    /// ready sprites
	void readyCreateNewSprite(bool askUserToSave);
	void readyOpenSprite(bool askUserToSave);
	void needSaveFilenameToSerialize();

	void animationPlayerSetEnabled(bool state);

private:
	enum class Tool { None, Brush, Eraser };

	std::function<void(Editor*, int)> animationTimerLambda;

	Sprite *sprite;
	QString currentSavePath;
	QString currentSaveName;
	bool isSpriteSaved;    
    bool duplicateFrame;

	bool isAnimationPlaying;
	int frameDuration;

	Tool currentTool;
	QColor drawingColor;

	int brushSize;
	int eraserSize;
	void setIsSpriteSaved(bool state);
	void setIsAnimationPlaying(bool state);

	void splitFilename(const QString &filename, QString &path, QString &name);
	void emitNewSpriteSignals();


};

#endif // EDITOR_H
