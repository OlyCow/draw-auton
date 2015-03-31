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

QString ActionCustom::getCall()
{
	int param_index = actionDefine->get_widget()->get_current_param();
	QString return_string = "";
	return_string += actionDefine->get_declare()->section("(", 0, 0);
	return_string += "(";
	return_string += actionDefine->get_param(param_index)->get_text();
	return_string += ");\n";
	return return_string;
}
