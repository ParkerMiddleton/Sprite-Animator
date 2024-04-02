#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "previewpanel.h"
#include "viewport.h"
#include "timelinepanel.h"
#include "layerspanel.h"

/**
 * @authors Tommy Heimer, Egor Chesnokov, Koby Dato, Parker Middleton, Aditya Mukerjee, Charles WolfGramm.
 *
 * @version 1.0
 * @date 4/1/2024
 */

class Editor;

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

///
/// \brief The MainWindow class.
///
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	///
	/// \brief Constructor
	/// \param editor Pointer to model.
	/// \param parent
	///
	MainWindow(Editor *editor, QWidget *parent = nullptr);

	///
	/// Destructor.
	///
	~MainWindow();

public slots:

	///
	/// \brief changeColor changes the current color
	///
	void changeColor();

	///
	/// \brief Updates the title of the main window.
	/// \param spriteName names of the sprite to display.
	/// \param showStar if true, shows the star that indicates that the file is modified and unsaved.
	///
	void updateTitle(const QString &spriteName, bool showStar);

	///
	/// \brief Initializes the create new sprite routine.
	/// \param askUserToSave if true, shows dialog to ask if the user wants to save.
	///
	void handleCreateNewSprite(bool askUserToSave);

	///
	/// \brief Initializes the open sprite routine.
	/// \param askUserToSave if true, shows dialog to ask if the user wants to save.
	///
	void handleOpenSprite(bool askUserToSave);

	///
	/// \brief Initializes the save sprite routine.
	///
	void initializeSaveProcess();

	///
	/// \brief Initializes the save sprite with dialog routine.
	///
	void initializeSaveProcessWithDialogue();

	///
	/// \brief Highlights specified button.
	/// \param button button to highlight
	///
	void highlightButton(QPushButton *button);

	///
	/// \brief Sends signal to preview window to display current fps.
	/// \param fps fps to display
	///
	void getFPS(int fps);

	///
	/// \brief setActiveFrameID Listens for an id to be sent
	/// from a Frame Button to update the view with a highlight
	/// indicating the frame is active.
	/// \param id ID of the frame button
	///
	void setActiveFrameID(int id);

	///
	/// \brief setActiveLayerID Listens for an id to be sent from a
	/// Layer Button to update the view with a highlight indicating
	/// the frame is active.
	/// \param id ID of the Layer
	///
	void setActiveLayerID(int id);

	///
	/// \brief Updates the text of the pencil to reflect size changes
	/// \param id id of eraser number
	///
	void setPencilText(int id);

	///
	/// \brief Updates the text of the eraser to reflect size changes
	/// \param id id of eraser number
	///
	void setEraserText(int id);


signals:
	/// On color changed.
	void colorChanged(const QColor &color);

	/// On brush size changed.
	void BrushSizeChanged(int brushSize);

	/// On New file menu clicked.
	void newSpriteRequested(int width, int height);

	/// On Open file menu clicked.
	void loadRequested(const QString &filename);

	/// On Save file menu clicked.
	void saveRequested(const QString &filename);

	/// On frame duplication.
	void duplicateFrameRequested(bool duplicate);

	/// On frame button pressed.
	void highlightIcon(int id);

	/// On layer button pressed.
	void highlightLayer(int id);


private:
	Ui::MainWindow *ui;
	Editor *editor;

	Viewport *viewport;
	PreviewPanel *previewPanel;
	TimelinePanel *timelinePanel;
	LayersPanel *layersPanel;
	int activeFrame;

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
	bool duplicateFrame;

	int prevNewWidth;
	int prevNewHeight;

	///
	/// \brief Setups Highlight Buttons Connections.
	///
	void setupHighlightButtonsConnections();

	///
	/// \brief Setups Highlight Buttons Connections.
	///
	void setupToolsPanelConnections();

	///
	/// \brief Setups Highlight Buttons Connections.
	///
	void setupViewportConnections();

	///
	/// \brief Setups Highlight Buttons Connections.
	///
	void setupTimelinePanelConnections();

	///
	/// \brief Setups Highlight Buttons Connections.
	///
	void setupLayersPanelConnections();

	///
	/// \brief Setups Highlight Buttons Connections.
	///
	void setupPreviewPanelConnections();

	///
	/// \brief Creates menu bar actions.
	///
	void createActions();

	///
	/// \brief Creates menu bar menus.
	///
	void createMenus();

	///
	/// \brief Opens the help window.
	///
	void openHelpWindow();

	///
	/// \brief Resets button style.
	/// \param button button to the reset the style of
	///
	void resetButtonStyles(QPushButton *button);

	///
	/// \brief Asks the user if they want to duplicate frame and then sends signal to the model to create a new frame.
	///
	void onAddFrameButtonClicked();

};
#endif // MAINWINDOW_H
