#ifndef PREVIEWPANEL_H
#define PREVIEWPANEL_H

/// \brief This class will always mirror the currently edited frame from the canvas window
/// It will also allow for "playing" annimations between all the current frames.
class PreviewPanel : public QGraphicsView
{
	Q_OBJECT

public:
	explicit PreviewPanel(QWidget *parent = 0);

public slots:
	void setupNewSpriteDisplay(int spriteWidth, int spriteHeight);
	void updateSpriteDisplay(const QPixmap &sprite);
	void updateSpriteAnimationDisplay(const QPixmap &sprite);

	void setAnimationPlayerEnabled(bool state);

private:
	static const int SCENE_WIDTH = 1024;
	static const int SCENE_HEIGHT = 1024;

	QGraphicsScene gScene;
	QGraphicsPixmapItem gSprite;

	QPoint spritePosOffset;

	bool isPlayingAnimation;

};

#endif // PREVIEWPANEL_H
