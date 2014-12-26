#ifndef SETUPWINDOW_H
#define SETUPWINDOW_H

#include <QDialog>

#include "actionwidget.h"

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

private slots:
	void on_pushButton_save_clicked();
	void on_pushButton_clear_clicked();
	void on_pushButton_empty_clicked();
	void on_pushButton_close_clicked();

private:
	Ui::SetupWindow *ui;
    std::vector<QWidget> custom_action;
	std::vector<ActionWidget*> action_widget;
	int action_widget_num;
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
