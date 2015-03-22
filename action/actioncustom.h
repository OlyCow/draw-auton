#ifndef ACTIONCUSTOM_H
#define ACTIONCUSTOM_H

#include "definitions.h"
#include "action.h"
#include "actiondefine.h"

#include <QObject>
#include <QWidget>

#include <vector>

#include <QPointF>
#include <QString>

class ActionCustom : public Action
{
	Q_OBJECT

public:
	ActionCustom(ActionDefine* definition, QPointF start_point);
	~ActionCustom();

	ActionType isType()	{return TYPE_CUSTOM;}

	ActionDefine* getDefine() {return actionDefine;}

private:
	ActionDefine* actionDefine;
};

#endif // ACTIONCUSTOM_H
