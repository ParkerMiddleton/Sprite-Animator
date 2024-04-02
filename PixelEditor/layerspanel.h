#ifndef LAYERSPANEL_H
#define LAYERSPANEL_H

#include "layericon.h"
/**
 * @authors Tommy Heimer, Egor Chesnokov, Koby Dato, Parker Middleton, Aditya Mukerjee, Charles WolfGramm.
 *
 * @version 1.0
 * @date 4/1/2024
 */

///
/// \brief Represents layer editing.
///
class LayersPanel : public QScrollArea
{
	Q_OBJECT

public:
	///
	/// \brief Contructor.
	/// \param parent parent of this widget.
	///
	explicit LayersPanel(QWidget *parent = nullptr);

	///
	/// \brief Destructor.
	///
	~LayersPanel();

	///
	/// \brief Setups the layout of this widget. Must be called after the contructor.
	/// \param contents content of the QScrollArea
	///
	void setupLayout(QWidget *contents);

public slots:
	///
	/// \brief Adds the current layer button to the timeline.
	///
	void addLayer();

	///
	/// \brief Removes the current layer button from the timeline.
	///
	void removeLayer();

	///
	/// \brief Adds a specified number of layer buttons to the layers panel.
	/// \param layersCount How many buttons to add.
	///
	void setupLayerButtons(int layersCount);

	///
	/// \brief Highlights a layer that have been clicked on so the user knows which layer is currently being worked on.
	/// \param id id of the layer button.
	///
    void highlightLayerIcon(int id);

signals:
	/// \brief On layer button selected.
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
