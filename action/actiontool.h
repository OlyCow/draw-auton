#ifndef ACTIONTOOL_H
#define ACTIONTOOL_H

#include <QString>

#include <QObject>
#include <QToolButton>

class ActionDefine;

class ActionTool : public QToolButton
{
	Q_OBJECT

public:
	ActionTool(QString name, QString icon, ActionDefine* parentDefine, QWidget* parentWidget = NULL);
	~ActionTool();

	void setParent(ActionDefine* ptr)	{parent = ptr;}

	ActionDefine* getParent()			{return parent;}

private:
	ActionDefine* parent;
};

#endif // ACTIONTOOL_H
