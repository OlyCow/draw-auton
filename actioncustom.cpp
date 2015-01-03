#include "actioncustom.h"



ActionCustom::ActionCustom(QPointF start_point) :
	setup_widget(new ActionWidget())
{
	start = start_point;
	end = start_point;

	QObject::connect(	setup_widget,	&ActionWidget::param_added,
						this,			&ActionCustom::param_add);
	QObject::connect(	setup_widget,	&ActionWidget::param_cleared,
						this,			&ActionCustom::param_clear);
}

ActionCustom::~ActionCustom()
{
	delete setup_widget;
}

void ActionCustom::param_add()
{
	list_params.push_back(setup_widget->comboBox_param->currentText());
	list_icons.push_back(definitions::icon[definitions::ICON_APERTURE]);
}

void ActionCustom::param_clear(int index)
{
	list_params.erase(list_params.begin() + index);
	list_icons.erase(list_icons.begin() + index);
}
