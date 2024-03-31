#include "spritemodel.h"

Layer::Layer(Sprite *parentSprite)
	: parentSprite(parentSprite)
{
	int size = parentSprite->getWidth() * parentSprite->getHeight();
	pixels.reserve(size);

	for (int index = 0; index < size; index++)
	{
		pixels.push_back({0, 0, 0, 0});
	}
}

void Layer::setPixel(int x, int y, QColor color)
{
	int index = x + y * parentSprite->getWidth();
	pixels[index].r = color.red();
	pixels[index].g = color.green();
	pixels[index].b = color.blue();
	pixels[index].a = color.alpha();
}

Layer Layer::fromJson(const QJsonObject &json, Sprite *parentSprite)
{
	Layer layer;
	layer.parentSprite = parentSprite;

	if (const QJsonValue &jsonVal = json["pixels"]; jsonVal.isArray())
	{
		const QJsonArray &jsonPixels = jsonVal.toArray();
		layer.pixels.resize(jsonPixels.size());

		int pixelIndex = 0;
		for (const QJsonValue &jsonPixelVal : jsonPixels)
		{
			const QJsonObject &pixelJson = jsonPixelVal.toObject();

			if (const QJsonValue &red = pixelJson["r"]; red.isDouble())
			{
				//layer.pixels[pixelIndex].setRed(red.toInt());
				layer.pixels[pixelIndex].r = red.toInt();
			}
			if (const QJsonValue &green = pixelJson["g"]; green.isDouble())
			{
				//layer.pixels[pixelIndex].setGreen(green.toInt());
				layer.pixels[pixelIndex].g = green.toInt();
			}
			if (const QJsonValue &blue = pixelJson["b"]; blue.isDouble())
			{
				//layer.pixels[pixelIndex].setBlue(blue.toInt());
				layer.pixels[pixelIndex].b = blue.toInt();
			}
			if (const QJsonValue &alpha = pixelJson["a"]; alpha.isDouble())
			{
				//layer.pixels[pixelIndex].setAlpha(alpha.toInt());
				layer.pixels[pixelIndex].a = alpha.toInt();
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

	for (const Color &pixel : pixels)
	{
		QJsonObject pixelJson;
		pixelJson["r"] = pixel.r;
		pixelJson["g"] = pixel.g;
		pixelJson["b"] = pixel.b;
		pixelJson["a"] = pixel.a;
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
	layers[currentLayerIndex].setPixel(x, y, color);

	QPen pen;
	pen.setWidth(1);

	QPainter painter(&displayData);
	painter.setCompositionMode(QPainter::CompositionMode_Source);
	pen.setColor(this->getMergedPixel(x, y));
	painter.setPen(pen);
	painter.drawPoint(x, y);
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

Layer& Frame::currentLayer()
{
	return layers[currentLayerIndex];
}

Color mixColorsAdditive(Color bgc, Color fgc)
{
	struct DClr { double r = 0.0; double g = 0.0; double b = 0.0; double a = 0.0; };
	DClr result;
	DClr bg{(double)bgc.r / 255.0, (double)bgc.g / 255.0, (double)bgc.b / 255.0, (double)bgc.a / 255.0};
	DClr fg{(double)fgc.r / 255.0, (double)fgc.g / 255.0, (double)fgc.b / 255.0, (double)fgc.a / 255.0};

	result.a = 1 - (1 - fg.a) * (1 - bg.a);

	if (result.a >= 1.0e-6) // If not fully transparent
	{
		result.r = fg.r * fg.a / result.a + bg.r * bg.a * (1 - fg.a) / result.a;
		result.g = fg.g * fg.a / result.a + bg.g * bg.a * (1 - fg.a) / result.a;
		result.b = fg.b * fg.a / result.a + bg.b * bg.a * (1 - fg.a) / result.a;
	}

	return Color{uchar(255.0 * result.r), uchar(255.0 * result.g), uchar(255.0 * result.b), uchar(255.0 * result.a)};
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
	// TODO: Rewrite using QPainter and without QImage.
	QImage image(parentSprite->getWidth(), parentSprite->getHeight(), QImage::Format_RGBA8888);

	for (int row = 0; row < image.height(); row++)
	{
		for (int col = 0; col < image.width(); col++)
		{
			image.setPixelColor(col, row, this->getMergedPixel(col, row));
		}
	}

	displayData.convertFromImage(image, Qt::NoFormatConversion);
}

QColor Frame::getMergedPixel(int x, int y)
{
	int index = x + y * parentSprite->getWidth();
	Color clr{0, 0, 0, 0};

	for (const Layer &layer : layers)
	{
		clr = mixColorsAdditive(clr, layer.pixels[index]);
	}

	return QColor(clr.r, clr.g, clr.b, clr.a);
}

// SPRITE CLASS

Sprite::Sprite(int width, int height)
	: width{width}
	, height{height}
	, currentFrameIndex{-1}
	, fps{0}
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

Sprite* Sprite::fromJson(const QJsonObject &json)
{
	Sprite *sprite = nullptr;

	const QJsonValue &jsonWidth = json["width"];
	const QJsonValue &jsonHeight = json["height"];

	if (jsonWidth.isDouble() &&
		jsonHeight.isDouble())
	{
		sprite = new Sprite();

		sprite->width = jsonWidth.toInt();
		sprite->height = jsonHeight.toInt();

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
{

}
