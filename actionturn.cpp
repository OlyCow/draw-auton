#include "actionturn.h"

ActionTurn::ActionTurn(TurnDirection direction, QPointF startPoint, float degrees)
{
	start = startPoint;
	switch (direction) {
		case TURN_LEFT :
			name = "TurnLeft";
			break;
		case TURN_RIGHT :
			name = "TurnRight";
			break;
	}
	param = degrees;
	update_call();
}
