#include "layerspanel.h"

LayersPanel::LayersPanel(QWidget *parent)
	: QScrollArea{parent}
{
	layerButtons = new QMap<int, LayerIcon*>();
	layout = new QHBoxLayout();
	layout->setAlignment(Qt::AlignLeft); // all new buttons start from left
	this->setLayout(layout);

    //stylesheet data
    highlightIconStylehseet = "background-color: #f5f5f5;color: #000000;padding: 4px;border: 2px solid #5cc7d1";
    regularIconStylesheet = "background-color: #f5f5f5;color: #000000;padding: 4px;border: 1px solid #444444";

    currentID= 0;


    addLayer();
}

void LayersPanel::addLayer()
{

    int index = layerButtons->size();
    LayerIcon *icon = new LayerIcon(index+1);

	layerButtons->insert(index, icon);

	connect(icon, &QPushButton::clicked, this, [this, index](){
		// Emit the sendIconID signal with the captured index
		emit layerButtonSelected(index);
	});

	layout->addWidget(icon);
}

void LayersPanel::removeLayer()
{
	if (layerButtons->isEmpty())
	{
		// The map is already empty, nothing to remove
		return;
	}

	// Get the last index
	int lastIndex = layerButtons->size() - 1;

	// Get the key corresponding to the last index
	int lastKey = layerButtons->keys().at(lastIndex);

	if (lastKey > 0)
	{
		// Remove the last element from the map and get the associated FrameIcon pointer
		LayerIcon *iconToRemove = layerButtons->take(lastKey);

		// Remove the widget from the layout
		layout->removeWidget(iconToRemove);

		// Optionally, delete the FrameIcon object to free up memory
		delete iconToRemove;
	}
}

void LayersPanel::setupLayerButtons(int layersCount)
{
	for (auto [key, value] : layerButtons->asKeyValueRange())
	{
		layout->removeWidget(value);
		delete value;
	}

	layerButtons->clear();

	for (int index = 0; index < layersCount; index++)
	{
		this->addLayer();
	}
}

void LayersPanel::highlightLayerIcon(int id){

    QMap<int, LayerIcon*>::iterator it;
    for(it = layerButtons->begin(); it !=layerButtons->end(); ++it){

        int key = it.key();
        LayerIcon* value = it.value();

        if (key != id) {
            value->setStyleSheet(regularIconStylesheet);
        } else {
            value->setStyleSheet(highlightIconStylehseet);
            currentID = id;
        }

    }
}





