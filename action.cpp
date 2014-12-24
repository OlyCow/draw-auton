#include "action.h"

Action::Action() :
	name(""),
	call(""),
	param(""),
	declaration(""),
	definition("")
{
}

Action::Action(	QString input_name,
				QString input_call,
				QString input_param,
				QString input_declaration,
				QString input_definition) :
	name(input_name),
	call(input_call),
	param(input_param),
	declaration(input_declaration),
	definition(input_definition)
{
}

QString Action::getCall()
{
	QString buffer = call;
	buffer += "(";
	buffer += param;
	buffer += ");\n";
	return buffer;
}
