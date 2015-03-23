#ifndef ACTIONTOOL_H
#define ACTIONTOOL_H

#include <QString>

#include <QObject>
#include <QToolButton>

#include "definitions.h"

class ActionDefine;

class ActionTool : public QToolButton
{
	Q_OBJECT

public:
	ActionTool(QString name, QString icon, ActionDefine* parentDefine, QWidget* parentWidget = NULL);
	~ActionTool();

	void set_parent(ActionDefine* ptr)	{parent = ptr;}

	ActionDefine* get_parent()			{return parent;}

private:
	ActionDefine* parent;
};

#endif // ACTIONTOOL_H
