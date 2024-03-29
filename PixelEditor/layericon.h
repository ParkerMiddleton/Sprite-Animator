#ifndef LAYERICON_H
#define LAYERICON_H

#include <QWidget>
#include <QPushButton>

class LayerIcon : public QPushButton
{
    Q_OBJECT
public:
    explicit LayerIcon(QWidget *parent = nullptr);

signals:
};

#endif // LAYERICON_H
