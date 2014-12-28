#include "action.h"

Action::Action() :
	name(""),
	param(""),
	call("")
{
}

Action::~Action()
{
}

Action::Action(QString input_name,
				QString input_param) :
	name(input_name),
	param(input_param)
{
	update_call();
}

void Action::update_call()
{
	call = name + "(" + param + ");\n";
}
