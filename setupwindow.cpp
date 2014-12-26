#include "setupwindow.h"
#include "ui_setupwindow.h"

QStringList SetupWindow::keywords = QStringList();
QStringList SetupWindow::functions = QStringList();

SetupWindow::SetupWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SetupWindow),
	action_widget_num(0)
{
	ui->setupUi(this);
	QFontDatabase::addApplicationFont(":/fonts/DroidSansMono.ttf");

	controller_config = read_file("code/controller_config.txt");
	ui->textEdit_pragmas->setHtml(format_code(controller_config));

	additional_includes = read_file("code/additional_includes.txt");
	ui->textEdit_includes->setHtml(format_code(additional_includes));

	definition_move = read_file("code/definition_move.txt");
	ui->textEdit_move->setHtml(format_code(definition_move));

	definition_turn = read_file("code/definition_turn.txt");
	ui->textEdit_turn->setHtml(format_code(definition_turn));

	misc_init = read_file("code/misc_init.txt");
	ui->textEdit_init->setHtml(format_code(misc_init));

	misc_declare = read_file("code/misc_declare.txt");
	ui->textEdit_misc_declare->setHtml(format_code(misc_declare));

	misc_define = read_file("code/misc_define.txt");
	ui->textEdit_misc_define->setHtml(format_code(misc_define));

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

	add_action_widget();
	QObject::connect(	action_widget[0],	&ActionWidget::info_added,
						this,				&SetupWindow::create_action_widget);
	QObject::connect(	action_widget[0],	&ActionWidget::info_cleared,
						this,				&SetupWindow::remove_action_widget);


	ui->textEdit_pragmas->installEventFilter(this);
	ui->textEdit_includes->installEventFilter(this);
	ui->textEdit_move->installEventFilter(this);
	ui->textEdit_turn->installEventFilter(this);
	ui->textEdit_init->installEventFilter(this);
	ui->textEdit_misc_declare->installEventFilter(this);
	ui->textEdit_misc_define->installEventFilter(this);
}

SetupWindow::~SetupWindow()
{
	delete ui;
}

void SetupWindow::create_action_widget()
{
	add_action_widget();
}

void SetupWindow::remove_action_widget(int index_accept)
{
	delete_action_widget(index_accept);
}

void SetupWindow::add_action_widget()
{
	action_widget_num++;
	QWidget* actual_this = this;
	action_widget.push_back(new ActionWidget(actual_this, action_widget_num));
	int index = action_widget_num - 1;
	ui->verticalLayout->insertWidget(index, action_widget[index]);
	action_widget[index]->textEdit_define->installEventFilter(this);
}

void SetupWindow::delete_action_widget(int index)
{
	ui->verticalLayout->removeWidget(action_widget[index]);
	delete action_widget[index];
	std::vector<ActionWidget*>::iterator it = action_widget.begin();
	it += index;
	action_widget.erase(it);
	action_widget_num--;
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
		current_line.replace("\t", "&nbsp;&nbsp;&nbsp;&nbsp;");
		current_line.replace(" ", "&nbsp;");
		output += current_line;
		output += "<br />";
	}
	output.chop(6); // last "<br />
	QRegularExpression find_line_comment("\/{2,}+.*");
	QRegularExpressionMatch line_comment_match = find_line_comment.match(output);
	for (int i=0; i<line_comment_match.capturedTexts().size(); i++) {
		QString original = line_comment_match.captured(i);
		QString replaced = "<font color=\"Green\">"+original+"</font>";
		output.replace(original, replaced);
	}
	QRegularExpression find_pragma("#+.*");
	QRegularExpressionMatch pragma_match = find_pragma.match(output);
	for (int i=0; i<pragma_match.capturedTexts().size(); i++) {
		QString original = pragma_match.captured(i);
		QString replaced = "<font color=\"Maroon\">"+original+"</font>";
		output.replace(original, replaced);
	}
	QRegularExpression find_block_comment("\/\\*.*?\\*\/");
	find_block_comment.setPatternOptions(QRegularExpression::MultilineOption);
	QRegularExpressionMatch block_comment_match = find_block_comment.match(output);
	for (int i=0; i<block_comment_match.capturedTexts().size(); i++) {
		QString original = block_comment_match.captured(i);
		QString replaced = "<font color=\"Green\">"+original+"</font>";
		output.replace(original, replaced);
	}
	for (int i=0; i<keywords.size(); i++) {
		QString current = keywords[i];
		QRegularExpression find_keyword("\\b("+current+")\\b");
		QRegularExpressionMatch match = find_keyword.match(current);
		for (int j=0; j<match.capturedTexts().size(); j++) {
			QString original = match.captured(j);
			QString replaced = "<font color=\"Blue\">"+original+"</font>";
			output.replace(original, replaced);
		}
	}
	for (int i=0; i<functions.size(); i++) {
		QString current = functions[i];
		QRegularExpression find_function("\\b("+current+")\\b");
		QRegularExpressionMatch match = find_function.match(current);
		for (int j=0; j<match.capturedTexts().size(); j++) {
			QString original = match.captured(j);
			QString replaced = "<font color=\"DarkBlue\">"+original+"</font>";
			output.replace(original, replaced);
		}
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
