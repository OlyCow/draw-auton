#include "setupwindow.h"
#include "ui_setupwindow.h"

SetupWindow::SetupWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SetupWindow),
	do_update(true)
{
	ui->setupUi(this);
	QFontDatabase::addApplicationFont(":/fonts/DroidSansMono.ttf");

	controller_config = read_file("code/controller_config.txt");
	ui->textEdit_pragmas->setText(controller_config);

	additional_includes = read_file("code/additional_includes.txt");
	ui->textEdit_includes->setText(additional_includes);
}

SetupWindow::~SetupWindow()
{
	delete ui;
}

void SetupWindow::on_pushButton_save_clicked()
{
	controller_config = ui->textEdit_pragmas->toPlainText();
	write_file("code/controller_config.txt", controller_config);

	additional_includes = ui->textEdit_includes->toPlainText();
	write_file("code/additional_includes.txt", controller_config);
}

void SetupWindow::on_pushButton_clear_clicked()
{
	ui->textEdit_pragmas->setPlainText(controller_config);
	ui->textEdit_includes->setPlainText(additional_includes);
}

void SetupWindow::on_pushButton_empty_clicked()
{
	ui->textEdit_pragmas->setPlainText("");
	ui->textEdit_includes->setPlainText("");
}

void SetupWindow::on_pushButton_close_clicked()
{
	// remember to clear data
	this->hide();
}

void SetupWindow::on_textEdit_pragmas_textChanged()
{
	if (do_update == true) {
		do_update = false;
		QString raw = ui->textEdit_pragmas->toPlainText();
		raw = format_code(raw);
		ui->textEdit_pragmas->setHtml(raw);
	} else {
		do_update = true;
	}
}

void SetupWindow::on_textEdit_includes_textChanged()
{
	if (do_update == true) {
		do_update = false;
		QString raw = ui->textEdit_includes->toPlainText();
		raw = format_code(raw);
		ui->textEdit_includes->setHtml(raw);
	} else {
		do_update = true;
	}
}

QString SetupWindow::format_code(QString input)
{
	QString output = "";
	QStringList raw_list = input.split("\n");
	for (int i=0; i<raw_list.size(); ++i) {
		QString current_line = raw_list.at(i);
		if (raw_list.at(i).startsWith("#")) {
			current_line = "<font color=\"Maroon\">" + current_line + "</font>";
		}
		if (raw_list.at(i).startsWith("//")) {
			current_line = "<font color=\"Green\">" + current_line + "</font>";
		}
		output += current_line;
		output += "<br />";
	}
	output.chop(6); // last "<br />
	return output;
}

QString SetupWindow::read_file(QString path)
{
	QFile file(path);
	file.open(QFile::ReadOnly | QFile::Text);
	QTextStream read_buffer(&file);
	QString output = read_buffer.readAll();
	file.close();
	return output;
}

void SetupWindow::write_file(QString path, QString input)
{
	QFile file(path);
	file.open(QFile::WriteOnly | QFile::Text);
	QTextStream write_buffer(&file);
	write_buffer << input;
	file.flush();
	file.close();
}
