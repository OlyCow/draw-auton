#include "actiondefine.h"

ActionDefine::ActionDefine() :
	tool(new ActionTool("","",this)),
	widget(new ActionWidget(0, this))
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

void ActionDefine::set_tool_name(QString input)
{
	tool->setText(input);
}
void ActionDefine::set_tool_icon(int input_index)
{
	tool->setIcon(QIcon(definitions::icon[input_index]));
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
