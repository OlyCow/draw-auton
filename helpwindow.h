#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QDialog>
#include <QMessageBox>

#include <QString>
#include <QFont>

namespace Ui {
class HelpWindow;
}

class HelpWindow : public QDialog
{
	Q_OBJECT

public:
	explicit HelpWindow(QWidget *parent = 0);
	~HelpWindow();

private slots:
	void on_pushButton_close_clicked();

	void on_pushButton_snap_to_grid_clicked();
	void on_pushButton_generate_program_clicked();
	void on_pushButton_export_image_clicked();
	void on_pushButton_keyboard_shortcuts_clicked();

private:
	Ui::HelpWindow *ui;

	QMessageBox* construct_message(QString message);
};

#endif // HELPWINDOW_H
