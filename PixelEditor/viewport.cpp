#include "viewport.h"

Viewport::Viewport(QWidget *parent)
	: QGraphicsView{parent}
	, gScene{0, 0, SCENE_WIDTH, SCENE_HEIGHT}
	, isLeftMouseButtonPressed{false}
	, spritePosOffset{0, 0}
	, isPanning{false}
{
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setTransformationAnchor(QGraphicsView::NoAnchor);

	gItemGroup.addToGroup(&gBackground);
	gItemGroup.addToGroup(&gSprite);
	gScene.addItem(&gItemGroup);
	this->setScene(&gScene);
}

void Viewport::setupNewSpriteDisplay(int spriteWidth, int spriteHeight)
{
	this->setupTransparencyBackground(spriteWidth, spriteHeight);

	// Setup position in scene
	spritePosOffset.setX(SCENE_WIDTH / 2 - spriteWidth / 2);
	spritePosOffset.setY(SCENE_HEIGHT / 2 - spriteHeight / 2);

	gBackground.setTransform(QTransform().translate(spritePosOffset.x(), spritePosOffset.y()));
	gSprite.setTransform(QTransform().translate(spritePosOffset.x(), spritePosOffset.y()));

	this->resetTransform();
	this->scale(6.f, 6.f);
	this->centerOn(&gBackground);

	emit spriteSizeChanged(QPoint{spriteWidth, spriteHeight});
}

void Viewport::updateSpriteDisplay(const QPixmap &sprite)
{
	gSprite.setPixmap(sprite);
}

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
		isLeftMouseButtonPressed = true;
		this->draw(event->pos());
	}
}

void Viewport::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
	{
		isPanning = false;
		this->setCursor(Qt::CrossCursor);
	}
	else if (event->button() == Qt::LeftButton)
	{
		isLeftMouseButtonPressed = false;
	}
}

void Viewport::mouseMoveEvent(QMouseEvent *event)
{
	const QPointF &newViewPos = this->mapToScene(event->pos());

	emit mouseMoved(QPoint(newViewPos.x(), newViewPos.y()) - spritePosOffset);

	if (isPanning)
	{
		QPointF deltaViewPos = newViewPos - oldViewPos;
		this->translate(deltaViewPos.rx(), deltaViewPos.ry());
		oldViewPos = this->mapToScene(event->pos());
	}
	else if (isLeftMouseButtonPressed)
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

	if (!(0 <= p2.x() && p2.x() < gBackground.pixmap().width() && 0 <= p2.y() && p2.y() < gBackground.pixmap().height()))
		return;

	emit pixelClicked(p2.x(), p2.y());
}

void Viewport::zoom(const QPoint &mousePos, qreal factor)
{
	const QPointF &prevMouseCoordinate = this->mapToScene(mousePos);
	this->scale(factor, factor);
	const QPointF &currentMouseCoordinate = this->mapToScene(mousePos);
	const QPointF &offsetMouseCoordinate = currentMouseCoordinate - prevMouseCoordinate;
	this->translate(offsetMouseCoordinate.x(), offsetMouseCoordinate.y());
}

void Viewport::setupTransparencyBackground(int width, int height)
{
	QPixmap pBackground(width, height);

	//Draw checker pattern
	QPainter painter(&pBackground);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if ((x + y) % 2 == 0)
				painter.fillRect(x, y, 1, 1, Qt::lightGray);
			else
				painter.fillRect(x, y, 1, 1, Qt::white);
		}
	}

	painter.end();

	gBackground.setPixmap(pBackground);
}
