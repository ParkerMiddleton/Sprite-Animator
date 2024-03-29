#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class EditorModel;

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(EditorModel *editor, QWidget *parent = nullptr);
	~MainWindow();

public slots:
	void changeColor();

signals:
	void spriteCreationRequested();
	void colorChanged(const QColor &color);

	void openClicked(const QFileInfo &filePath);
	void saveClicked();
	void saveAsClicked(const QFileInfo &filePath);

private slots:
	void on_actionOpenSprite_triggered();
	void on_actionSaveSprite_triggered();
	void on_actionSaveSpriteAs_triggered();

	void on_actionNew_triggered();

private:
	Ui::MainWindow *ui;
	EditorModel *editor;
	QPainter brush;
	QColor currentColor;
	QColorDialog *colorDialog;

};

#endif // MAINWINDOW_H
