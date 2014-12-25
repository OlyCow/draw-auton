#include "setupwindow.h"
#include "ui_setupwindow.h"

SetupWindow::SetupWindow(QWidget *parent) :
    QDialog(parent),
	ui(new Ui::SetupWindow)
{
	ui->setupUi(this);
	QFontDatabase::addApplicationFont(":/fonts/DroidSansMono.ttf");
}

SetupWindow::~SetupWindow()
{
	delete ui;
}

void SetupWindow::on_pushButton_close_clicked()
{
	this->hide();
}
