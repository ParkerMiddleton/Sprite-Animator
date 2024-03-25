#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QImageWriter>
#include <QPainter>
#include <QColorDialog>
#include <QColor>
#include <QPalette>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_colorPicker_clicked();
    void handleColorSelected(const QColor &color);

signals:
    void colorChanged(const QColor &color);

private:
    Ui::MainWindow *ui;
    QPainter brush;
    QColor currentColor;
    QColorDialog *colorDialog;
};
#endif // MAINWINDOW_H
