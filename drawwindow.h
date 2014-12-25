#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#include <QMainWindow>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

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

	void on_pushButton_generateProgram_clicked();

private:
	Ui::DrawWindow *ui;
    SetupWindow *setupWindow;
	ActionList *list_history;

	QString canned_declares;
	QString canned_definitions;

	QGraphicsScene field;
};

#endif // DRAWWINDOW_H
