#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>

#include <QEvent>
#include <QKeyEvent>

#include <QLabel>
#include <QString>

namespace Ui {
class AboutWindow;
}

class AboutWindow : public QDialog
{
	Q_OBJECT

public:
	explicit AboutWindow(QWidget *parent = 0);
	~AboutWindow();

private slots:
	void on_pushButton_close_clicked();

private:
	Ui::AboutWindow *ui;
	int current_pos;

	static int keys[10];

	bool eventFilter(QObject* object, QEvent* event);
};

#endif // ABOUTWINDOW_H
