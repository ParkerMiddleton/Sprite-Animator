#ifndef FRAMEWINDOW_H
#define FRAMEWINDOW_H


#include <QLabel>
#include <QPaintDevice>
#include <QPixmap>

class FrameWindow : public QLabel
{

    Q_OBJECT


private:


public:
    FrameWindow(QWidget *parent = 0);
    ~FrameWindow();


protected:
    // void paintEvent(QPaintEvent *e) override;
    // void mousePressEvent(QMouseEvent *event) override;
    // void mouseReleaseEvent(QMouseEvent *event) override;
    // void mouseMoveEvent(QMouseEvent *event)override;
    // void resizeEvent(QResizeEvent *event)override;



};



#endif // FRAMEWINDOW_H
