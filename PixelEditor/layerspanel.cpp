#include "layerspanel.h"

LayersPanel::LayersPanel(QWidget *parent)
	: QScrollArea{parent}
{
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	this->verticalScrollBar()->setEnabled(false);

    //stylesheet data
    highlightIconStylehseet = "background-color: #f5f5f5;color: #000000;padding: 4px;border: 2px solid #5cc7d1";
    regularIconStylesheet = "background-color: #f5f5f5;color: #000000;padding: 4px;border: 1px solid #444444";

	currentID = 0;
}

LayersPanel::~LayersPanel()
{
	for (auto [key, value] : layerButtons.asKeyValueRange())
	{
		contentsLayout->removeWidget(value);
		delete value;
	}
}

void LayersPanel::setupLayout(QWidget *contents)
{
	contentsLayout = new QHBoxLayout(contents);
	this->setWidget(contents);
	contentsLayout->setAlignment(Qt::AlignLeft);
	contentsLayout->setSizeConstraint(QLayout::SetMinimumSize);

	this->addLayer();
}

void LayersPanel::addLayer()
{
	int index = layerButtons.size();
    LayerIcon *icon = new LayerIcon(index+1);

	layerButtons.insert(index, icon);

	connect(icon, &QPushButton::clicked, this, [this, index](){
		// Emit the sendIconID signal with the captured index
		emit layerButtonSelected(index);
	});

	highlightLayerIcon(index);
	contentsLayout->addWidget(icon);
}

void LayersPanel::removeLayer()
{
	if (layerButtons.isEmpty())
		return;

	// Get the key corresponding to the last index
	int lastKey = layerButtons.lastKey();

	if (lastKey > 0)
	{
		// Remove the last element from the map and get the associated FrameIcon pointer
		LayerIcon *iconToRemove = layerButtons.take(lastKey);

		// Remove the widget from the layout
		contentsLayout->removeWidget(iconToRemove);

		// Optionally, delete the FrameIcon object to free up memory
		delete iconToRemove;
	}

	if (currentID != 0 && currentID == lastKey)
	{
		this->highlightLayerIcon(currentID - 1);
	}
}

void LayersPanel::setupLayerButtons(int layersCount)
{
	for (auto [key, value] : layerButtons.asKeyValueRange())
	{
		contentsLayout->removeWidget(value);
		delete value;
	}

	layerButtons.clear();

	for (int index = 0; index < layersCount; index++)
	{
		this->addLayer();
	}
}

void LayersPanel::highlightLayerIcon(int id)
{
	for (auto [key, value] : layerButtons.asKeyValueRange())
	{
		if (key != id)
		{
			value->setStyleSheet(regularIconStylesheet);
		}
		else
		{
			value->setStyleSheet(highlightIconStylehseet);
			currentID = id;
		}
	}
}

void LayersPanel::wheelEvent(QWheelEvent *event)
{
	if (event->angleDelta().y() < 0)
	{
		this->horizontalScrollBar()->triggerAction(QAbstractSlider::SliderAction::SliderPageStepSub);
	}
	else if (event->angleDelta().y() > 0)
	{
		this->horizontalScrollBar()->triggerAction(QAbstractSlider::SliderAction::SliderPageStepAdd);
	}
}
