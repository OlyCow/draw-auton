#include "actionparam.h"

ActionParam::ActionParam() :
	icon(0),
	text(QString())
{
}

ActionParam::ActionParam(int icon_index, QString param) :
	icon(icon_index),
	text(param)
{
}

ActionParam::~ActionParam()
{
}
