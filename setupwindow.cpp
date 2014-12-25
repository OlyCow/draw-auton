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

	definition_move = read_file("code/definition_move.txt");
	ui->textEdit_move->setText(definition_move);

	definition_turn = read_file("code/definition_turn.txt");
	ui->textEdit_turn->setText(definition_turn);

	QFont monospace_font;
	monospace_font.setFamily("Droid Sans Mono");
	monospace_font.setStyleHint(QFont::Monospace);
	monospace_font.setFixedPitch(true);
	monospace_font.setPointSize(10);
	QFontMetrics monospace_metrics(monospace_font);
	int tab_width = 4 * monospace_metrics.width(' ');
	ui->textEdit_pragmas->setTabStopWidth(tab_width);
	ui->textEdit_includes->setTabStopWidth(tab_width);
	ui->textEdit_move->setTabStopWidth(tab_width);
	ui->textEdit_turn->setTabStopWidth(tab_width);

	QString read_buffer;
	read_buffer = read_file("code/keywords.txt");
	keywords = read_buffer.split("\n");

	read_buffer = read_file("code/functions.txt");
    functions = read_buffer.split("\n");

    create_new_action();
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

	definition_move = ui->textEdit_move->toPlainText();
	write_file("code/definition_move.txt", definition_move);

	definition_turn = ui->textEdit_turn->toPlainText();
	write_file("code/definition_turn.txt", definition_turn);
}

void SetupWindow::on_pushButton_clear_clicked()
{
	ui->textEdit_pragmas->setPlainText(controller_config);
	ui->textEdit_includes->setPlainText(additional_includes);
	ui->textEdit_move->setPlainText(definition_move);
	ui->textEdit_turn->setPlainText(definition_turn);
}

void SetupWindow::on_pushButton_empty_clicked()
{
	ui->textEdit_pragmas->setPlainText("");
	ui->textEdit_includes->setPlainText("");
	ui->textEdit_move->setPlainText("");
	ui->textEdit_turn->setPlainText("");
}

void SetupWindow::on_pushButton_close_clicked()
{
	// remember to clear data
	this->close();
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

void SetupWindow::create_new_action()
{
    QWidget* blank_widget = new QWidget();
    QGridLayout* blank_action = new QGridLayout(blank_widget);
    blank_action->layout()->setMargin(0);

    QLabel* label_name = new QLabel("Action Name:");
    QLabel* label_declare = new QLabel("Declaration/\nCall:");

    QLineEdit* lineEdit_name = new QLineEdit();
    lineEdit_name->setStyleSheet("font: bold 10pt");
    lineEdit_name->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    lineEdit_name->setClearButtonEnabled(true);

    QLineEdit* lineEdit_declare = new QLineEdit();
    lineEdit_declare->setStyleSheet("font: 10pt \"Droid Sans Mono\"");
    lineEdit_declare->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    lineEdit_declare->setClearButtonEnabled(true);

    QTextEdit* textEdit_define = new QTextEdit();
    textEdit_define->setStyleSheet("font: 10pt \"Droid Sans Mono\"");
    textEdit_define->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    textEdit_define->setLineWrapMode(QTextEdit::NoWrap);
    textEdit_define->setAcceptRichText(false);

    blank_action->addWidget(label_name, 0, 0);
    blank_action->addWidget(lineEdit_name, 0, 1);
    blank_action->addWidget(label_declare, 1, 0);
    blank_action->addWidget(lineEdit_declare, 1, 1);
    blank_action->addWidget(textEdit_define, 2, 0, 1, 2);

    int insert_pos = 0;
    ui->verticalLayout->insertWidget(insert_pos, blank_widget);
}
