#ifndef SPRITE_H
#define SPRITE_H

class QJsonObject;
class Sprite;

class Layer
{
	friend class Frame;

public:
	Layer(Sprite *parentSprite);

	/// @brief draw Draws a pixel on the current layer of current frame.
	/// @param x, location x
	/// @param y, location y
	/// @param BrushSize, length of the square to be drawn.
	void drawColor(int x, int y, QColor color, int brushSize = 1);

	static Layer fromJson(const QJsonObject &json, Sprite *parentSprite);
	QJsonObject toJson() const;

private:
	Sprite *parentSprite;

	QList<QColor> pixels;

};

class Frame
{
public:
	Frame(Sprite *parentSprite);

	/// @brief addLayer Adds a new Layer to the frame.
	void addLayer();

	void removeCurrentLayer();

	void selectLayer(int layerIndex);

	Layer& getCurrentLayer();

	QImage getMergedLayerImage();
	QColor getMergedPixel(int x, int y);

	static Frame fromJson(const QJsonObject &json, Sprite *parentSprite);
	QJsonObject toJson() const;

private:
	Sprite *parentSprite;

	QList<Layer> layers;
	int currentLayerIndex;

	/// @brief mergeLayers merges all Layers into final image

};

class Sprite
{
public:
	Sprite(int width, int height);

	/// @brief addFrame Adds a new frame to the sprite.
	void addFrame();

	void selectFrame(int frameIndex);

	void moveCurrentFrameForward();

	void moveCurrentFrameBackward();

	/// @brief removeFrame Removes the current frame.
	void removeCurrentFrame();

	Frame& getCurrentFrame();

	QString getName();
	int getWidth();
	int getHeight();

	void setName(const QString &newName);

	static Sprite* fromJson(const QJsonObject &json);
	QJsonObject toJson() const;

private:
	QString name;
	int width;
	int height;

	QList<Frame> frames;
	int currentFrameIndex;

	int fps;

	Sprite();

};

#endif // SPRITE_H
