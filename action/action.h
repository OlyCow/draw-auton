#ifndef ACTION_H
#define ACTION_H

#include <QObject>

#include <QString>
#include <QPointF>

enum ActionType {
	TYPE_UNKNOWN = -1,
	TYPE_MOVE = 0,
	TYPE_TURN,
	TYPE_CUSTOM
};

class Action : public QObject
{
	Q_OBJECT

public:
	Action(	QString input_name,
			QString input_param);
	virtual ~Action();

	virtual ActionType isType()	{return TYPE_UNKNOWN;}

	void update_call();

	void setStart(QPointF input)		{start = input;}
	void setEnd(QPointF input)			{end = input;}
	void setName(QString input)			{name = input;}
	void setParam(QString input)		{param = input;}

	QPointF getStart()			{return start;}
	QPointF getEnd()			{return end;}
	QString getName()			{return name;}
	QString getParam()			{return param;}
	QString getCall()			{return call;}

protected:
	Action();

	QString name;
	QString param;
	QString call;

	QPointF start;
	QPointF end;
};

#endif // ACTION_H
