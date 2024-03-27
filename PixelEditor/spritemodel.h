#ifndef SPRITEMODEL_H
#define SPRITEMODEL_H

#include <QColor>
#include <QList>

class QJsonObject;
class Sprite;

class Layer
{
public:
	QList<QColor> pixels;

	Layer(Sprite *parentSprite);

	void setPixel(int x, int y, QColor color, int brushSize);

	static Layer fromJson(const QJsonObject &json, Sprite *parentSprite);
	QJsonObject toJson() const;

private:
	Sprite *parentSprite;

};

class Frame
{
public:
	Frame(Sprite *parentSprite);

	void addLayer();
	void removeLayer();

	void selectLayer(int layerIndex);
	void mergeLayers();

	QList<QColor> getImage();

	static Frame fromJson(const QJsonObject &json, Sprite *parentSprite);
	QJsonObject toJson() const;

private:
	Sprite *parentSprite;

	QList<Layer> layers;
	int currentLayerIndex;

	Layer *mergedLayer;

};

class Sprite
{
public:
	Sprite(int width, int height);

	void addFrame();

	void moveFrameForward();
	void moveFrameBackward();
	void removeFrame();

	void selectFrame(int frameIndex);

	QString getName();
	int getWidth();
	int getHeight();

	static Sprite* fromJson(const QJsonObject &json);
	QJsonObject toJson() const;

private:
	int width;
	int height;
	QString name;

	QList<Frame> frames;
	int currentFrameIndex;

	int fps;

	Sprite(); // JSON constructor. Might become obsolete later.
};

#endif // SPRITEMODEL_H
