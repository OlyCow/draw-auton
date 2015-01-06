#include "actiondefine.h"

ActionDefine::ActionDefine() :
	tool(new ActionTool("","")),
	widget(new ActionWidget())
{
	QObject::connect(	widget,	&ActionWidget::param_added,
						this,	&ActionDefine::param_add);
	QObject::connect(	widget,	&ActionWidget::param_cleared,
						this,	&ActionDefine::param_clear);
}

ActionDefine::~ActionDefine()
{
	delete tool;
	delete widget;
}

void ActionDefine::param_add()
{
	list_params.push_back(widget->comboBox_param->currentText());
	list_icons.push_back(definitions::icon[definitions::ICON_APERTURE]);
}

void ActionDefine::param_clear(int index)
{
	list_params.erase(list_params.begin() + index);
	list_icons.erase(list_icons.begin() + index);
}
