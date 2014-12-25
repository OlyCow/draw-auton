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

void DrawWindow::on_pushButton_generateProgram_clicked()
{
	QString final;
	final += SetupWindow::read_file("code/controller_config.txt");
	final += "\n";
	final += "#include \"JoystickDriver.c\"\n\n";
	final += SetupWindow::read_file("code/additional_includes.txt");
	final += "\n";
	final += "task main()\n{\n";
	final += "\t waitForStart();\n";
	final += "}\n";
	SetupWindow::write_file("output/Autonomous.c", final);
}
