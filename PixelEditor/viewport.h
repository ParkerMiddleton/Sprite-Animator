#ifndef VIEWPORT_H
#define VIEWPORT_H

class Viewport : public QGraphicsView
{
	Q_OBJECT

public:
	explicit Viewport(QWidget *parent = 0);

public slots:
	void setupNewSpriteDisplay(int spriteWidth, int spriteHeight);
	void updateSpriteDisplay(const QPixmap &sprite);

signals:
	void pixelClicked(int x, int y);

	void mouseMoved(QPoint pos);
	void spriteSizeChanged(QPoint size);

protected:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	//void resizeEvent(QResizeEvent *event)override;
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

	void draw(const QPoint &mousePos);
	void zoom(const QPoint &mousePos, qreal factor);

	void setupTransparencyBackground(int width, int height);

};

#endif // VIEWPORT_H
