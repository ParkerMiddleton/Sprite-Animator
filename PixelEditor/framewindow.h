#ifndef FRAMEWINDOW_H
#define FRAMEWINDOW_H


#include <QLabel>
#include <QPaintDevice>
#include <QPixmap>
#include <QMouseEvent>

class FrameWindow : public QLabel
{

    Q_OBJECT


private:
    QPixmap *pixmap;
    QColor color;
    int pressed;
    bool pencilEnabled;
    bool eraserEnabled; // actually disables and enables

    void draw(QMouseEvent *e);

public:
    ///
    /// \brief FrameWindow Constructor
    /// \param parent
    ///
    explicit FrameWindow(QWidget *parent = nullptr);

    ///
    /// \brief Destructs a FrameWindow object for safe
    /// memory managment
    ///
    ~FrameWindow();

public slots:

    void setDrawingColor(const QColor &newColor);
    void setBrushEnabled();
    void setEraserEnabled();

signals:
    void informViewOfPencilEnabled(bool);

    ///
    /// \brief sendPixmapData sends data of the current Pixmap
    /// to anyone who wishes to recieve it
    /// \param p the active pixmap
    ///
    void sendPixmapData(QPixmap *p);

protected:

    ///
    /// \brief paintEvent A paint event happens whenever the user
    /// uses a QPainter on an object that accepts it
    /// \param e Event
    ///
    void paintEvent(QPaintEvent *e) override;

    ///
    /// \brief mousePressEvent triggers whenever a mouse is clicked
    /// \param e Event
    ///
    void mousePressEvent(QMouseEvent *e) override;

    ///
    /// \brief mouseReleaseEvent triggers whenever a mouse is released
    /// from a click
    /// \param e Event
    ///
    void mouseReleaseEvent(QMouseEvent *e) override;

    ///
    /// \brief mouseMoveEvent triggers whenever a mouse is released
    /// from a click
    /// \param e
    ///
    void mouseMoveEvent(QMouseEvent *e)override;

};



#endif // FRAMEWINDOW_H
