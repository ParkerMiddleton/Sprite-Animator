#include "layericon.h"

LayerIcon::LayerIcon(int layerNum, QWidget *parent)
	: QPushButton{parent}
{
	// button attributes
	this->setText(QString::number(layerNum));
	this->setFixedHeight(100);
	this->setFixedHeight(25);

	//stylesheets associated with active status
	highlightIconStylehseet = "background-color: #f5f5f5;color: #000000;padding: 4px;border: 2px solid #5cc7d1";
	regularIconStylesheet = "background-color: #f5f5f5;color: #000000;padding: 4px;border: 1px solid #444444";

	//highlight the first icon on startup
	if (layerNum != 1)
	{
		this->setStyleSheet(regularIconStylesheet);
	}
	else
	{
		this->setStyleSheet(highlightIconStylehseet);
	}
}
