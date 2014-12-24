#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#include <QMainWindow>

#include "action.h"
#include "actionlist.h"

#include "aboutwindow.h"
#include "helpwindow.h"
#include "setupwindow.h"

namespace Ui {
class DrawWindow;
}

class DrawWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit DrawWindow(QWidget *parent = 0);
	~DrawWindow();

private slots:
    void on_pushButton_setup_clicked();

private:
	Ui::DrawWindow *ui;
    setupwindow *setupWindow;
	ActionList *list_history;
};

#endif // DRAWWINDOW_H
