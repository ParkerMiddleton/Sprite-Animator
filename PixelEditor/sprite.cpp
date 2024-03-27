#include "sprite.h"
#include "serializer.h"
Layer::Layer(int width, int height) {
    pixels.resize(height * width);
}

void Layer::setPixel(int r, int g, int b, int a, int x, int y){
    pixels[x + (y * x)] = QColor(r, g, b, a);
}

Frame::Frame(int width, int height): mergedLayer(width, height), width(width), height(height) {
    addLayer();
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

void Frame::mergeLayers(){
    Layer tempLayer(width, height);
    for(Layer l:layers){

    }
}
QList<QColor> Frame::getMergedLayer(){
    return mergedLayer.pixels;
}



Sprite::Sprite(int width, int height):width(height),height(height) {

}
void Sprite::setPixel(int x, int y, int BrushSize){

}
void Sprite::erasePixel(int x, int y, int BrushSize){

}

void Sprite::addFrame(){
    frames.push_back(Frame(width, height));
}
void Sprite::nextFrame(){
    frameIndex++;
}

void Sprite::previousFrame(){
    frameIndex--;
}

void Sprite::deleteFrame(){
    frames.removeAt(frameIndex);
}

void Sprite::selectLayer(int layerIndex){
    frames[frameIndex].setLayerIndex(layerIndex);
}

void Sprite::addLayerToCurrentFrame(){
    frames[frameIndex].addLayer();
}
void Sprite::saveSprite(){
    Serializer::serialize(*this);
}

void Sprite::loadSprite(){

}

QList<QColor> Sprite::getFrameImage(){
    return frames[frameIndex].getMergedLayer();
}
