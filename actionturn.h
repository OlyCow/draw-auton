#ifndef ACTIONTURN_H
#define ACTIONTURN_H

#include "action.h"

#include <QObject>

#include <QPointF>

enum TurnDirection {
	TURN_LEFT = 0,
	TURN_RIGHT = 1
};

class ActionTurn : public Action
{
	Q_OBJECT

public:
	ActionTurn(TurnDirection direction, QPointF startPoint, float degrees);

	ActionType isType()	{return TYPE_TURN;}
};

#endif // ACTIONTURN_H
