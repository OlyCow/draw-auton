#ifndef ACTIONCUSTOM_H
#define ACTIONCUSTOM_H

#include "action.h"
#include "actionwidget.h"

#include <QWidget>

class ActionCustom : public Action
{
public:
	ActionCustom();
	~ActionCustom();

private:
	ActionWidget* setup_widget;
};

#endif // ACTIONCUSTOM_H
