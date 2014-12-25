#include "setupwindow.h"
#include "ui_setupwindow.h"

setupwindow::setupwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setupwindow)
{
	ui->setupUi(this);
	QFontDatabase::addApplicationFont(":/fonts/DroidSansMono.ttf");
}

setupwindow::~setupwindow()
{
	delete ui;
}
