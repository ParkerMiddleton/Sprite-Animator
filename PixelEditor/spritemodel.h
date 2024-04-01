#ifndef SPRITEMODEL_H
#define SPRITEMODEL_H

class Sprite;

class Layer
{
public:
	Layer(Sprite *parentSprite);

	/// @brief draw Draws a pixel on the current layer of current frame.
	/// @param x, location x
	/// @param y, location y
	/// @param BrushSize, length of the square to be drawn.
	void setPixel(int x, int y, QColor color);
	QColor getPixel(int x, int y) const;

	static Layer fromJson(const QJsonObject &json, Sprite *parentSprite);
	QJsonObject toJson() const;

private:
	Sprite *parentSprite;
	QList<int> pixels;

	Layer();

};

class Frame
{
public:
	Frame(Sprite *parentSprite);

	void paintAt(int x, int y, QColor color, int brushSize);

	/// @brief addLayer Adds a new Layer to the frame.
	void addLayer();

	void removeCurrentLayer();

	void selectLayer(int layerIndex);

	const QPixmap& getDisplayData();

	int getLayerCount();
	int getCurrentLayerIndex();

	static Frame fromJson(const QJsonObject &json, Sprite *parentSprite);
	QJsonObject toJson() const;

private:
	Sprite *parentSprite;
	QPixmap displayData;

	QList<Layer> layers;
	int currentLayerIndex;

	Frame(int width, int height);

	void mergeLayersIntoDisplayData();
	QColor getMergedPixel(int x, int y);
	QColor colorsBlendAlpha(QColor bgc, QColor fgc);

	/// @brief mergeLayers merges all Layers into final image

};

class Sprite
{
public:
	Sprite(int width, int height);

	/// @brief addFrame Adds a new frame to the sprite.
	void addFrame();

	void selectFrame(int frameIndex);

	void moveCurrentFrameLeft();
	void moveCurrentFrameRight();

	/// @brief removeFrame Removes the current frame.
	void removeCurrentFrame();

	Frame& currentFrame();

	int getWidth();
	int getHeight();

	int getFrameCount();
	int getCurrentFrameIndex();

	int getFPS();
	void setFPS(int fps);

	Frame& getFrame(int index);

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
