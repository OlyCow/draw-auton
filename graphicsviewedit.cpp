#include "graphicsviewedit.h"

GraphicsViewEdit::GraphicsViewEdit(QWidget* parent) :
	QGraphicsView(parent)
{
}

void GraphicsViewEdit::mousePressEvent(QMouseEvent *event)
{
	emit mouse_pressed(event->localPos());
}

void GraphicsViewEdit::mouseMoveEvent(QMouseEvent *event)
{
	emit mouse_moved(event->localPos());
}

void GraphicsViewEdit::mouseReleaseEvent(QMouseEvent *event)
{
	emit mouse_released(event->localPos());
}
