#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#include <QDebug>

#include <cmath>
#include <vector>

#include <QPointF>
#include <QSize>

#include <QTextStream>
#include <QDir>
#include <QFile>

#include <QEvent>
#include <QKeyEvent>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>

#include <QImage>
#include <QPainter>

#include <QCoreApplication>

#include <QFileDialog>
#include <QProgressDialog>
#include <QMainWindow>

#include "definitions.h"

#include "action.h"
#include "actionmove.h"
#include "actionturn.h"
#include "actioncustom.h"
#include "actiondefine.h"
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

	void start_snap();
	void end_snap();

	void add_custom_define(ActionDefine* definition);
	void update_custom_define(ActionDefine* definition);
	void remove_custom_define(ActionDefine* definition);

private slots:
	void on_pushButton_setup_clicked();

	void on_pushButton_help_clicked();
	void on_pushButton_about_clicked();

	void on_pushButton_generateProgram_clicked();
	void on_pushButton_exportDiagram_clicked();

	void on_pushButton_undo_clicked();
	void on_pushButton_clear_clicked();

	void on_toolButton_add_clicked();

private:
	Ui::DrawWindow* ui;
	SetupWindow* setupWindow;
	AboutWindow* aboutWindow;
	HelpWindow* helpWindow;
	ActionList* list_history;
	std::vector<QGraphicsLineItem*> list_lines;
	std::vector<ActionDefine*> list_defines;

	QString canned_declares;
	QString canned_definitions;

	QGraphicsScene field;
	bool isDragging;
	bool isSnapping;
	QPointF startPoint;
	QPointF endPoint;
	QGraphicsLineItem* currentLine;
	QGraphicsEllipseItem* circleHome;
	QGraphicsEllipseItem* circleCurrent;

	void resizeEvent(QResizeEvent* event);
	void showEvent(QShowEvent* event);

	bool eventFilter(QObject* object, QEvent* event);
};

#endif // DRAWWINDOW_H
