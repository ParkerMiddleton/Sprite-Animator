#include "frameicon.h"

FrameIcon::FrameIcon(int frameNum, QWidget *parent)
	: QPushButton{parent}
{
	//ICON visual properties
	this->setText(QString::number(frameNum));
	this->setFixedHeight(50);
	this->setFixedWidth(25);

	//stylesheets associated with active status
	highlightIconStylehseet = "background-color: #f5f5f5;color: #000000;padding: 4px;border: 1px solid #ADD8E6";
	regularIconStylesheet = "background-color: #f5f5f5;color: #000000;padding: 4px;border: 1px solid #444444";

	//highlight the first icon on startup
	if (frameNum != 1)
	{
		this->setStyleSheet(regularIconStylesheet);
	}
	else
	{
		this->setStyleSheet(highlightIconStylehseet);
	}
}
