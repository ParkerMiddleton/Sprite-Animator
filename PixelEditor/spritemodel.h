#ifndef SPRITEMODEL_H
#define SPRITEMODEL_H

class QJsonObject;
class Sprite;

struct Color
{
	uchar r = 0;
	uchar g = 0;
	uchar b = 0;
	uchar a = 255;
};

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

	QList<Color> pixels;

	Layer();

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

	Frame();

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

	int getWidth();
	int getHeight();

	static Sprite* fromJson(const QJsonObject &json);
	QJsonObject toJson() const;

private:
	int width;
	int height;

	QList<Frame> frames;
	int currentFrameIndex;

	int fps;

	Sprite();

};

#endif // SPRITEMODEL_H
