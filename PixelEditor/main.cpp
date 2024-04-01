#include "mainwindow.h"
#include "editor.h"

static const int SPRITE_WIDTH_DEFAULT = 70;
static const int SPRITE_HEIGHT_DEFAULT = 50;

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);

	Editor editor;
	MainWindow window(&editor);
	window.show();
	editor.createNewSprite(SPRITE_WIDTH_DEFAULT, SPRITE_HEIGHT_DEFAULT);

	return application.exec();
}
