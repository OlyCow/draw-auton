#include "actionmove.h"

ActionMove::ActionMove(MoveDirection direction, QPointF startPoint, QPointF endPoint)
{
	start = startPoint;
	end = endPoint;
	switch (direction) {
		case MOVE_FORWARD :
			name = "MoveForward";
			break;
		case MOVE_BACKWARD :
			name = "MoveBackward";
			break;
	}
	param = QString::number(find_dist());
	update_call();
}

float ActionMove::find_dist()
{
	float ans;
	QPointF diff = start - end;
	ans = diff.x() * diff.x() + diff.y() * diff.y();
	ans = sqrt(ans);
	return ans;
}
