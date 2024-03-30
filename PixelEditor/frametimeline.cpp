#include "frametimeline.h"

FrameTimeline::FrameTimeline(QWidget *parent)
	: QScrollArea{parent}
{

	framesInUse = new QMap<int, FrameIcon*>();

	layout= new QHBoxLayout();
	layout->setAlignment(Qt::AlignLeft);
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

	connect(icon, &QPushButton::clicked, this, [this, index]()
			{
				// Emit the sendIconID signal with the captured index
				QTextStream(stdout) << index << "\n";
				emit sendIconID(index);
			});

	layout->addWidget(icon);


}

void FrameTimeline::removeFrame() {
    if (framesInUse->isEmpty()) {
        // The map is already empty, nothing to remove
        return;
    }

    // Get the last index
    int lastIndex = framesInUse->size() - 1;

    // Get the key corresponding to the last index
    int lastKey = framesInUse->keys().at(lastIndex);

    if(lastKey > 0) {
        // Remove the last element from the map and get the associated FrameIcon pointer
        FrameIcon *iconToRemove = framesInUse->take(lastKey);

        // Remove the widget from the layout
        layout->removeWidget(iconToRemove);

        // Optionally, delete the FrameIcon object to free up memory
        delete iconToRemove;
    }
}

void FrameTimeline::moveLeft(){
	//TODO: Move an active frame over one poisiton left
	// dont move it left if it's first in the sequence
}

void FrameTimeline::moveRight(){
	//TODO: Move an active frame over one poisiton Right
	// dont move it right if it's at the end of the sequence
}

