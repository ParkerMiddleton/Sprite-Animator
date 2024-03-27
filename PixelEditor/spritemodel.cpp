#include "spritemodel.h"

#include <QJsonObject>
#include <QJsonArray>

//++========================+
// LAYER CLASS DEFINITION

Layer::Layer(Sprite *parentSprite)
	: parentSprite(parentSprite)
{
	pixels.resize(this->parentSprite->getWidth() * this->parentSprite->getHeight());
}

void Layer::setPixel(int x, int y, QColor color, int brushSize)
{
	pixels[x + y * parentSprite->getWidth()] = color;
}

Layer Layer::fromJson(const QJsonObject &json, Sprite *parentSprite)
{
	Layer layer(parentSprite);

	if (const QJsonValue &jsonVal = json["pixels"]; jsonVal.isArray())
	{
		const QJsonArray &jsonPixels = jsonVal.toArray();

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

//++========================+
// FRAME CLASS DEFINITION

Frame::Frame(Sprite *parentSprite)
	: parentSprite(parentSprite)
{
	this->addLayer();
}

void Frame::addLayer()
{
	layers.push_back(Layer(parentSprite));
}

void Frame::removeLayer()
{
	layers.remove(currentLayerIndex);
}

void Frame::selectLayer(int layerIndex)
{
	currentLayerIndex = layerIndex;
}

void Frame::mergeLayers()
{
	Layer tempLayer(parentSprite);

	for (Layer l:layers)
	{

	}
}

QList<QColor> Frame::getImage()
{
	return mergedLayer->pixels;
}

Frame Frame::fromJson(const QJsonObject &json, Sprite *parentSprite)
{
	Frame frame(parentSprite);

	if (const QJsonValue &jsonVal = json["layers"]; jsonVal.isArray())
	{
		const QJsonArray &jsonLayers = jsonVal.toArray();
		frame.layers.reserve(jsonLayers.size());

		for (const QJsonValue &jsonLayerVal : jsonLayers)
			frame.layers.append(Layer::fromJson(jsonLayerVal.toObject(), parentSprite));
	}

	return frame;
}

QJsonObject Frame::toJson() const
{
	QJsonObject json;
	QJsonArray jsonLayers;

	for (const Layer &layer : layers)
	{
		jsonLayers.append(layer.toJson());
	}

	json["layers"] = jsonLayers;

	return json;
}

//++========================+
// SPRITE CLASS DEFINITION

Sprite::Sprite(int width, int height)
	: width(width)
	, height(height)
{

}

void Sprite::addFrame()
{
	frames.push_back(Frame(this));
}

void Sprite::moveFrameForward()
{
	// List manipulation.
}

void Sprite::moveFrameBackward()
{
	// List manipulation.
}

void Sprite::removeFrame()
{
	frames.removeAt(currentFrameIndex);
}

void Sprite::selectFrame(int frameIndex)
{
	currentFrameIndex = frameIndex;
}

QString Sprite::getName()
{
	return name;
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

	const QJsonValue &jsonName = json["name"];
	const QJsonValue &jsonWidth = json["width"];
	const QJsonValue &jsonHeight = json["height"];

	if (jsonName.isString() &&
		jsonWidth.isDouble() &&
		jsonHeight.isDouble())
	{
		sprite = new Sprite();

		sprite->name = jsonName.toString();
		sprite->width = jsonWidth.toInt();
		sprite->height = jsonHeight.toInt();

		if (const QJsonValue jsonFramesVal = json["frams"]; jsonFramesVal.isArray())
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
	json["name"] = name;
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
{

}
