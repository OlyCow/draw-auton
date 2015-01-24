#include "actionturn.h"

ActionTurn::ActionTurn(TurnDirection direction, QPointF startPoint, float degrees)
{
	start = startPoint;
	end = startPoint;
	switch (direction) {
		case TURN_LEFT :
			name = "TurnLeft";
			break;
		case TURN_RIGHT :
			name = "TurnRight";
			break;
	}
	param = QString::number(degrees);
	update_call();
}
