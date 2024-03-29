#include "sprite.h"
#include <QDebug>

Layer::Layer(int width, int height) {
    int size = width * height;
    QColor empty(0,0,0,0);
    for(int i = 0; i < size; i++){
        pixels.push_back(empty);
    }

}

void Layer::setPixel(QColor color, int index){
    pixels[index] = color;
}

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

void Frame::mergeLayers(){
    int index = 0;

    for(Layer& l:layers){
        for(QColor& q: l.pixels){
            //if(q.alpha() != 0){
            mergedLayer.setPixel(q, index);
            //}
            index++;
        }
    }
}
QList<QColor> Frame::getMergedLayer(){
    mergeLayers();
    return mergedLayer.pixels;
}

Sprite::Sprite(int width, int height):width(width),height(height) {
    frameIndex = 0;
    fps = 0;
    addFrame();
}
void Sprite::setPixel(int x, int y, int BrushSize, QColor color){
    //qDebug() << x << y;
    int index = (x + (y * width));
    qDebug() << index;
    frames[frameIndex].layers[frames[frameIndex].layerIndex].setPixel(color, index);

}
void Sprite::erasePixel(int x, int y, int BrushSize){
    Frame temp = frames[frameIndex];
    int index = (x + (y * width));
    QColor empty(0,0,0,0);
    temp.layers[temp.layerIndex].setPixel(empty, index);
}

void Sprite::addFrame(){
    frames.push_back(Frame(width, height));
}

void Sprite::nextFrame(){
    if(frameIndex + 1 != frames.size()){
        frameIndex++;
    }
    fps++;
}

void Sprite::previousFrame(){
    if(frameIndex > 0){
        frameIndex--;
    }
    fps--;
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

}

void Sprite::loadSprite(){

}

QList<QColor> Sprite::getFrameImage(){
    return frames[frameIndex].getMergedLayer();
}

void Sprite::setFrameID(int id){
    frameIndex= id;
}

int Sprite::getFPS(){
    return fps;
}

void Sprite::playAnimation(){


    for(int i = 0; i < frames.size(); i++){

      //  emit // some method that the preview window will recieve,
        // that sends all the data for the merged layer of every frame in the loop.

    }

}

// int main() {
//     // Create a sprite with a width and height of 100
//     Sprite sprite(100, 100);

//     // Add a frame to the sprite
//     sprite.addFrame();

//     // Select the first frame
//     sprite.getFrameImage();

//     // Add a layer to the current frame
//     sprite.addLayerToCurrentFrame();

//     // Set some pixels in the current frame's current layer
//     sprite.setPixel(0, 0, 1, QColor(255, 0, 0, 0)); // Set a red pixel at (10, 10)
//     sprite.setPixel(1, 0, 1, QColor(0, 255, 0, 0)); // Set a green pixel at (20, 20)

//     // Retrieve the merged image of the current frame
//     QList<QColor> mergedImage = sprite.getFrameImage();

//     // Display the merged image
//     std::cout << "Merged Image:" << std::endl;
//     for (int y = 0; y < 99; ++y) {
//         for (int x = 0; x < 99; ++x) {
//             QColor pixelColor = mergedImage[x + y * 99];
//             std::cout << "(" << pixelColor.red() << "," << pixelColor.green() << "," << pixelColor.blue() << ") ";
//         }
//         std::cout << std::endl;
//     }

//     return 0;
// }
