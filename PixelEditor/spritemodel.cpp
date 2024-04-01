#include "spritemodel.h"

Layer::Layer(Sprite *parentSprite)
	: parentSprite{parentSprite}
{
	int size = parentSprite->getWidth() * parentSprite->getHeight();
	pixels.resize(size * 4);

	for (int index = 0; index < size; index++)
	{
		int pxy = index * 4;

		pixels[pxy + 0] = 0;
		pixels[pxy + 1] = 0;
		pixels[pxy + 2] = 0;
		pixels[pxy + 3] = 0;
	}
}

void Layer::setPixel(int x, int y, QColor color)
{
	int index = x + y * parentSprite->getWidth();
	int pxy = index * 4;
	pixels[pxy + 0] = color.red();
	pixels[pxy + 1] = color.green();
	pixels[pxy + 2] = color.blue();
	pixels[pxy + 3] = color.alpha();
}

QColor Layer::getPixel(int x, int y) const
{
	int index = x + y * parentSprite->getWidth();
	int pxy = index * 4;

	return QColor{pixels[pxy + 0], pixels[pxy + 1], pixels[pxy + 2], pixels[pxy + 3]};
}

Layer Layer::fromJson(const QJsonObject &json, Sprite *parentSprite)
{
	Layer layer;
	layer.parentSprite = parentSprite;

	if (const QJsonValue &jsonVal = json["pixels"]; jsonVal.isArray())
	{
		const QJsonArray &jsonPixels = jsonVal.toArray();
		layer.pixels.resize(jsonPixels.size() * 4);

		int pixelIndex = 0;
		for (const QJsonValue &jsonPixelVal : jsonPixels)
		{
			const QJsonObject &pixelJson = jsonPixelVal.toObject();
			int pxy = pixelIndex * 4;

			if (const QJsonValue &red = pixelJson["r"]; red.isDouble())
			{
				layer.pixels[pxy + 0] = red.toInt();
			}
			if (const QJsonValue &green = pixelJson["g"]; green.isDouble())
			{
				layer.pixels[pxy + 1] = green.toInt();
			}
			if (const QJsonValue &blue = pixelJson["b"]; blue.isDouble())
			{
				layer.pixels[pxy + 2] = blue.toInt();
			}
			if (const QJsonValue &alpha = pixelJson["a"]; alpha.isDouble())
			{
				layer.pixels[pxy + 3] = alpha.toInt();
			}

			pixelIndex++;
		}
	}

	return layer;
}

QJsonObject Layer::toJson() const
{
	QJsonObject json;
	QJsonArray jsonPixels;

	int size = parentSprite->getWidth() * parentSprite->getHeight();

	for (int index = 0; index < size; index++)
	{
		QJsonObject pixelJson;
		int pxy = index * 4;
		pixelJson["r"] = pixels[pxy + 0];
		pixelJson["g"] = pixels[pxy + 1];
		pixelJson["b"] = pixels[pxy + 2];
		pixelJson["a"] = pixels[pxy + 3];
		jsonPixels.append(pixelJson);
	}

	json["pixels"] = jsonPixels;

	return json;
}

Layer::Layer()
{

}

// FRAME CLASS

Frame::Frame(Sprite *parentSprite)
	: parentSprite{parentSprite}
	, displayData(parentSprite->getWidth(), parentSprite->getHeight())
	, currentLayerIndex{-1}
{
	displayData.fill(Qt::transparent);
	this->addLayer();
}

