#ifndef GRAPHICSVIEWEDIT_H
#define GRAPHICSVIEWEDIT_H

#include <QObject>

#include <QPointF>

#include <QGraphicsView>

#include <QMouseEvent>
#include <QKeyEvent>

class GraphicsViewEdit : public QGraphicsView
{
	Q_OBJECT

public:
	GraphicsViewEdit(QWidget* parent=0);

signals:
	void mouse_pressed(QPointF pos);
	void mouse_moved(QPointF pos);
	void mouse_released(QPointF pos);

private slots:
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
};

#endif // GRAPHICSVIEWEDIT_H
