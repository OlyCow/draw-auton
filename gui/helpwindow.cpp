#include "helpwindow.h"
#include "ui_helpwindow.h"

HelpWindow::HelpWindow(QWidget *parent) :
    QDialog(parent),
	ui(new Ui::HelpWindow)
{
	ui->setupUi(this);
}

HelpWindow::~HelpWindow()
{
	delete ui;
}

QMessageBox* HelpWindow::construct_message(QString message)
{
	QMessageBox* help = new QMessageBox(	QMessageBox::Information,
											"Draw Auton - Help",
											message,
											QMessageBox::Ok,
											this						);
	help->setWindowModality(Qt::NonModal);
	help->exec();
	return help;
}

void HelpWindow::on_pushButton_close_clicked()
{
	this->close();
}

void HelpWindow::on_pushButton_snap_to_grid_clicked()
{
	QString msg = "";
	msg += "At any time (before/during/after a click), press the ";
	msg += "\"Shift\" key to snap nodes to a quarter-tile sized grid. ";
	msg += "(This corresponds to a step size of 6 inches.)";
	construct_message(msg);
}

void HelpWindow::on_pushButton_generate_program_clicked()
{
	QString msg = "";
	msg += "To generate a program, click on the \"Generate Program\" ";
	msg += "button in the main window. To make sure the resulting code ";
	msg += "actually works, remember to set up basic functions. To ";
	msg += "do this click on the \"Setup\" button in the main window.\n\n";
	msg += "You can also use the keyboard shortcut \"Ctrl+S\" to generate ";
	msg += "code.";
	construct_message(msg);
}

void HelpWindow::on_pushButton_export_image_clicked()
{
	QString msg = "";
	msg += "Click on the \"Export Image\" button in the main window. ";
	msg += "This will export the current viewport as a \".png\" image.";
	construct_message(msg);
}

void HelpWindow::on_pushButton_keyboard_shortcuts_clicked()
{
	QString msg = "";
	msg += "F10:\t\tSetup\n";
	msg += "Ctrl+I:\t\tImport\n";
	msg += "Ctrl+Z:\t\tUndo\n";
	msg += "Ctrl+W:\t\tClear Diagram\n";
	msg += "Ctrl+S:\t\tGenerate Program\n";
	msg += "Ctrl+E:\t\tExport Diagram\n";
	msg += "F1:\t\tHelp";
	QMessageBox* help = construct_message(msg);
	help->setFont(QFont("Droid Sans Mono", 11));
}
