#include "drawwindow.h"
#include "ui_drawwindow.h"

DrawWindow::DrawWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DrawWindow)
{
    ui->setupUi(this);
}

DrawWindow::~DrawWindow()
{
    delete ui;
}
