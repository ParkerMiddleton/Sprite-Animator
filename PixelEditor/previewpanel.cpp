#include "previewpanel.h"

PreviewPanel::PreviewPanel(QWidget *parent)
	: QGraphicsView{parent}
	, gScene{0, 0, SCENE_WIDTH, SCENE_HEIGHT}
	, spritePosOffset{0, 0}
	, isPlayingAnimation{false}
{
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	gScene.addItem(&gSprite);
	this->setScene(&gScene);
}

void PreviewPanel::setupNewSpriteDisplay(int spriteWidth, int spriteHeight)
{
	// Setup position in scene
	spritePosOffset.setX(SCENE_WIDTH / 2 - spriteWidth / 2);
	spritePosOffset.setY(SCENE_HEIGHT / 2 - spriteHeight / 2);

	gSprite.setTransform(QTransform().translate(spritePosOffset.x(), spritePosOffset.y()));

	// Match scale to the size.
	this->resetTransform();
	qreal scaleFactor = std::min((qreal)this->width() / (qreal)spriteWidth, (qreal)this->height() / (qreal)spriteHeight);
	scaleFactor -= scaleFactor * 0.1;
	this->scale(scaleFactor, scaleFactor);
}

void PreviewPanel::updateSpriteDisplay(const QPixmap &sprite)
{
	if (!isPlayingAnimation)
	{
		gSprite.setPixmap(sprite);
		this->centerOn(&gSprite);
	}
}

void PreviewPanel::updateSpriteAnimationDisplay(const QPixmap &sprite)
{
	if (isPlayingAnimation)
	{
		gSprite.setPixmap(sprite);
		this->centerOn(&gSprite);
	}
}

void PreviewPanel::setAnimationPlayerEnabled(bool state)
{
	isPlayingAnimation = state;
}
