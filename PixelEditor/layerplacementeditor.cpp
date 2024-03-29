#include "layerplacementeditor.h"


LayerPlacementEditor::LayerPlacementEditor(QWidget *parent)
    : QScrollArea{parent}
{
    layout = new QHBoxLayout();
    layout->setAlignment(Qt::AlignLeft); // all new buttons start from left
    this->setLayout(layout);

}

void LayerPlacementEditor::addLayer(){
    // find out what the active frame is in the edit window, and subsequent backing
    // data structre, to add a layer to.

    //add layer to backend

    // add a layerIcon

    LayerIcon *icon = new LayerIcon();
    layout->addWidget(icon);
}

void LayerPlacementEditor::removeLayer(){

    //TODO:
}
