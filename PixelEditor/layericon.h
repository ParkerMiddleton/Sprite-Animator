#ifndef LAYERICON_H
#define LAYERICON_H

#include <QWidget>
#include <QPushButton>

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
