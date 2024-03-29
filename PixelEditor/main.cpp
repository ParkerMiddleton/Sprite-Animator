#include "mainwindow.h"
#include "editormodel.h"

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);

	EditorModel editor;
	MainWindow window(&editor);
	window.show();

	return application.exec();
}
