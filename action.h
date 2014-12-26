#ifndef ACTION_H
#define ACTION_H

#include <QString>

class Action
{
public:
	Action(QString input_name,
			QString input_call,
			QString input_param,
			QString input_declaration,
			QString input_definition);

	void setName(QString input)			{name = input;}
	void setCall(QString input)			{call = input;}
	void setParam(QString input)		{param = input;}
	void setDeclaration(QString input)	{declaration = input;}
	void setDefinition(QString input)	{definition = input;}

	QString getCall();

	QString getName()			{return name;}
	QString getParam()			{return param;}
	QString getDeclaration()	{return declaration;}
	QString getDefinition()		{return definition;}

protected:
	Action();

	QString name;
	QString call;
	QString param;
	QString declaration;
	QString definition;
};

#endif // ACTION_H
