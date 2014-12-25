#ifndef SETUPWINDOW_H
#define SETUPWINDOW_H

#include <QDialog>
#include <QFontDatabase>

namespace Ui {
class SetupWindow;
}

class SetupWindow : public QDialog
{
	Q_OBJECT

public:
	explicit SetupWindow(QWidget *parent = 0);
	~SetupWindow();

private slots:
	void on_pushButton_close_clicked();

private:
	Ui::SetupWindow *ui;
};

#endif // SETUPWINDOW_H
