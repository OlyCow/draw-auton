#include "actiondefine.h"

ActionDefine::ActionDefine() :
	icon(0),
	name(new QString("")),
	declare(new QString("")),
	define(new QString(""))
{
	widget = new ActionWidget(0, this);
	QObject::connect(	widget,	&ActionWidget::param_added,
						this,	&ActionDefine::add_param);
	QObject::connect(	widget, &ActionWidget::param_cleared,
						this,	&ActionDefine::remove_param);

	tool = new ActionTool("","",this);
}

ActionDefine::~ActionDefine()
{
	delete widget;
	delete tool;
	delete define;
	delete declare;
	delete name;
}

void ActionDefine::set_widget(ActionWidget *input)
{
	QObject::disconnect(	widget,	&ActionWidget::param_added,
							this,	&ActionDefine::add_param);
	QObject::disconnect(	widget, &ActionWidget::param_cleared,
							this,	&ActionDefine::remove_param);
	widget = input;
	QObject::connect(	widget,	&ActionWidget::param_added,
						this,	&ActionDefine::add_param);
	QObject::connect(	widget, &ActionWidget::param_cleared,
						this,	&ActionDefine::remove_param);
}

void ActionDefine::set_tool(ActionTool *input)
{
	tool = input;
}

void ActionDefine::update_data_from_widget()
{
	icon = widget->get_icon();
	name = widget->get_name();
	declare = widget->get_declare();
	define = widget->get_define();
	update_tool_with_data();
}

void ActionDefine::update_tool_with_data()
{

}
