#ifndef SPRITEMODEL_H
#define SPRITEMODEL_H

#include <QColor>
#include <QList>

class QJsonObject;
class Sprite;

class Layer
{
public:
	uchar *pixels;
	uint width, height;

	Layer(uint width, uint height);
	~Layer();

	void setPixel(uint x, uint y, QColor color);

	static Layer fromJson(const QJsonObject &json);
	QJsonObject toJson() const;

};

class Frame
{
public:
    Frame(int width, int height);

    /**
     * @brief addLayer Adds a new Layer to the frame.
     */
    void addLayer();

    void removeLayer();

    /**
     * @brief mergeLayers merges all Layers into final image
     */
    void mergeLayers();

    void setLayerIndex(int);

    QList<QColor> getMergedLayer();

	static Frame fromJson(const QJsonObject &json);
	QJsonObject toJson() const;

private:
    QList<Layer> layers;
    Layer mergedLayer;
    int layerIndex;
    int width;
    int height;

};

class Sprite
{
public:
    Sprite(int width, int height);

    /**
     * @brief draw Draws a pixel on the current layer of current frame.
     * @param x, location x
     * @param y, location y
     * @param BrushSize, length of the square to be drawn.
     */

    void setPixel(int x, int y, int BrushSize);
    /**
     * @brief erase Erases a pixel on the current layer of the current frame.
     * @param x
     * @param y
     * @param size
     */

    void erasePixel(int x, int y, int size);
    /**
     * @brief addFrame Adds a new frame to the sprite.
     */

    void addFrame();
    /**
     * @brief nextFrame Cycles to the next frame.
	 */

    void nextFrame();
    /**
     * @brief previousFrame Cycles to the previous frame.
     */
    void previousFrame();
    /**
     * @brief deleteFrame Deletes the current frame.
     */
    void deleteFrame();
    /**
     * @brief selectLayer selects a layer from the current Frame
     * @param layerIndex
     */
    void selectLayer(int layerIndex);
    /**
     * @brief addLayerToCurrentFrame
     */
    void addLayerToCurrentFrame();
    /**
     * @brief saveSprite Writes sprite to a json.
     */
    void saveSprite();
    /**
     * @brief loadSprite Loads sprite from a json.
     * @param filePath
     */
    void loadSprite(QString filePath);
    /**
     * @brief getImage From the current frame, retrieve a merged image of all its layers.
     * @return
     */
    QList<QColor> getFrameImage();

	static Sprite fromJson(const QJsonObject &json);
	QJsonObject toJson() const;

private:
    QList<Frame> frames;
	int width;
	int height;
	int frameIndex;
	int fps;
	QString name;

};

#endif // SPRITEMODEL_H
