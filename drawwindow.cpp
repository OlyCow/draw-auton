#include "drawwindow.h"
#include "ui_drawwindow.h"

DrawWindow::DrawWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::DrawWindow),
    setupWindow(new SetupWindow),
	list_history(new ActionList)
{
	ui->setupUi(this);

	canned_declares = "void Move(int inches);\n";
	canned_declares += "void MoveForward(int inches);\n";
	canned_declares += "void MoveBackward(int inches);\n";
	canned_declares += "void Turn(int degrees);\n";
	canned_declares += "void TurnLeft(int degrees);\n";
	canned_declares += "void TurnRight(int degrees);\n";

	canned_definitions = "";
	canned_definitions += "void MoveForward(int inches) {\n";
	canned_definitions += "\tMove(inches);\n";
	canned_definitions += "}\n";
	canned_definitions += "void MoveBackward(int inches) {\n";
	canned_definitions += "\tMove(-inches);\n";
	canned_definitions += "}\n";
	canned_definitions += "void TurnLeft(int degrees) {\n";
	canned_definitions += "\tTurn(degrees);\n";
	canned_definitions += "}\n";
	canned_definitions += "void TurnRight(int degrees) {\n";
	canned_definitions += "\tTurn(-degrees);\n";
	canned_definitions += "}\n";
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
	final += canned_declares;
	final += "\ntask main()\n{\n";
	final += "\t waitForStart();\n";
	final += "}\n\n";
	final += SetupWindow::read_file("code/definition_move.txt");
	final += "\n";
	final += SetupWindow::read_file("code/definition_turn.txt");
	final += "\n";
	final += canned_definitions;
	SetupWindow::write_file("output/Autonomous.c", final);
}
