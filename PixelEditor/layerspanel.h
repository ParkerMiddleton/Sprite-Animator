#ifndef LAYERSPANEL_H
#define LAYERSPANEL_H

#include "layericon.h"
/**
 * @authors Tommy Heimer, Egor Chesnokov, Kobe Dato, Parker Middleton, Aditya Mukerjee, Charles WolfGramm.
 *
 * @version 1.0
 * @date 4/1/2024
 */



///
/// \brief The LayersPanel class Represents layer editing
///
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

    /// sets up layer buttons
	void setupLayerButtons(int layersCount);

    ///highlights Icons
    void highlightLayerIcon(int id);

signals:
	void layerButtonSelected(int layerButtonIndex);

private:
	QLayout *layout;
	QMap<int, LayerIcon*> *layerButtons;
    int currentID;
    QString highlightIconStylehseet;
    QString regularIconStylesheet;

};

#endif // LAYERSPANEL_H
