#include "setupwindow.h"
#include "ui_setupwindow.h"

QStringList SetupWindow::keywords = QStringList();
QStringList SetupWindow::functions = QStringList();

SetupWindow::SetupWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SetupWindow)
{
	ui->setupUi(this);
	QFontDatabase::addApplicationFont(":/fonts/DroidSansMono.ttf");

	controller_config = read_file("code/controller_config.txt");
	ui->textEdit_pragmas->setText(format_code(controller_config));

	additional_includes = read_file("code/additional_includes.txt");
	ui->textEdit_includes->setText(format_code(additional_includes));

	definition_move = read_file("code/definition_move.txt");
	ui->textEdit_move->setText(format_code(definition_move);

	definition_turn = read_file("code/definition_turn.txt");
	ui->textEdit_turn->setText(format_code(definition_turn));

	misc_init = read_file("code/misc_init.txt");
	ui->textEdit_init->setText(format_code(misc_init));

	misc_declare = read_file("code/misc_declare.txt");
	ui->textEdit_misc_declare->setText(format_code(misc_declare));

	misc_define = read_file("code/misc_define.txt");
	ui->textEdit_misc_define->setText(format_code(misc_define));

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
	SetupWindow::keywords = read_buffer.split("\n");

	read_buffer = read_file("code/functions.txt");
	SetupWindow::functions = read_buffer.split("\n");

	ui->textEdit_pragmas->installEventFilter(this);
	ui->textEdit_includes->installEventFilter(this);
	ui->textEdit_move->installEventFilter(this);
	ui->textEdit_turn->installEventFilter(this);
	ui->textEdit_init->installEventFilter(this);
	ui->textEdit_misc_declare->installEventFilter(this);
	ui->textEdit_misc_define->installEventFilter(this);

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

	misc_init = ui->textEdit_init->toPlainText();
	write_file("code/misc_init.txt", misc_init);

	misc_declare = ui->textEdit_misc_declare->toPlainText();
	write_file("code/misc_declare.txt", misc_declare);

	misc_define = ui->textEdit_misc_define->toPlainText();
	write_file("code/misc_define.txt", misc_define);
}

void SetupWindow::on_pushButton_clear_clicked()
{
	ui->textEdit_pragmas->setPlainText(controller_config);
	ui->textEdit_includes->setPlainText(additional_includes);
	ui->textEdit_move->setPlainText(definition_move);
	ui->textEdit_turn->setPlainText(definition_turn);
	ui->textEdit_init->setPlainText(misc_init);
	ui->textEdit_misc_declare->setPlainText(misc_declare);
	ui->textEdit_misc_define->setPlainText(misc_define);
}

void SetupWindow::on_pushButton_empty_clicked()
{
	ui->textEdit_pragmas->setPlainText("");
	ui->textEdit_includes->setPlainText("");
	ui->textEdit_move->setPlainText("");
	ui->textEdit_turn->setPlainText("");
	ui->textEdit_init->setPlainText("");
	ui->textEdit_misc_declare->setPlainText("");
	ui->textEdit_misc_define->setPlainText("");
}

void SetupWindow::on_pushButton_close_clicked()
{
	// remember to clear data
	this->close();
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
	for (int i=0; i<keywords.size(); i++) {
		QString current = keywords[i];
		output.replace(current, "<font color=\"Blue\">"+current+"</font>");
	}
	for (int i=0; i<functions.size(); i++) {
		QString current = functions[i];
		output.replace(current, "<font color=\"DarkBlue\">"+current+"</font>");
	}
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

bool SetupWindow::eventFilter(QObject *object, QEvent *event)
{
	if (event->type() == QEvent::FocusOut) {
		QTextEdit* object_casted = qobject_cast<QTextEdit*>(object);
		QString raw = object_casted->toPlainText();
		raw = format_code(raw);
		object_casted->setHtml(raw);
	}
	return false;
}
