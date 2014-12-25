#include "drawwindow.h"
#include "ui_drawwindow.h"

DrawWindow::DrawWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::DrawWindow),
    setupWindow(new SetupWindow),
	list_history(new ActionList)
{
	ui->setupUi(this);
}

DrawWindow::~DrawWindow()
{
	delete ui;
    delete setupWindow;
	delete list_history;
}

void DrawWindow::on_pushButton_setup_clicked()
{
    setupWindow->show();
}
