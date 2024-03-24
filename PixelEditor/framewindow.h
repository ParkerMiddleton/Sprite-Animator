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

    void draw(QMouseEvent *e);

public:
    FrameWindow(QWidget *parent = 0);
    ~FrameWindow();

public slots:
    void setDrawingColor(const QColor &newColor);

protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e)override;
    // void resizeEvent(QResizeEvent *event)override;



};



#endif // FRAMEWINDOW_H
