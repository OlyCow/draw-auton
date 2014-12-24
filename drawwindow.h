#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#include <QMainWindow>
#include "action.h"
#include "actionlist.h"

namespace Ui {
class DrawWindow;
}

class DrawWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit DrawWindow(QWidget *parent = 0);
	~DrawWindow();

private:
	Ui::DrawWindow *ui;
	ActionList *list_history;
};

#endif // DRAWWINDOW_H
