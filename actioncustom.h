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

	ActionWidget* getSetupWidget()	{return setup_widget;}

private:
	ActionWidget* setup_widget;

	QString icon;
	std::vector<QString> list_params;
	std::vector<QString> list_icons;

	void param_add();
	void param_clear(int index);
};

#endif // ACTIONCUSTOM_H
