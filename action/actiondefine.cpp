#include "actiondefine.h"

ActionDefine::ActionDefine() :
	icon(0),
	name(new QString("")),
	declare(new QString("")),
	define(new QString(""))
{
	widget = new ActionWidget(this);
	QObject::connect(	widget,	&ActionWidget::param_added,
						this,	&ActionDefine::add_param);
//	QObject::connect(	widget, &ActionWidget::param_cleared,
//						this,	&ActionDefine::remove_param);
	QObject::connect(	widget, SIGNAL(param_cleared(int)),
						this,	SLOT(remove_param(int)));

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

void ActionDefine::remove_param(ActionParam *param)
{
	for (unsigned int i=0; i<list_param.size(); i++) {
		if (list_param[i] == param) {
			list_param.erase(list_param.begin() + i);
			break;
		}
	}
}

void ActionDefine::set_widget(ActionWidget *input)
{
	QObject::disconnect(	widget,	&ActionWidget::param_added,
							this,	&ActionDefine::add_param);
//	QObject::disconnect(	widget, &ActionWidget::param_cleared,
//							this,	&ActionDefine::remove_param);
	QObject::disconnect(	widget, SIGNAL(param_cleared(int)),
							this,	SLOT(remove_param(int)));
	widget = input;
	QObject::connect(	widget,	&ActionWidget::param_added,
						this,	&ActionDefine::add_param);
//	QObject::connect(	widget, &ActionWidget::param_cleared,
//						this,	&ActionDefine::remove_param);
	QObject::connect(	widget, SIGNAL(param_cleared(int)),
						this,	SLOT(remove_param(int)));
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
	tool->setText(*name);
	tool->setIcon(QIcon(definitions::icon[icon]));
}
