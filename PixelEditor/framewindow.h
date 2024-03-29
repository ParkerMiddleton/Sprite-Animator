#ifndef FRAMEWINDOW_H
#define FRAMEWINDOW_H


#include <QLabel>
#include <QPaintDevice>
#include <QPixmap>
#include <QMouseEvent>
#include "sprite.h"

class FrameWindow : public QLabel
{

    Q_OBJECT


private:
    QPixmap *pixmap;
    QColor color;
    Sprite *sprite;
    int pressed;
    bool pencilEnabled;
    bool eraserEnabled; // actually disables and enables
    QMap<QString, Sprite*> sprites;
    QString spriteName;
    void draw(QMouseEvent *e);

public:
    explicit FrameWindow(QWidget *parent = 0);
    ~FrameWindow();
    void drawFrame(int x, int y, int spriteX, int spriteY);
    void loadFrame();
    void erase(int x, int y);
    int frameWidth;
    int frameHeight;

public slots:
    void setDrawingColor(const QColor &newColor);
    void setBrushEnabled();
    void setEraserEnabled();
    void newFrame();
    void loadPreviousFrame();
    void displayActiveFrame(int id);
    void sendSprite();


signals:
    void informViewOfPencilEnabled(bool);
    void sendPixmapData(QPixmap *p);
    void sendData(Sprite *s);

protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e)override;
    // void resizeEvent(QResizeEvent *event)override;
};



#endif // FRAMEWINDOW_H
