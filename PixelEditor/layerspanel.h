#ifndef LAYERSPANEL_H
#define LAYERSPANEL_H

#include "layericon.h"

class LayersPanel : public QScrollArea
{
	Q_OBJECT

public:
	explicit LayersPanel(QWidget *parent = nullptr);
	~LayersPanel();

	void setupLayout(QWidget *contents);

public slots:
	/// \brief addLayer adds a layer to an active frame
	void addLayer();

	/// \brief removeLayer removes from the end of a sequence.
	void removeLayer();

	void setupLayerButtons(int layersCount);

    void highlightLayerIcon(int id);

signals:
	void layerButtonSelected(int layerButtonIndex);

protected:
	void wheelEvent(QWheelEvent *event) override;

private:
	QHBoxLayout *contentsLayout;
	QMap<int, LayerIcon*> *layerButtons;

    int currentID;
    QString highlightIconStylehseet;
    QString regularIconStylesheet;

};

#endif // LAYERSPANEL_H
