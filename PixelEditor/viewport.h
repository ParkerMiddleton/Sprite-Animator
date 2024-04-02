#ifndef VIEWPORT_H
#define VIEWPORT_H
/**
 * @authors Tommy Heimer, Egor Chesnokov, Koby Dato, Parker Middleton, Aditya Mukerjee, Charles WolfGramm.
 *
 * @version 1.0
 * @date 4/1/2024
 */

///
/// \brief This class displays the current loaded sprite and detects when the user wants to modify pixels.
///
class Viewport : public QGraphicsView
{
	Q_OBJECT

public:
	///
	/// \brief Viewport Contructor.
	/// \param parent parent of this widget.
	///
	explicit Viewport(QWidget *parent = 0);

public slots:
	///
	/// \brief Updates the viewport for the new size of the sprite.
	/// \param spriteWidth width of the new sprite.
	/// \param spriteHeight height of the new sprite.
	///
	void setupNewSpriteDisplay(int spriteWidth, int spriteHeight);

	///
	/// \brief Updates the display data.
	/// \param sprite display data.
	///
	void updateSpriteDisplay(const QPixmap &sprite);

signals:
	/// \brief On mouse clicked in the displayed sprite.
	void pixelClicked(int x, int y);

	/// \brief On mouse moved inside the viewport.
	void mouseMoved(QPoint pos);

	/// \brief On new sprite setup.
	void spriteSizeChanged(QPoint size);

protected:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;

private:
	static const int SCENE_WIDTH = 1024;
	static const int SCENE_HEIGHT = 1024;

	QGraphicsScene gScene;
	QGraphicsItemGroup gItemGroup;

	QGraphicsPixmapItem gBackground;
	QGraphicsPixmapItem gSprite;

	bool isLeftMouseButtonPressed;
	QPoint spritePosOffset;

	bool isPanning;
	QPointF oldViewPos;

	///
	/// \brief Sends signal if mouse clicked on the displayed sprite.
	/// \param mousePos mouse position of the click event
	///
	void draw(const QPoint &mousePos);

	///
	/// \brief Scales the viewport.
	/// \param mousePos mouse position to scale into.
	/// \param factor scale factor.
	///
	void zoom(const QPoint &mousePos, qreal factor);

	///
	/// \brief setupTransparencyBackground Setups the transparency background with the size of the sprite.
	/// \param width width of the transparency background to setup.
	/// \param height height of the transparency background to setup.
	///
	void setupTransparencyBackground(int width, int height);

};

#endif // VIEWPORT_H
