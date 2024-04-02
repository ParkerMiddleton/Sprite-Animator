#ifndef SPRITEMODEL_H
#define SPRITEMODEL_H
/**
 * Tommy Heimer, Egor Chesnokov, Kobe Dato, Parker Middleton, Aditya, Charles.
 *  Last update: 4/1/2024
 *
 */
class Sprite;

/**
 * Layer represents an indivdual layer in a given frame. This model allows the user to
 * create multiple multiple layers in an frame that is amalgamated into a frnal image in
 * frame.
 * @brief The Layer class
 */
class Layer
{
public:
	Layer(Sprite *parentSprite);
    ///
    /// @brief draw Draws a pixel in the layer
	/// @param x, location x
	/// @param y, location y
	/// @param BrushSize, length of the square to be drawn.
    ///
	void setPixel(int x, int y, QColor color);
    ///
    /// \brief getPixel
    /// \param x
    /// \param y
    /// \return returns the color of a pixel in the layer at a point.
    ///
	QColor getPixel(int x, int y) const;
    ///
    /// \brief fromJson deserializes a layer object from a json file.
    /// \param json save file.
    /// \param parentSprite the sprite this layer belongs to.
    /// \return a new layer.
    ///
	static Layer fromJson(const QJsonObject &json, Sprite *parentSprite);
    ///
    /// \brief toJson serializes this layer to a json object.
    /// \return A serialzed json representation of this layer.
    ///
	QJsonObject toJson() const;

private:
	Sprite *parentSprite;
	QList<int> pixels;

	Layer();

};
/**
 * @brief The Frame class
 * Frame represents an image in sprite. the final image a frame produces is a product of its layers.
 * Like sprite, frame has a list of layers and internal index that the user can use to manipulate
 * the individual layers.
 */
class Frame
{
public:
	Frame(Sprite *parentSprite);

    ///
    /// \brief paintAt paints a pixel or multiple pixel in the current layer of the frame.
    /// \param x
    /// \param y
    /// \param color
    /// \param brushSize
    ///
	void paintAt(int x, int y, QColor color, int brushSize);

    ///
    /// \brief addLayer adds a new layer to the list of layers in this frame.
    ///
	void addLayer();

	void removeCurrentLayer();
    ///
    /// \brief selectLayer selects a layer for the frame to represent at a given index.
    /// \param layerIndex
    ///
	void selectLayer(int layerIndex);
    ///
    /// \brief getDisplayData
    /// \return returns the current frame layer as a sumation of its layers.
    ///
	const QPixmap& getDisplayData();
    ///
    /// \brief getLayerCount
    /// \return returns the number layers in this frame.
    ///
	int getLayerCount();
    ///
    /// \brief getCurrentLayerIndex
    /// \return returns the index for the list of layers in this frame.
    ///
	int getCurrentLayerIndex();

	static Frame fromJson(const QJsonObject &json, Sprite *parentSprite);
	QJsonObject toJson() const;

private:
	Sprite *parentSprite;
	QPixmap displayData;

	QList<Layer> layers;
	int currentLayerIndex;
    ///
    /// \brief Frame Constructor for a new frame.
    /// \param width
    /// \param height
    ///
	Frame(int width, int height);
    ///
    /// \brief mergeLayersIntoDisplayData Merges all layer information into a single pixmap.
    ///
	void mergeLayersIntoDisplayData();
    ///
    /// \brief getMergedPixel merges pixel information from this frames layers at a set point.
    /// \param x
    /// \param y
    /// \return returns the color of the merged pixel.
    ///
	QColor getMergedPixel(int x, int y);
    ///
    /// \brief colorsBlendAlpha Blends on opaque colors.
    /// \param bgc background color.
    /// \param fgc forground color.
    /// \return blended color.
    ///
	QColor colorsBlendAlpha(QColor bgc, QColor fgc);
};
/**
 * @brief The Sprite class
 * Sprite represents a list of frames that can be played back as an aniation.
 * Sprite has an internl index for this list the user cna manipulate to access individual
 * frames in the sprite.
 */
class Sprite
{
public:
	Sprite(int width, int height);
    ///
	/// @brief addFrame Adds a new frame to the sprite.
    void addFrame(bool duplicate);
    ///
    /// \brief selectFrame Selects frame from a list of frames using an
    /// \param frameIndex
    ///
	void selectFrame(int frameIndex);
    ///
    /// \brief moveCurrentFrameLeft
	void moveCurrentFrameLeft();
	void moveCurrentFrameRight();
    ///
	/// @brief removeFrame Removes the current frame.
	void removeCurrentFrame();
    /// @brief returns the address in memory for the current frame the sprite is representing
	Frame& currentFrame();
    ///
    /// \brief getWidth
    /// \return returns the width of the sprite.
    ///
	int getWidth();
    ///
    /// \brief getHeight
    /// \return returns the height of the sprite.
    ///
	int getHeight();
    ///
    /// \brief getFrameCount
    /// \return returns the amount of frames in the sprite
    ///
	int getFrameCount();
    ///
    /// \brief getCurrentFrameIndex
    /// \return returns the index that the sprite is currently on.
    ///
	int getCurrentFrameIndex();
    ///
    /// \brief getFPS
    /// \return returns the current fps the preview animation will run at.
    ///
	int getFPS();
    ///
    /// \brief setFPS sets the fps the preview animation will run at.
    /// \param fps
    ///
	void setFPS(int fps);
    ///
    /// \brief getFrame
    /// \param index
    /// \return returns any given frame from an inputed index.
    ///
	Frame& getFrame(int index);
    ///
    /// \brief FromJson Loads a saved sprite form a json file
    /// \param json A json save file.
    /// \return returns a pointer to a new sprite loaded from the json.
    ///
	static Sprite* fromJson(const QJsonObject &json);
    ///
    /// \brief toJson Serilizes this sprite object to a json object.
    /// \return returns that JsonObject.
    ///
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
