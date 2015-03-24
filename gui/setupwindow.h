#ifndef SETUPWINDOW_H
#define SETUPWINDOW_H

#include <QDebug>

#include <vector>

#include <QEvent>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QDir>
#include <QFile>
#include <QFont>
#include <QFontDatabase>
#include <QFontMetrics>
#include <QTextCursor>

#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include <QHBoxLayout>

#include <QDialog>

#include "definitions.h"

#include "actiondefine.h"
#include "actionwidget.h"

namespace Ui {
class SetupWindow;
}

class SetupWindow : public QDialog
{
	Q_OBJECT

public:
	explicit SetupWindow(QWidget *parent = 0);
	~SetupWindow();

	static QString format_code(QString input);
	static QString read_file(QString path);
	static void write_file(QString path, QString input);

	static QStringList keywords;
	static QStringList functions;

signals:
	void added_custom_define(ActionDefine* definition);
	void updated_custom_define(ActionDefine* definition);
	void removed_custom_define(ActionDefine* definition);

public slots:
	ActionWidget* create_action_widget();
	void remove_action_tab(int index);
	void remove_action_widget(ActionWidget* widget);
	void update_custom_action(ActionWidget* widget);

	void show_new_custom_tab();

private slots:
	void on_pushButton_save_clicked();
	void on_pushButton_clear_clicked();
	void on_pushButton_empty_clicked();
	void on_pushButton_close_clicked();

private:
	Ui::SetupWindow *ui;
	ActionWidget* new_tab_widget;
	std::vector<ActionWidget*> list_custom_widgets;

	std::vector<QTextEdit*> code_edits;

	QDir dir_data;
	QString path_dir;

	std::vector<QString*> code_vars;
	QString controller_config;
	QString additional_includes;
	QString definition_move;
	QString definition_turn;
	QString misc_init;
	QString misc_declare;
	QString misc_define;

	bool eventFilter(QObject* object, QEvent* event);
};

#endif // SETUPWINDOW_H
