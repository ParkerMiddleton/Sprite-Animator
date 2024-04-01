#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "previewpanel.h"
#include "viewport.h"
#include "timelinepanel.h"
#include "layerspanel.h"
#include "createnewspritedialog.h"

class Editor;

//asdasd

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
	void initializeSaveProcess();
	void initializeSaveProcessWithDialogue();

    void highlightButton(QPushButton *button);
    void getFPS(int fps);

signals:
    void colorChanged(const QColor &color);
    void BrushSizeChanged(int brushSize);

	void newSpriteRequested(int width, int height);
    void loadRequested(const QString &filename);
    void saveRequested(const QString &filename);

private:
    Ui::MainWindow *ui;
    Editor *editor;

    Viewport *vp;
	PreviewPanel *pw;
	TimelinePanel *ft;
	LayersPanel *lt;

    QMenu *fileMenu;
    QMenu *helpMenu;
    QActionGroup *alignmentGroup;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *helpAct;

    QColor currentColor;
    QMap<QPushButton*, QString> buttonStylesheets;

	int prevNewWidth;
	int prevNewHeight;

    void createActions();
    void createMenus();
    void openHelpWindow();
    void resetButtonStyles(QPushButton *button);

};
#endif // MAINWINDOW_H
