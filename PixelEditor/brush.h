#ifndef BRUSH_H
#define BRUSH_H

#include <QObject>
#include <QLabel>
#include <QPaintDevice>
#include "mainwindow.h"

class Brush : public QObject {
    Q_OBJECT
public:
    // Constructor
    explicit Brush(int size = 1, QColor color = Qt::black, QObject *parent = nullptr);


    // Destructor
    ~Brush();

    // Getters
    int getSize();
    QColor getColor();

public slots:
    // Slot to set the size of the brush
    void setSize(int size);

    // Slot to set the color of the brush
    void setColor(const QColor &color);

private:
    MainWindow *mainWindowPointer;
    int brushSize;             // Size of the brush
    QColor brushColor;

};
#endif // BRUSH_H
