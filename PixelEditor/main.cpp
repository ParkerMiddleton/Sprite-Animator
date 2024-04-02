#include "mainwindow.h"
#include "editor.h"

/**
 * @authors Tommy Heimer, Egor Chesnokov, Koby Dato, Parker Middleton, Aditya Mukerjee, Charles WolfGramm.
 *
 * @version 1.0
 * @date 4/1/2024
 */

static const int SPRITE_WIDTH_DEFAULT = 70;
static const int SPRITE_HEIGHT_DEFAULT = 50;

///
/// \brief qMain Initializes model and view.
/// \param argc
/// \param argv
/// \return
///
int main(int argc, char *argv[])
{
	QApplication application(argc, argv);

	Editor editor;
	MainWindow window(&editor);
	window.show();
	editor.createNewSprite(SPRITE_WIDTH_DEFAULT, SPRITE_HEIGHT_DEFAULT);

	return application.exec();
}