void Frame::paintAt(int x, int y, QColor color, int brushSize)
{
	// Check if brush size is odd.
	if (!(brushSize % 2))
		return;

	int brushHalf = (brushSize - 1) / 2;
	int spriteWidth = parentSprite->getWidth();
	int spriteHeight = parentSprite->getHeight();

	// Find Brush rect
	int lt_x = x - brushHalf; int lt_y = y - brushHalf; // lt is Left Top
	int rb_x = x + brushHalf; int rb_y = y + brushHalf; // rb is Right Bottom

	// Check bounds
	if (lt_x < 0) lt_x = 0;
	if (lt_y < 0) lt_y = 0;
	if (rb_x >= spriteWidth) rb_x = spriteWidth - 1;
	if (rb_y >= spriteHeight) rb_y = spriteHeight - 1;

	// Draw pixels
	QPen pen;
	pen.setWidth(1);
	QPainter painter(&displayData);
	painter.setCompositionMode(QPainter::CompositionMode_Source);

	for (int row = lt_y; row <= rb_y; row++)
	{
		for (int col = lt_x; col <= rb_x; col++)
		{
			layers[currentLayerIndex].setPixel(col, row, color);
			pen.setColor(this->getMergedPixel(col, row));
			painter.setPen(pen);
			painter.drawPoint(col, row);
		}
	}

	painter.end();
}

void Frame::addLayer()
{
	layers.push_back(Layer(parentSprite));
	currentLayerIndex = layers.size() - 1;
}

void Frame::selectLayer(int layerIndex)
{
	currentLayerIndex = layerIndex;
}

void Frame::removeCurrentLayer()
{
	if (layers.size() > 1) // If there is more than one layer.
	{
		layers.removeAt(currentLayerIndex);

		if (currentLayerIndex == layers.size()) // If index was the last layer.
		{
			currentLayerIndex--;
		}

		this->mergeLayersIntoDisplayData();
	}
}

const QPixmap& Frame::getDisplayData()
{
	return displayData;
}

int Frame::getLayerCount()
{
	return layers.size();
}

int Frame::getCurrentLayerIndex()
{
	return currentLayerIndex;
}

Frame Frame::fromJson(const QJsonObject &json, Sprite *parentSprite)
{
	Frame frame(parentSprite->getWidth(), parentSprite->getHeight());
	frame.parentSprite = parentSprite;

	if (const QJsonValue &jsonVal = json["layers"]; jsonVal.isArray())
	{
		const QJsonArray &jsonLayers = jsonVal.toArray();
		frame.layers.reserve(jsonLayers.size());

		for (const QJsonValue &jsonLayerVal : jsonLayers)
		{
			frame.layers.append(Layer::fromJson(jsonLayerVal.toObject(), parentSprite));
		}
	}

	frame.mergeLayersIntoDisplayData();

	return frame;
}

QJsonObject Frame::toJson() const
{
	QJsonObject json;
	QJsonArray jsonLayers;

	static int ins = 0;
	for (const Layer &layer : layers)
	{
		QTextStream(stdout) << ins++;
		jsonLayers.append(layer.toJson());
	}

	json["layers"] = jsonLayers;

	return json;
}

Frame::Frame(int width, int height)
	: displayData(width, height)
	, currentLayerIndex{0}
{
	displayData.fill(Qt::transparent);
}

void Frame::mergeLayersIntoDisplayData()
{
	QPen pen;
	pen.setWidth(1);

	QPainter painter(&displayData);
	painter.setCompositionMode(QPainter::CompositionMode_Source);

	for (int row = 0; row < displayData.height(); row++)
	{
		for (int col = 0; col < displayData.width(); col++)
		{
			pen.setColor(this->getMergedPixel(col, row));
			painter.setPen(pen);
			painter.drawPoint(col, row);
		}
	}

	painter.end();
}

QColor Frame::getMergedPixel(int x, int y)
{
	QColor mergedColor(Qt::transparent);

	for (const Layer &layer : layers)
	{
		mergedColor = colorsBlendAlpha(mergedColor, layer.getPixel(x, y));
	}

	return mergedColor;
}


