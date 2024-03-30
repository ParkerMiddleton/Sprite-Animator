#ifndef LAYERPLACEMENTEDITOR_H
#define LAYERPLACEMENTEDITOR_H

#include "layericon.h"

class LayerPlacementEditor : public QScrollArea
{
    Q_OBJECT

private:
    QLayout *layout;


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
};

#endif // LAYERPLACEMENTEDITOR_H
