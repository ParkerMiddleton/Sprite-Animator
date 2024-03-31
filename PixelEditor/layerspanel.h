#ifndef LAYERSPANEL_H
#define LAYERSPANEL_H

#include "layericon.h"

class LayersPanel : public QScrollArea
{
	Q_OBJECT

public:
	explicit LayersPanel(QWidget *parent = nullptr);

public slots:
	/// \brief addLayer adds a layer to an active frame
	void addLayer();

	/// \brief removeLayer removes from the end of a sequence.
	void removeLayer();

	void setupLayerButtons(int layersCount);

signals:
	void layerButtonSelected(int layerButtonIndex);

private:
	QLayout *layout;
	QMap<int, LayerIcon*> *layerButtons;

};

#endif // LAYERSPANEL_H
