#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#include <QDebug>

#include <QMainWindow>

#include <QPointF>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>

#include <QImage>
#include <QPainter>

#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <QProgressDialog>

#include "action.h"
#include "actionmove.h"
#include "actionturn.h"
#include "actionlist.h"

#include "graphicsviewedit.h"

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

public slots:
	void add_move(QPointF start);
	void update_move(QPointF end);
	void end_move(QPointF end);

private slots:
	void on_pushButton_setup_clicked();

	void on_pushButton_help_clicked();
	void on_pushButton_about_clicked();

	void on_pushButton_generateProgram_clicked();
	void on_pushButton_exportDiagram_clicked();

private:
	Ui::DrawWindow *ui;
	SetupWindow* setupWindow;
	AboutWindow* aboutWindow;
	HelpWindow* helpWindow;
	ActionList *list_history;

	QString canned_declares;
	QString canned_definitions;

	QGraphicsScene field;
	bool isDragging;
	QPointF startPoint;
	QPointF endPoint;
	QGraphicsLineItem* currentLine;

	void resizeEvent(QResizeEvent* event);
	void showEvent(QShowEvent* event);
};

#endif // DRAWWINDOW_H
