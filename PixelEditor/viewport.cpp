#include "viewport.h"

Viewport::Viewport(QWidget *parent)
	: QGraphicsView{parent}
	, currentTool{Tool::None}
	, pBackground{nullptr}
	, pSprite{nullptr}
	, gScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT)
	, isMousePressed{false}
	, spritePosOffset{0, 0}
	, isPanning{false}
{
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setTransformationAnchor(QGraphicsView::NoAnchor);

	pen.setWidth(1);
	gItemGroup.addToGroup(&gBackground);
	gItemGroup.addToGroup(&gSprite);
	gScene.addItem(&gItemGroup);
	//gScene.addItem(&gSprite);
	this->setScene(&gScene);

	/*
	Known Issue: We want the label contained within the gridLayout object to match the height and width
	of its parent container. As of now, this isnt working properly. Hard coded pixmap sizes are used below,
	but we should be able to use this->height() and this->width() respectively.
	*/

	// // Fill the label with an array of transparent pixels
	// pixmap = new QPixmap(frameWidth, frameHeight); // random values here are of the gridlayout's height and width

	// //Fill the map with transparent pixels
	// pixmap->fill(Qt::transparent);

	// //Tells the QPainter object that this is the object we are drawing.
	// QPainter painter (pixmap);

	// //Draw the pixels
	// int checkerSize = 10;
	// for (int y = 0; y < frameHeight; y += checkerSize) { // height
	//     for (int x = 0; x < frameWidth; x += checkerSize) { // width
	//         if ((x / checkerSize + y / checkerSize) % 2 == 0) {
	//             painter.fillRect(x, y, checkerSize, checkerSize, Qt::lightGray);
	//         }else{
	//             painter.fillRect(x, y, checkerSize, checkerSize, QColor::fromRgb(255, 255, 255,255));
	//         }
	//     }
	// }
	// // End painting
	// painter.end();

	// Set the pixmap as the label's pixmap
	//setPixmap(*transparencyPixmap);
	/*QPainter painter(pixmap);

	int x = 0;
	int y = 0;

	for(QColor q : sprite->getFrameImage())
	{
		QPen defaultPen(q,1);
		painter.setPen(defaultPen);
		painter.drawPoint(x,y);
		x++;
		if(x == frameWidth)
		{
			x = 0;
			y++;
		}
		repaint();
	}*/
}

Viewport::~Viewport()
{
	delete pBackground;
	delete pSprite;
}

void Viewport::setupSprite(const QImage &image, int width, int height)
{
	delete pBackground;
	delete pSprite;

	pBackground = new QPixmap(width, height);
	pBackground->fill(Qt::magenta);

	pSprite = new QPixmap(width, height);
	pSprite->fill(Qt::transparent);
	pSprite->convertFromImage(image, Qt::NoFormatConversion);

	QTextStream(stdout) << pSprite->hasAlphaChannel() << "\n";

	// Setup position in scene
	spritePosOffset.setX(SCENE_WIDTH / 2 - width / 2);
	spritePosOffset.setY(SCENE_HEIGHT / 2 - height / 2);

	gBackground.setPixmap(*pBackground);
	gSprite.setPixmap(*pSprite);

	gBackground.setTransform(QTransform().translate(spritePosOffset.x(), spritePosOffset.y()));
	gSprite.setTransform(QTransform().translate(spritePosOffset.x(), spritePosOffset.y()));

	this->centerOn(&gSprite);

	this->repaint();
}

void Viewport::setPixelColor(int x, int y, QColor color)
{
	QPainter painter(pSprite);
	painter.setCompositionMode(QPainter::CompositionMode_Source);
	pen.setColor(color);
	painter.setPen(pen);
	painter.drawPoint(x, y);

	gSprite.setPixmap(*pSprite);

	emit sendPixmapData(pSprite);
}

/*void Viewport::paintEvent(QPaintEvent *)
{
	//QTextStream(stdout) << "fsdf";
	if (transparencyPixmap && spritePixmap)
	{
		QPainter painter(this);
		painter.drawPixmap(0, 0, *transparencyPixmap);
		painter.drawPixmap(offsetX, offsetY, *spritePixmap);

		emit sendPixmapData(spritePixmap);
	}
}*/

void Viewport::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
	{
		isPanning = true;
		oldViewPos = this->mapToScene(event->pos());
		this->setCursor(Qt::ClosedHandCursor);
	}
	else if (event->button() == Qt::LeftButton)
	{
		isMousePressed = true;
		this->draw(event->pos());
	}
}

void Viewport::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
	{
		isPanning = false;
		this->setCursor(Qt::ArrowCursor);
	}
	else if (event->button() == Qt::LeftButton)
	{
		isMousePressed = false;
	}
}

void Viewport::mouseMoveEvent(QMouseEvent *event)
{
	if (isPanning)
	{
		const QPointF &newViewPos = this->mapToScene(event->pos());
		QPointF deltaViewPos = newViewPos - oldViewPos;
		this->translate(deltaViewPos.rx(), deltaViewPos.ry());
		oldViewPos = this->mapToScene(event->pos());
	}
	else if (isMousePressed)
	{
		this->draw(event->pos());
	}
}

void Viewport::wheelEvent(QWheelEvent *event)
{
	if (event->angleDelta().y() < 0)
	{
		this->zoom(event->position().toPoint(), 1.0 / 1.2);
	}
	else if (event->angleDelta().y() > 0)
	{
		this->zoom(event->position().toPoint(), 1.2);
	}
}

void Viewport::draw(const QPoint &mousePos)
{
	QPointF scenePos = this->mapToScene(mousePos);
	QPoint p2(scenePos.x() - spritePosOffset.x(), scenePos.y() - spritePosOffset.y());

	if (!(0 <= p2.x() && p2.x() < pSprite->width()
		&&
		  0 <= p2.y() && p2.y() < pSprite->height()))
	{
		return;
	}

	if (currentTool == Tool::Brush)
	{
		emit colorPainted(p2.x(), p2.y(), color);
	}
	else if (currentTool == Tool::Eraser)
	{
		emit colorPainted(p2.x(), p2.y(), QColor(0, 0, 0, 0));
	}
}

void Viewport::zoom(const QPoint &mousePos, qreal factor)
{
	const QPointF &prevMouseCoordinate = this->mapToScene(mousePos);
	this->scale(factor, factor);
	const QPointF &currentMouseCoordinate = this->mapToScene(mousePos);
	const QPointF &offsetMouseCoordinate = currentMouseCoordinate - prevMouseCoordinate;
	this->translate(offsetMouseCoordinate.x(), offsetMouseCoordinate.y());
}

void Viewport::setDrawingColor(const QColor &newColor)
{
	color = newColor;
}

void Viewport::setBrushEnabled()
{
	currentTool = Tool::Brush;
}

void Viewport::setEraserEnabled()
{
	currentTool = Tool::Eraser;
}