QColor Frame::colorsBlendAlpha(QColor bgc, QColor fgc)
{
	// Taken from: https://stackoverflow.com/a/727339
	// Extremely suboptimal implementation.
	struct DClr { double r = 0.0; double g = 0.0; double b = 0.0; double a = 0.0; };
	DClr result;
	DClr bg{(double)bgc.red() / 255.0, (double)bgc.green() / 255.0, (double)bgc.blue() / 255.0, (double)bgc.alpha() / 255.0};
	DClr fg{(double)fgc.red() / 255.0, (double)fgc.green() / 255.0, (double)fgc.blue() / 255.0, (double)fgc.alpha() / 255.0};

	result.a = 1 - (1 - fg.a) * (1 - bg.a);

	if (result.a >= 1.0e-6) // If not fully transparent
	{
		result.r = fg.r * fg.a / result.a + bg.r * bg.a * (1 - fg.a) / result.a;
		result.g = fg.g * fg.a / result.a + bg.g * bg.a * (1 - fg.a) / result.a;
		result.b = fg.b * fg.a / result.a + bg.b * bg.a * (1 - fg.a) / result.a;
	}

	return QColor{uchar(255.0 * result.r), uchar(255.0 * result.g), uchar(255.0 * result.b), uchar(255.0 * result.a)};
}

// SPRITE CLASS

Sprite::Sprite(int width, int height)
	: width{width}
	, height{height}
	, currentFrameIndex{-1}
	, fps{24}
{
	this->addFrame();
}

void Sprite::addFrame()
{
	frames.push_back(Frame(this));
	currentFrameIndex = frames.size() - 1;
}

void Sprite::selectFrame(int frameIndex)
{
	currentFrameIndex = frameIndex;
}

void Sprite::moveCurrentFrameLeft()
{
	if (currentFrameIndex > 0)
	{
		int oldIndex = currentFrameIndex;
		frames.swapItemsAt(oldIndex, --currentFrameIndex);
	}
}

void Sprite::moveCurrentFrameRight()
{
	if (frames.size() > 1 && currentFrameIndex < frames.size() - 1)
	{
		int oldIndex = currentFrameIndex;
		frames.swapItemsAt(oldIndex, ++currentFrameIndex);
	}
}

void Sprite::removeCurrentFrame()
{
	if (frames.size() > 1) // If there is more than one frame.
	{
		frames.removeAt(currentFrameIndex);

		if (currentFrameIndex == frames.size()) // If index was the last frame.
		{
			currentFrameIndex--;
		}
	}
}

Frame& Sprite::currentFrame()
{
	return frames[currentFrameIndex];
}

int Sprite::getWidth()
{
	return width;
}

int Sprite::getHeight()
{
	return height;
}

int Sprite::getFrameCount()
{
	return frames.size();
}

int Sprite::getCurrentFrameIndex()
{
	return currentFrameIndex;
}

int Sprite::getFPS()
{
	return fps;
}

void Sprite::setFPS(int fps)
{
	this->fps = fps;
}

Frame &Sprite::getFrame(int index)
{
	return frames[index];
}

Sprite* Sprite::fromJson(const QJsonObject &json)
{
	Sprite *sprite = nullptr;

	const QJsonValue &jsonWidth = json["width"];
	const QJsonValue &jsonHeight = json["height"];
	const QJsonValue &jsonFPS = json["fps"];

	if (jsonWidth.isDouble() &&
		jsonHeight.isDouble())
	{
		sprite = new Sprite();

		sprite->width = jsonWidth.toInt();
		sprite->height = jsonHeight.toInt();

		if (jsonFPS.isDouble())
			sprite->fps = jsonFPS.toInt();

		if (const QJsonValue jsonFramesVal = json["frames"]; jsonFramesVal.isArray())
		{
			const QJsonArray &jsonFrames = jsonFramesVal.toArray();
			sprite->frames.reserve(jsonFrames.size());

			for (const QJsonValue &jsonFrameVal : jsonFrames)
				sprite->frames.append(Frame::fromJson(jsonFrameVal.toObject(), sprite));
		}
	}

	return sprite;
}

QJsonObject Sprite::toJson() const
{
	QJsonObject json;
	json["width"] = width;
	json["height"] = height;
	json["fps"] = fps;

	QJsonArray jsonFrames;

	for (const Frame &frame : frames)
	{
		jsonFrames.append(frame.toJson());
	}

	json["frames"] = jsonFrames;

	return json;
}

Sprite::Sprite()
	: currentFrameIndex{0}
	, fps{24}
{

}
