#ifndef ACTIONCUSTOM_H
#define ACTIONCUSTOM_H

#include "definitions.h"
#include "action.h"
#include "actionwidget.h"

#include <QObject>
#include <QWidget>

#include <vector>

#include <QPointF>
#include <QString>

class ActionCustom : public Action
{
	Q_OBJECT

public:
	ActionCustom(QPointF start_point);
	~ActionCustom();

	ActionType isType()	{return TYPE_CUSTOM;}

private:
	QString icon;
};

#endif // ACTIONCUSTOM_H
