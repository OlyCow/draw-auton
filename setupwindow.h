#ifndef SETUPWINDOW_H
#define SETUPWINDOW_H

#include <QDialog>

#include <vector>

#include <QEvent>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QFile>
#include <QFont>
#include <QFontDatabase>
#include <QFontMetrics>
#include <QTextCursor>

#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include <QHBoxLayout>

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
	void added_custom_action(ActionWidget* widget);
	void removed_custom_action(int index);

public slots:
	ActionWidget* create_action_widget();
	void remove_action_widget(int index);

private slots:
	void on_pushButton_save_clicked();
	void on_pushButton_clear_clicked();
	void on_pushButton_empty_clicked();
	void on_pushButton_close_clicked();

private:
	Ui::SetupWindow *ui;
	ActionWidget* new_tab_widget;
	std::vector<ActionWidget*> list_custom_actions;

	std::vector<QTextEdit*> code_edits;

	std::vector<QString*> code_vars;
	std::vector<QString> code_urls;
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
