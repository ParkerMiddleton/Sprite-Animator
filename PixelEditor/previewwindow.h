#ifndef PREVIEWWINDOW_H
#define PREVIEWWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include "Sprite.h"


///
/// \brief This class will always mirror the currently edited frame from the canvas window
/// It will also allow for "playing" annimations between all the current frames.
///
///
class PreviewWindow : public QLabel
{
    Q_OBJECT
private:
    QPixmap *currentPixmap;
    Sprite *sprite;

public:
    explicit PreviewWindow(QWidget *parent = nullptr);

    void playAnimation();

public slots:
<<<<<<< Updated upstream

    ///
    /// \brief recievePixmapData
    /// \param sentPixmap
    ///
    void recievePixmapData(QPixmap *sentPixmap);
=======
>>>>>>> Stashed changes

    void recievePixmapData(QPixmap *sentPixmap);
    void recieveSpriteData(Sprite *data);

protected:
    void paintEvent(QPaintEvent *e) override;

};

#endif // PREVIEWWINDOW_H
