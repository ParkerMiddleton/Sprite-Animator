#ifndef PREVIEWWINDOW_H
#define PREVIEWWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPainter>


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

public:
    explicit PreviewWindow(QWidget *parent = nullptr);



public slots:

    ///
    /// \brief recievePixmapData
    /// \param sentPixmap
    ///
    void recievePixmapData(QPixmap *sentPixmap);


protected:
    void paintEvent(QPaintEvent *e) override;

};

#endif // PREVIEWWINDOW_H
