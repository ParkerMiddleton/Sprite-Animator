#include "layerplacementeditor.h"


LayerPlacementEditor::LayerPlacementEditor(QWidget *parent)
    : QScrollArea{parent}
{
    layerButtons = new QMap<int, LayerIcon*>();
    layout = new QHBoxLayout();
    layout->setAlignment(Qt::AlignLeft); // all new buttons start from left
    this->setLayout(layout);

    addLayer();
}

void LayerPlacementEditor::addLayer(){
    LayerIcon *icon = new LayerIcon();

    int index = layerButtons->size();
    layerButtons->insert(index, icon);

    connect(icon, &QPushButton::clicked, this, [this, index]() {
        // Emit the sendIconID signal with the captured index
        emit sendLayerIconID(index);
    });
    layout->addWidget(icon);
}

void LayerPlacementEditor::removeLayer(){
    if (layerButtons->isEmpty()) {
        // The map is already empty, nothing to remove
        return;
    }

    // Get the last index
    int lastIndex = layerButtons->size() - 1;

    // Get the key corresponding to the last index
    int lastKey = layerButtons->keys().at(lastIndex);

    if(lastKey > 0) {
        // Remove the last element from the map and get the associated FrameIcon pointer
        LayerIcon *iconToRemove = layerButtons->take(lastKey);

        // Remove the widget from the layout
        layout->removeWidget(iconToRemove);

        // Optionally, delete the FrameIcon object to free up memory
        delete iconToRemove;
    }
}
