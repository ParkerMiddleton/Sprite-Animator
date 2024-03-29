#include "frametimeline.h"
#include <QDebug>

FrameTimeline::FrameTimeline(QWidget *parent)
    : QScrollArea{parent}
{

    framesInUse = new QMap<int, FrameIcon*>();

    layout= new QHBoxLayout();
    this->setLayout(layout);

    //gets first button to represent the starting frame
    addFrame();

}


FrameTimeline::~FrameTimeline(){
    if(framesInUse){
        delete framesInUse;
    }
}


void FrameTimeline::addFrame(){

    FrameIcon *icon = new FrameIcon();

    int index = framesInUse->size();
    framesInUse->insert(index, icon);

    connect(icon, &QPushButton::clicked, this, [this, index]() {
        // Emit the sendIconID signal with the captured index
        emit sendIconID(index);
    });

    layout->addWidget(icon);


}

void FrameTimeline::removeFrame(){

    //Going to need to get the frame ID for an exisiting frame object
    // this data will come from the sprite model

    //TODO: 1) Get the id of the last frame in the sequence
    //      2) create a Frame Icon object with that same ID but use it to
    //         remove the widget using the layout->removeWidget(someIcon)

}

void FrameTimeline::moveLeft(){
    //TODO: Move an active frame over one poisiton left
    // dont move it left if it's first in the sequence
}

void FrameTimeline::moveRight(){
    //TODO: Move an active frame over one poisiton Right
    // dont move it right if it's at the end of the sequence
}

// void FrameTimeline::sendIconInformation(){


//     emit sendIconID(); // an active frame
// }
