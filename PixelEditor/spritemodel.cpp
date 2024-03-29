#include "spritemodel.h"

#include <QJsonObject>
#include <QJsonArray>

Layer::Layer(int width, int height)
{
	int size = width * height;
	QColor empty(0,0,0,0);
	for(int i = 0; i < size; i++){
		pixels.push_back(empty);
	}
}

void Layer::setPixel(QColor color, int index){
	pixels[index] = color;
}

Layer Layer::fromJson(const QJsonObject &json, Sprite *parentSprite)
{
	Layer layer(parentSprite->width, parentSprite->height);

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

// FRAME CLASS

Frame::Frame(int width, int height): mergedLayer(width, height), width(width), height(height) {
	addLayer();
	layerIndex = 0;
}
void Frame::addLayer(){
	Layer newLayer(width, height);
	layers.push_back(newLayer);
}
void Frame::removeLayer(){
	layers.remove(layerIndex);
}
void Frame::setLayerIndex(int input){
	layerIndex = input;
}

void Frame::mergeLayers()
{
	int index = 0;

	for (Layer layer : layers)
	{
		for (QColor color : layer.pixels)
		{
			if (color.alpha() != 0)
			{
				mergedLayer.setPixel(color, index);
			}

			index++;
		}
	}
}

QList<QColor> Frame::getMergedLayer()
{
	this->mergeLayers();
	return mergedLayer.pixels;
}

Frame Frame::fromJson(const QJsonObject &json, Sprite *parentSprite)
{
	Frame frame(parentSprite->width, parentSprite->height);

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

// SPRITE CLASS

Sprite::Sprite(int width, int height)
	: name("untitiled")
	, width(width)
	, height(height)
{
	frameIndex = 0;
	this->addFrame();
}

void Sprite::setPixel(int x, int y, int BrushSize, QColor color)
{
	int index = (x + (y * width));
	frames[frameIndex].layers[frames[frameIndex].layerIndex].setPixel(color, index);

}

void Sprite::erasePixel(int x, int y, int BrushSize)
{
	Frame temp = frames[frameIndex];
	int index = (x + (y * width));
	QColor empty(0,0,0,0);
	temp.layers[temp.layerIndex].setPixel(empty, index);
}

void Sprite::addFrame()
{
	frames.push_back(Frame(width, height));
}

void Sprite::nextFrame()
{
	if (frameIndex + 1 != frames.size())
	{
		frameIndex++;
	}
}

void Sprite::previousFrame()
{
	if (frameIndex == 0)
	{
		frameIndex--;
	}
}

void Sprite::deleteFrame()
{
	frames.removeAt(frameIndex);
}

void Sprite::selectLayer(int layerIndex)
{
	frames[frameIndex].setLayerIndex(layerIndex);
}

void Sprite::addLayerToCurrentFrame()
{
	frames[frameIndex].addLayer();
}

void Sprite::saveSprite()
{

}

void Sprite::loadSprite()
{

}

QList<QColor> Sprite::getFrameImage()
{
	return frames[frameIndex].getMergedLayer();
}

QString Sprite::getName()
{
	return name;
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
	: frameIndex{0}
{

}
