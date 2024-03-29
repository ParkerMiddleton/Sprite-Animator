#ifndef VIEWPORT_H
#define VIEWPORT_H

class Viewport : public QGraphicsView
{
	Q_OBJECT

public:
	explicit Viewport(QWidget *parent = 0);
	~Viewport();

public slots:
	void setupSprite(const QImage &image, int width, int height);
	void setPixelColor(int x, int y, QColor color);

	void setDrawingColor(const QColor &color);
	void setBrushEnabled();
	void setEraserEnabled();

signals:
	void colorPainted(int x, int y, QColor color);
	void informViewOfPencilEnabled(bool);
	void sendPixmapData(QPixmap *p);

protected:
	//void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	//void resizeEvent(QResizeEvent *event)override;
	void wheelEvent(QWheelEvent *event) override;

private:
	enum class Tool { None, Brush, Eraser };

	static const int SCENE_WIDTH = 1024;
	static const int SCENE_HEIGHT = 1024;

	Tool currentTool;

	QPixmap *pBackground;
	QPixmap *pSprite;

	QGraphicsScene gScene;
	QGraphicsItemGroup gItemGroup;

	QGraphicsPixmapItem gBackground;
	QGraphicsPixmapItem gSprite;

	QPen pen;

	QColor color;
	bool isMousePressed;
	QPoint spritePosOffset;

	bool isPanning;
	QPointF oldViewPos;

	void draw(const QPoint &mousePos);
	void zoom(const QPoint &mousePos, qreal factor);

};

#endif // VIEWPORT_H
