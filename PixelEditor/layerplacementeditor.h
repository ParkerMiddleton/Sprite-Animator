#ifndef LAYERPLACEMENTEDITOR_H
#define LAYERPLACEMENTEDITOR_H

#include "layericon.h"

class LayerPlacementEditor : public QScrollArea
{
    Q_OBJECT

private:
    QLayout *layout;
    QMap<int, LayerIcon*> *layerButtons;


public:
    explicit LayerPlacementEditor(QWidget *parent = nullptr);

public slots:

    ///
    /// \brief addLayer adds a layer to an active frame
    ///
    void addLayer();

    ///
    /// \brief removeLayer removes from the end of a sequence.
    ///
    void removeLayer();


signals:
    void sendLayerIconID(int index);
};

#endif // LAYERPLACEMENTEDITOR_H
