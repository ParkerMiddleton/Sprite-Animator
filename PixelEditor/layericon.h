#ifndef LAYERICON_H
#define LAYERICON_H

#include <QWidget>
#include <QPushButton>
/**
 * @authors Tommy Heimer, Egor Chesnokov, Kobe Dato, Parker Middleton, Aditya Mukerjee, Charles WolfGramm.
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

    QString highlightIconStylehseet;
    QString regularIconStylesheet;

public:
    explicit LayerIcon(int numLayer, QWidget *parent = nullptr);

signals:
};

#endif // LAYERICON_H
