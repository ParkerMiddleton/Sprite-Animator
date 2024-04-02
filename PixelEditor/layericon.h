#ifndef LAYERICON_H
#define LAYERICON_H

/**
 * @authors Tommy Heimer, Egor Chesnokov, Koby Dato, Parker Middleton, Aditya Mukerjee, Charles WolfGramm.
 *
 * @version 1.0
 * @date 4/1/2024
 */

///
/// \brief The LayerIcon class Represents the clickable icon a layer within a frame
///
class LayerIcon : public QPushButton
{
	Q_OBJECT

public:
	///
	/// \brief Constructor.
	/// \param numLayer index of layer.
	/// \param parent parent of this widget.
	///
	explicit LayerIcon(int layerNum, QWidget *parent = nullptr);

private:
	QString highlightIconStylehseet;
	QString regularIconStylesheet;

};

#endif // LAYERICON_H
