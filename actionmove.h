#ifndef ACTIONMOVE_H
#define ACTIONMOVE_H

#include "action.h"

#include <cmath>

#include <QPointF>

class ActionMove : public Action
{
public:
	ActionMove();
	~ActionMove();

	float find_dist();

	void setEnd(QPointF input)	{end = input;}

private:
	QPointF end;
};

#endif // ACTIONMOVE_H
