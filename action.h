#ifndef ACTION_H
#define ACTION_H

#include <QString>
#include <QPointF>

class Action
{
public:
	Action(	QString input_name,
			QString input_param);

	void update_call();

	void setStart(QPointF input)		{start = input;}
	void setName(QString input)			{name = input;}
	void setParam(QString input)		{param = input;}

	QPointF getStart()			{return start;}
	QString getName()			{return name;}
	QString getParam()			{return param;}
	QString getCall()			{return call;}

protected:
	Action();

	QString name;
	QString param;
	QString call;

	QPointF start;
};

#endif // ACTION_H
