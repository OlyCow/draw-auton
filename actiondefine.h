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
