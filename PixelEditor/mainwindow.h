#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "previewwindow.h"
#include "viewport.h"
#include "frametimeline.h"

class Editor;



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	MainWindow(Editor *editor, QWidget *parent = nullptr);
	~MainWindow();

public slots:
	void changeColor();

	void updateTitle(const QString &spriteName, bool showStar);

	void handleCreateNewSprite(bool askUserToSave);
	void handleOpenSprite(bool askUserToSave);

	// Menu bar
	void on_actionSaveSprite_triggered();
	void on_actionSaveSpriteAs_triggered();

signals:
	void colorChanged(const QColor &color);

	void newSpriteRequested();
	void loadRequested(const QString &filename);
	void saveRequested(const QString &filename);

private:
	Ui::MainWindow *ui;
	Editor *editor;

	Viewport *vp;
	PreviewWindow *pw;
	FrameTimeline *ft;

	QColorDialog *colorDialog;

	QMenu *fileMenu;
	QActionGroup *alignmentGroup;
	QAction *newAct;
	QAction *openAct;
	QAction *saveAct;
	QAction *saveAsAct;

	QColor currentColor;

	void createActions();
	void createMenus();

};
#endif // MAINWINDOW_H
