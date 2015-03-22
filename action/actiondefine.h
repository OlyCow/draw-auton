#ifndef ACTIONDEFINE_H
#define ACTIONDEFINE_H

#include "definitions.h"

#include <vector>

#include <QObject>

#include "actiontool.h"
#include "actionwidget.h"

class ActionDefine : public QObject
{
	Q_OBJECT

public:
	ActionDefine();
	~ActionDefine();

	void set_tool(ActionTool* input)		{tool = input;}
	void set_widget(ActionWidget* input)	{widget = input;}

	void set_tool_name(QString input);
	void set_tool_icon(int input_index);

private slots:
	void param_add();
	void param_clear(int index);

private:
	ActionTool* tool;
	ActionWidget* widget;
	std::vector<QString> list_params;
	std::vector<QString> list_icons;
};

#endif // ACTIONDEFINE_H
