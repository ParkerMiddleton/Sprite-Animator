#ifndef PREVIEWPANEL_H
#define PREVIEWPANEL_H
/**
 * @authors Tommy Heimer, Egor Chesnokov, Koby Dato, Parker Middleton, Aditya Mukerjee, Charles WolfGramm.
 *
 * @version 1.0
 * @date 4/1/2024
 */

///
/// \brief This class will always mirror the currently edited frame from the canvas window
/// It will also allow for "playing" annimations between all the current frames.
///
class PreviewPanel : public QGraphicsView
{
	Q_OBJECT

public:
	///
	/// \brief PreviewPanel Contructor.
	/// \param parent parent of this widget.
	///
	explicit PreviewPanel(QWidget *parent = 0);

public slots:
	///
	/// \brief Updates the preview panel for the new size of the sprite.
	/// \param spriteWidth width of the new sprite.
	/// \param spriteHeight height of the new sprite.
	///
	void setupNewSpriteDisplay(int spriteWidth, int spriteHeight);

	///
	/// \brief Updates the display data.
	/// \param sprite display data.
	///
	void updateSpriteDisplay(const QPixmap &sprite);

	///
	/// \brief Update the display data when the animation playback is active.
	/// \param sprite display data.
	///
	void updateSpriteAnimationDisplay(const QPixmap &sprite);

	///
	/// \brief Enabled and disables the animation playback.
	/// \param state enable or disable
	///
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
