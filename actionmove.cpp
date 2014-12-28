#include "actionmove.h"

ActionMove::ActionMove()
{

}

ActionMove::~ActionMove()
{

}

float ActionMove::find_dist()
{
	float ans;
	QPointF diff = start - end;
	ans = diff.x() * diff.x() + diff.y() * diff.y();
	ans = sqrt(ans);
	return ans;
}
