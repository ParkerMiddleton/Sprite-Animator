#include "spritemodel.h"

Layer::Layer(Sprite *parentSprite)
	: parentSprite(parentSprite)
{
	int size = parentSprite->getWidth() * parentSprite->getHeight();
	pixels.reserve(size);

	for (int index = 0; index < size; index++)
	{
		pixels.push_back(Qt::transparent);
	}
}

void Layer::drawColor(int x, int y, QColor color, int brushSize)
{
	int index = x + y * parentSprite->getWidth();
	pixels[index] = color;
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
				layer.pixels[pixelIndex].setRed(red.toInt());
			if (const QJsonValue &green = pixelJson["g"]; green.isDouble())
				layer.pixels[pixelIndex].setGreen(green.toInt());
			if (const QJsonValue &blue = pixelJson["b"]; blue.isDouble())
				layer.pixels[pixelIndex].setBlue(blue.toInt());
			if (const QJsonValue &alpha = pixelJson["a"]; alpha.isDouble())
				layer.pixels[pixelIndex].setAlpha(alpha.toInt());

			pixelIndex++;
		}
	}

	return layer;
}

QJsonObject Layer::toJson() const
{
	QJsonObject json;
	QJsonArray jsonPixels;

	for (const QColor &pixel : pixels)
	{
		QJsonObject pixelJson;
		pixelJson["r"] = pixel.red();
		pixelJson["g"] = pixel.green();
		pixelJson["b"] = pixel.blue();
		pixelJson["a"] = pixel.alpha();
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
	, currentLayerIndex{0}
{
	this->addLayer();
}

void Frame::addLayer()
{
	layers.push_back(Layer(parentSprite));
}

void Frame::removeCurrentLayer()
{
	layers.remove(currentLayerIndex);
}

void Frame::selectLayer(int layerIndex)
{
	if (0 >= layerIndex && layerIndex < layers.size())
	{
		currentLayerIndex = layerIndex;
	}
}

Layer& Frame::getCurrentLayer()
{
	return layers[currentLayerIndex];
}

QImage Frame::getMergedLayerImage()
{
	QImage image(parentSprite->getWidth(), parentSprite->getHeight(), QImage::Format_RGBA8888);

	for (const Layer &layer : layers)
	{
		for (int row = 0; row < image.height(); row++)
		{
			for (int col = 0; col < image.width(); col++)
			{
				int index = col + row * image.width();
				image.setPixelColor(col, row, layer.pixels[index]);
			}
		}
	}

	return image;
}

QColor Frame::getMergedPixel(int x, int y)
{
	int index = x + y * parentSprite->getWidth();
	QColor mergedPixel;

	for (const Layer &layer : layers)
	{
		mergedPixel = layer.pixels[index];
	}

	return mergedPixel;
}

Frame Frame::fromJson(const QJsonObject &json, Sprite *parentSprite)
{
	Frame frame;
	frame.parentSprite = parentSprite;

	if (const QJsonValue &jsonVal = json["layers"]; jsonVal.isArray())
	{
		const QJsonArray &jsonLayers = jsonVal.toArray();
		frame.layers.reserve(jsonLayers.size());
		static int in = 0;

		for (const QJsonValue &jsonLayerVal : jsonLayers)
		{
			QTextStream(stdout) << in++;
			frame.layers.append(Layer::fromJson(jsonLayerVal.toObject(), parentSprite));
		}
	}

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

Frame::Frame()
	: currentLayerIndex{0}
{

}

// SPRITE CLASS

Sprite::Sprite(int width, int height)
	: width{width}
	, height{height}
	, currentFrameIndex{0}
	, fps{0}
{
	this->addFrame();
}

void Sprite::addFrame()
{
	frames.push_back(Frame(this));
}

void Sprite::selectFrame(int frameIndex)
{
	if (0 >= frameIndex && frameIndex < frames.size())
	{
		currentFrameIndex = frameIndex;
	}
}

void Sprite::removeCurrentFrame()
{
	frames.removeAt(currentFrameIndex);
}

Frame& Sprite::getCurrentFrame()
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
