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

	QRectF bounds = QRectF(-10, -10, 164, 164);
	field.addRect(bounds, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::white));

	QRectF tiles = QRectF(0, 0, 144, 144);
	field.addRect(tiles, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::lightGray));

	QRectF zone_ramp_out_R = QRectF(0, 0, 30, 66);
	QRectF zone_ramp_in_R = QRectF(0, 0, 28, 64);
	QRectF zone_park_out_R = QRectF(47, 0, 47, 23);
	QRectF zone_park_in_R = QRectF(49, 0, 43, 21);
	QRectF ramp_R = QRectF(0, 0, 23.75, 57);
	field.addRect(zone_ramp_out_R, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::red));
	field.addRect(zone_ramp_in_R, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::lightGray));
	field.addRect(zone_park_out_R, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::red));
	field.addRect(zone_park_in_R, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::lightGray));
	field.addRect(ramp_R, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::red));

	QRectF zone_ramp_out_B = QRectF(144-30, 144-66, 30, 66);
	QRectF zone_ramp_in_B = QRectF(144-28, 144-64, 28, 64);
	QRectF zone_park_out_B = QRectF(144-47-47, 144-23, 47, 23);
	QRectF zone_park_in_B = QRectF(144-43-49, 144-21, 43, 21);
	QRectF ramp_B = QRectF(144-23.75, 144-57, 23.75, 57);
	field.addRect(zone_ramp_out_B, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::blue));
	field.addRect(zone_ramp_in_B, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::lightGray));
	field.addRect(zone_park_out_B, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::blue));
	field.addRect(zone_park_in_B, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::lightGray));
	field.addRect(ramp_B, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::blue));

	field.setSceneRect(-5, -5, 149, 149);
	ui->graphicsView->setScene(&field);
}

void DrawWindow::resizeEvent(QResizeEvent* event)
{
	ui->graphicsView->fitInView(field.itemsBoundingRect(), Qt::KeepAspectRatio);
	QMainWindow::resizeEvent(event);
}

void DrawWindow::showEvent(QShowEvent* event)
{
	ui->graphicsView->fitInView(field.itemsBoundingRect(), Qt::KeepAspectRatio);
	QMainWindow::showEvent(event);
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
	final += "\n";
	final += SetupWindow::read_file("code/misc_declare.txt");
	final += "\ntask main()\n{\n";
	final += SetupWindow::read_file("code/misc_init.txt");
	final += "\n\t waitForStart();\n";
	final += "}\n\n";
	final += SetupWindow::read_file("code/definition_move.txt");
	final += "\n";
	final += SetupWindow::read_file("code/definition_turn.txt");
	final += "\n";
	final += canned_definitions;
	final += "\n";
	final += SetupWindow::read_file("code/misc__define.txt");
	final += "\n";
	SetupWindow::write_file("output/Autonomous.c", final);
}
