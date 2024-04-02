#include "timelinepanel.h"

TimelinePanel::TimelinePanel(QWidget *parent)
	: QScrollArea{parent}
{
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	this->verticalScrollBar()->setEnabled(false);

    //stylesheet data
    highlightIconStylehseet = "background-color: #f5f5f5;color: #000000;padding: 4px;border: 2px solid #5cc7d1";
    regularIconStylesheet = "background-color: #f5f5f5;color: #000000;padding: 4px;border: 1px solid #444444";

    //gets first button to represent the starting frame
	currentID = 0;
}

TimelinePanel::~TimelinePanel()
{
	for (auto [key, value] : frameButtons.asKeyValueRange())
	{
		contentsLayout->removeWidget(value);
		delete value;
	}
}

void TimelinePanel::setupLayout(QWidget *contents)
{
	contentsLayout = new QHBoxLayout(contents);
	this->setWidget(contents);
	contentsLayout->setAlignment(Qt::AlignLeft);
	contentsLayout->setSizeConstraint(QLayout::SetMinimumSize);

	this->addFrame();
}

void TimelinePanel::addFrame()
{
	int index = frameButtons.size();
	FrameIcon *icon = new FrameIcon(index + 1);

	frameButtons.insert(index, icon);

	connect(icon, &QPushButton::clicked, this, [this, index]() {
        emit frameButtonSelected(index);
	});

	this->highlightFrameIcon(index);
	contentsLayout->addWidget(icon);

	this->horizontalScrollBar()->triggerAction(QAbstractSlider::SliderAction::SliderPageStepAdd);
}

void TimelinePanel::removeFrame()
{
	if (frameButtons.isEmpty())
		return;

	// Get the key corresponding to the last index
	int lastKey = frameButtons.lastKey();

	if (lastKey > 0)
	{
		// Remove the last element from the map and get the associated FrameIcon pointer
		FrameIcon *iconToRemove = frameButtons.take(lastKey);

		// Remove the widget from the layout
		contentsLayout->removeWidget(iconToRemove);

		// Optionally, delete the FrameIcon object to free up memory
		delete iconToRemove;
	}

	if (currentID != 0 && currentID == lastKey)
	{
		this->highlightFrameIcon(currentID - 1);
	}
}

void TimelinePanel::moveLeft()
{
	if (currentID > 0)
	{
		highlightFrameIcon(currentID - 1);
    }
}

void TimelinePanel::moveRight()
{
	if (currentID < frameButtons.size() -1)
	{
        highlightFrameIcon(currentID + 1);
    }
}

void TimelinePanel::setupFrameButtons(int framesCount)
{
	for (auto [key, value] : frameButtons.asKeyValueRange())
	{
		contentsLayout->removeWidget(value);
		delete value;
	}

	frameButtons.clear();

	for (int index = 0; index < framesCount; index++)
	{
		this->addFrame();
	}
}

void TimelinePanel::highlightFrameIcon(int id)
{
	for (auto [key, value] : frameButtons.asKeyValueRange())
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

void TimelinePanel::wheelEvent(QWheelEvent *event)
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

