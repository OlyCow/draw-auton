#ifndef SETUPWINDOW_H
#define SETUPWINDOW_H

#include <QDialog>
#include <QFontDatabase>

namespace Ui {
class setupwindow;
}

class setupwindow : public QDialog
{
	Q_OBJECT

public:
	explicit setupwindow(QWidget *parent = 0);
	~setupwindow();

private:
	Ui::setupwindow *ui;
};

#endif // SETUPWINDOW_H
