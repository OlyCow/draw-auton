#ifndef ACTIONDEFINE_H
#define ACTIONDEFINE_H

#include <QDebug>

#include <vector>

#include <QObject>

#include "definitions.h"
#include "actionparam.h"
#include "actiontool.h"
#include "actionwidget.h"

class ActionDefine : public QObject
{
	Q_OBJECT

public:
	ActionDefine();
	~ActionDefine();

	void add_param(ActionParam* param)		{ list_param.push_back(param); }
	ActionParam* get_param(int index)		{ return list_param[index]; }
	int get_param_count()					{ return list_param.size(); }

	void set_icon(int index)				{ icon = index; }
	void set_name(QString* input)			{ name = input; }
	void set_declare(QString* input)		{ declare = input; }
	void set_define(QString* input)			{ define = input; }
	void set_tool(ActionTool* input);
	void set_widget(ActionWidget* input);

	int get_icon()					{ return icon; }
	QString* get_name()				{ return name; }
	QString* get_declare()			{ return declare; }
	QString* get_define()			{ return define; }
	ActionTool* get_tool()			{ return tool; }
	ActionWidget* get_widget()		{ return widget; }

public slots:
	void update_data_from_widget();
	void update_tool_with_data();

	void remove_param(int index)	{ list_param.erase(list_param.begin()+index); }
	void remove_param(ActionParam* param);

private:
	ActionTool* tool;
	ActionWidget* widget;

	int icon;
	QString* name;
	QString* declare;
	QString* define;
	std::vector<ActionParam*> list_param;
};

#endif // ACTIONDEFINE_H
