#include "brush.h"
//#include "mainwindow.h"
#include <iostream> // For printing



// Constructor
// In the Brush class constructor implementation (brush.cpp)
Brush::Brush(int size, QColor color, QObject *parent)
    : QObject(parent), mainWindowPointer(nullptr), brushSize(size), brushColor(color)
{
    // set color based off of signal sent from view
    // connect(static_cast<MainWindow*>(parent), &MainWindow::colorChanged,
    //         this, &Brush::setColor);
}

// Destructor
Brush::~Brush() {}

// Getters
int Brush::getSize() {
    return brushSize;
}

QColor Brush::getColor() {
    return brushColor;
}

// Slot to set the size of the brush
void Brush::setSize(int size) {
    brushSize = size;
    std::cout << "Brush size set to: " << size << std::endl; // Print statement
}

// Slot to set the color of the brush
void Brush::setColor(const QColor &color) {
    brushColor = color;
    std::cout << "Brush color set to: "
              << "RGB(" << color.red() << ", " << color.green() << ", " << color.blue() << ")"
              << " Alpha: " << color.alpha()
              << std::endl;
}
