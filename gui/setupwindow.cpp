#include "setupwindow.h"
#include "ui_setupwindow.h"

QStringList SetupWindow::keywords = QStringList();
QStringList SetupWindow::functions = QStringList();

SetupWindow::SetupWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SetupWindow),
	new_tab_widget(NULL),
	dir_data(QCoreApplication::applicationDirPath())
{
	ui->setupUi(this);
	QFontDatabase::addApplicationFont(":/fonts/DroidSansMono.ttf");

	dir_data = QCoreApplication::applicationDirPath() + "data/";
	if (!dir_data.exists()) {
		dir_data = QCoreApplication::applicationDirPath();
		dir_data.mkdir("data/");
		dir_data.cd("data/");
	}
	path_dir = dir_data.absolutePath();

	code_edits.push_back(ui->textEdit_pragmas);
	code_edits.push_back(ui->textEdit_includes);
	code_edits.push_back(ui->textEdit_move);
	code_edits.push_back(ui->textEdit_turn);
	code_edits.push_back(ui->textEdit_init);
	code_edits.push_back(ui->textEdit_misc_declare);
	code_edits.push_back(ui->textEdit_misc_define);

	code_vars.push_back(&controller_config);
	code_vars.push_back(&additional_includes);
	code_vars.push_back(&definition_move);
	code_vars.push_back(&definition_turn);
	code_vars.push_back(&misc_init);
	code_vars.push_back(&misc_declare);
	code_vars.push_back(&misc_define);

	for (unsigned int i=0; i<code_edits.size(); i++) {
		QFile check_exist = path_dir + definitions::path_code_blocks[i];
		if (!check_exist.exists()) {
			check_exist.open(QFile::WriteOnly | QFile::Text);
			QTextStream buf(&check_exist);
			buf.flush();
			check_exist.close();
		}
		*(code_vars[i]) = \
				read_file(path_dir + definitions::path_code_blocks[i]);
		code_edits[i]->setHtml(format_code(*(code_vars[i])));
	}

	QFont monospace_font;
	monospace_font.setFamily("Droid Sans Mono");
	monospace_font.setStyleHint(QFont::Monospace);
	monospace_font.setFixedPitch(true);
	monospace_font.setPointSize(10);
	QFontMetrics monospace_metrics(monospace_font);
	int tab_width = 4 * monospace_metrics.width(' ');
	for (unsigned int i=0; i<code_edits.size(); i++) {
		code_edits[i]->setTabStopWidth(tab_width);
	}

	QString read_buffer;
	read_buffer = read_file(path_dir + definitions::path_keywords);
	SetupWindow::keywords = read_buffer.split("\n");

	read_buffer = read_file(path_dir + definitions::path_functions);
	SetupWindow::functions = read_buffer.split("\n");

	for (unsigned int i=0; i<code_edits.size(); i++) {
		code_edits[i]->installEventFilter(this);
	}

	create_action_widget();

	QObject::connect(	ui->tabWidget_actions_custom,	&QTabWidget::tabCloseRequested,
						this,							&SetupWindow::remove_action_tab);
}

SetupWindow::~SetupWindow()
{
	delete ui;
	delete new_tab_widget;
}

ActionWidget* SetupWindow::create_action_widget()
{
	QTabWidget* tab_widget = ui->tabWidget_actions_custom;

	ActionDefine* new_define = new ActionDefine();
	ActionWidget* new_widget = new ActionWidget(new_define);
	new_define->set_widget(new_widget);
	tab_widget->addTab(new_widget, "New Action");
	
	if (tab_widget->count() == 1) {
		new_tab_widget = new_widget;
	}
	new_tab_widget->set_index(tab_widget->currentIndex());
	if (tab_widget->count() > 1) {
		QObject::disconnect(	new_tab_widget,	&ActionWidget::info_added,
								this,			&SetupWindow::create_action_widget);
		QObject::connect(		new_tab_widget,	&ActionWidget::info_updated,
								this,			&SetupWindow::update_custom_action);
		QObject::connect(		new_tab_widget,	&ActionWidget::info_cleared,
								this,			&SetupWindow::remove_action_widget);
		emit added_custom_define(new_tab_widget->get_parent());	// Haven't switched the new_tab_widget yet.
	}
	QObject::connect(	new_widget,	&ActionWidget::info_added,
						this,		&SetupWindow::create_action_widget);

	new_tab_widget = new_widget;
	return new_widget;
}

void SetupWindow::remove_action_tab(int index)
{
	ActionWidget* widget_removed = qobject_cast<ActionWidget*>(ui->tabWidget_actions_custom->widget(index));
	remove_action_widget(widget_removed);
}
void SetupWindow::remove_action_widget(ActionWidget* widget)
{
	QTabWidget* tab_widget = ui->tabWidget_actions_custom;
	int tab_num = tab_widget->count();
	if (tab_num > 1) {
		for (int i=0; i<tab_num; i++) {
			ActionWidget* widget_compare = qobject_cast<ActionWidget*>(tab_widget->widget(i));
			if (widget_compare == widget) {
				tab_widget->removeTab(i);
				emit removed_custom_define(widget->get_parent());
				break;
			}
		}
	}
}

void SetupWindow::update_custom_action(ActionWidget *widget)
{
	QString tab_name = widget->lineEdit_name->text();
	if (tab_name.length() == 0) {
		tab_name = "[...]";
	}
	ui->tabWidget_actions_custom->setTabText(	ui->tabWidget_actions_custom->currentIndex(),
												tab_name);
	emit updated_custom_define(widget->get_parent());
}

void SetupWindow::on_pushButton_save_clicked()
{
	for (unsigned int i=0; i<code_edits.size(); i++) {
		*(code_vars[i]) = code_edits[i]->toPlainText();
		write_file(	path_dir + definitions::path_code_blocks[i],
					*(code_vars[i])	);
	}
}

void SetupWindow::show_new_custom_tab()
{
	ui->tabWidget->setCurrentIndex(2);
	ui->tabWidget_actions_custom->setCurrentIndex(ui->tabWidget_actions_custom->count()-1);
}

void SetupWindow::on_pushButton_clear_clicked()
{
	for (unsigned int i=0; i<code_edits.size(); i++) {
		code_edits[i]->setHtml(format_code(*(code_vars[i])));
	}
}

void SetupWindow::on_pushButton_empty_clicked()
{
	for (unsigned int i=0; i<code_edits.size(); i++) {
		code_edits[i]->setPlainText("");
	}
}

void SetupWindow::on_pushButton_close_clicked()
{
	for (unsigned int i=0; i<code_edits.size(); i++) {
		code_edits[i]->setHtml(format_code(*(code_vars[i])));
	}
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
		current_line.replace("\\", "<font color=\"Gray\">\\</font>");
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
