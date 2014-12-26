#ifndef ACTIONMOVE_H
#define ACTIONMOVE_H

#include "action.h"

#include <QPointF>

class ActionMove : public Action
{
public:
	ActionMove();
	~ActionMove();

private:
	QPointF end;
};

#endif // ACTIONMOVE_H
