#include "mainwindow.h"
#include "editor.h"

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);

	Editor editor;
	MainWindow window(&editor);
	window.show();
	editor.createNewSprite();

	return application.exec();
}
