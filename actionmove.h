#ifndef ACTIONMOVE_H
#define ACTIONMOVE_H

#include "action.h"

#include <QObject>

#include <cmath>

#include <QPointF>

enum MoveDirection {
	MOVE_FORWARD = 0,
	MOVE_BACKWARD = 1
};

class ActionMove : public Action
{
	Q_OBJECT

public:
	ActionMove(MoveDirection direction, QPointF startPoint, QPointF endPoint);

	ActionType isType()	{return TYPE_MOVE;}

private:
	float find_dist();
};

#endif // ACTIONMOVE_H
