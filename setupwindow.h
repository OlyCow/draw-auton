#ifndef SETUPWINDOW_H
#define SETUPWINDOW_H

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QFile>
#include <QFontDatabase>
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

private slots:

	void on_pushButton_save_clicked();
	void on_pushButton_clear_clicked();
	void on_pushButton_empty_clicked();
	void on_pushButton_close_clicked();

	void on_textEdit_pragmas_textChanged();
	void on_textEdit_includes_textChanged();

private:
	Ui::SetupWindow *ui;
	QString controller_config;
	QString additional_includes;
	bool do_update;
};

#endif // SETUPWINDOW_H
