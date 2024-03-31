#include "timelinepanel.h"

TimelinePanel::TimelinePanel(QWidget *parent)
	: QScrollArea{parent}
{
	frameButtons = new QMap<int, FrameIcon*>();

	layout = new QHBoxLayout();
	layout->setAlignment(Qt::AlignLeft);
	this->setLayout(layout);
}


TimelinePanel::~TimelinePanel()
{
	delete frameButtons;
}

void TimelinePanel::addFrame()
{
	FrameIcon *icon = new FrameIcon();

	int index = frameButtons->size();
	frameButtons->insert(index, icon);

	connect(icon, &QPushButton::clicked, this, [this, index]() {
		emit frameButtonSelected(index);
	});

	layout->addWidget(icon);
}

void TimelinePanel::removeFrame()
{
	if (frameButtons->isEmpty())
		return;

	int lastIndex = frameButtons->size() - 1;

	// Get the key corresponding to the last index
	int lastKey = frameButtons->keys().at(lastIndex);

	if (lastKey > 0)
	{
		// Remove the last element from the map and get the associated FrameIcon pointer
		FrameIcon *iconToRemove = frameButtons->take(lastKey);

		// Remove the widget from the layout
		layout->removeWidget(iconToRemove);

		// Optionally, delete the FrameIcon object to free up memory
		delete iconToRemove;
	}
}

void TimelinePanel::moveLeft()
{
	//TODO: Move an active frame over one poisiton left
	// dont move it left if it's first in the sequence
}

void TimelinePanel::moveRight()
{
	//TODO: Move an active frame over one poisiton Right
	// dont move it right if it's at the end of the sequence
}

void TimelinePanel::setupFrameButtons(int framesCount)
{
	for (auto [key, value] : frameButtons->asKeyValueRange())
	{
		layout->removeWidget(value);
		delete value;
	}

	frameButtons->clear();

	for (int index = 0; index < framesCount; index++)
	{
		this->addFrame();
	}
}
