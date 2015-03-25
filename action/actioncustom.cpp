#include "actioncustom.h"

ActionCustom::ActionCustom(ActionDefine* definition, QPointF start_point)
{
	actionDefine = definition;
	start = start_point;
	end = start_point;
}

ActionCustom::~ActionCustom()
{
	delete actionDefine;
}
