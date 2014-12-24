#include "drawwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DrawWindow w;
	w.show();

	return a.exec();
}
