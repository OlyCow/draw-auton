#ifndef ACTIONMOVE_H
#define ACTIONMOVE_H

#include "action.h"

#include <cmath>

#include <QPointF>

enum MoveDirection {
	MOVE_FORWARD = 0,
	MOVE_BACKWARD = 1
};

class ActionMove : public Action
{
public:
	ActionMove(MoveDirection direction, QPointF startPoint, QPointF endPoint);

	QPointF getEnd()	{return end;}

protected:
	QPointF end;

	float find_dist();
};

#endif // ACTIONMOVE_H
