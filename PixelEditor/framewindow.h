#ifndef FRAMEWINDOW_H
#define FRAMEWINDOW_H

#include "spritemodel.h"
#include "filesystem.h"

#include <QLabel>
#include <QPaintDevice>
#include <QPixmap>
#include <QMouseEvent>


class FrameWindow : public QLabel
{

	Q_OBJECT


private:
	// Model Fields
	Sprite *sprite;
	FileSystem fileSystem;

	QPixmap *pixmap;
	QColor color;
	int pressed;
	bool pencilEnabled;
	bool eraserEnabled; // actually disables and enables

	void draw(QMouseEvent *e);

public:
	explicit FrameWindow(QWidget *parent = 0);
	~FrameWindow();

public slots:
	void setDrawingColor(const QColor &newColor);
	void setBrushEnabled();
	void setEraserEnabled();

	void saveSprite(const QString &filename);

signals:
	void informViewOfPencilEnabled(bool);
	void sendPixmapData(QPixmap *p);

protected:
	void paintEvent(QPaintEvent *e) override;
	void mousePressEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;
	void mouseMoveEvent(QMouseEvent *e)override;
	// void resizeEvent(QResizeEvent *event)override;
};



#endif // FRAMEWINDOW_H
