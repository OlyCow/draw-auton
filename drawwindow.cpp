#include "drawwindow.h"
#include "ui_drawwindow.h"

DrawWindow::DrawWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::DrawWindow),
	list_history(new ActionList)
{
	ui->setupUi(this);
}

DrawWindow::~DrawWindow()
{
	delete ui;
	delete list_history;
}
