#include "spritemodel.h"

#include "serializer.h"

#include <QJsonObject>
#include <QJsonArray>

//++========================+
// LAYER CLASS DEFINITION

Layer::Layer(uint width, uint height)
	: width(width)
	, height(height)
{
	pixels = new uchar[width * height * 4];
}

Layer::~Layer()
{
	if (pixels) delete[] pixels;
}

void Layer::setPixel(uint x, uint y, QColor color)
{
	uint pxy = x + y * width;

	if (pxy < (width * height))
	{
		pxy *= 4;
		pixels[pxy + 0] = color.red();
		pixels[pxy + 1] = color.green();
		pixels[pxy + 2] = color.blue();
		pixels[pxy + 3] = color.alpha();
	}
}

Layer Layer::fromJson(const QJsonObject &json)
{
	Layer layer;
}

QJsonObject Layer::toJson() const
{
	QJsonObject json;
	QJsonArray pixelsArray;

	for (uint index = 0; index < (width * height); index++)
	{
		QJsonObject pixelJson;
		int pxy = index * 4;
		pixelJson["r"] = pixels[pxy + 0];
		pixelJson["g"] = pixels[pxy + 1];
		pixelJson["b"] = pixels[pxy + 2];
		pixelJson["a"] = pixels[pxy + 3];
		pixelsArray.append(pixelJson);
	}

	json["pixels"] = pixelsArray;

	return json;
}

//++========================+
// FRAME CLASS DEFINITION

Frame::Frame(int width, int height)
	: mergedLayer(width, height)
	, width(width)
	, height(height)
{
	addLayer();
}

void Frame::addLayer()
{
	Layer newLayer(width, height);
	layers.push_back(newLayer);
}

void Frame::removeLayer()
{
	layers.remove(layerIndex);
}

void Frame::setLayerIndex(int input)
{
	layerIndex = input;
}

void Frame::mergeLayers()
{
	Layer tempLayer(width, height);

	for(Layer l:layers)
	{

	}
}

QList<QColor> Frame::getMergedLayer()
{
	return mergedLayer.pixels;
}

QJsonObject Frame::toJson() const
{
	QJsonObject json;
	QJsonArray layersArray;

	for (const Layer &layer : layers)
	{
		layersArray.append(layer.toJson());
	}

	json["layers"] = layersArray;

	return json;
}

//++========================+
// SPRITE CLASS DEFINITION

Sprite::Sprite(int width, int height)
	: width(height)
	, height(height)
{

}

void Sprite::setPixel(int x, int y, int BrushSize)
{

}

void Sprite::erasePixel(int x, int y, int BrushSize)
{

}

void Sprite::addFrame()
{
	frames.push_back(Frame(width, height));
}

void Sprite::nextFrame()
{
	frameIndex++;
}

void Sprite::previousFrame()
{
	frameIndex--;
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
	//Serializer::serialize(*this);
}

void Sprite::loadSprite(QString filePath)
{
	//Serializer::deserialize(filePath, *this);
}

QList<QColor> Sprite::getFrameImage()
{
	return frames[frameIndex].getMergedLayer();
}

QJsonObject Sprite::toJson() const
{
	QJsonObject json;
	json["name"] = name;
	QJsonArray layersArray;

	for (const Frame &frame : frames)
	{
		layersArray.append(frame.toJson());
	}

	json["frames"] = layersArray;

	return json;
}
