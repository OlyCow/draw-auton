#ifndef ACTIONTOOL_H
#define ACTIONTOOL_H

#include <QString>

#include <QObject>
#include <QToolButton>

class ActionDefine;
class DrawWindow;

class ActionTool : QToolButton
{
	Q_OBJECT

	friend class DrawWindow;

public:
	ActionTool(QString name, QString icon, ActionDefine* action, QWidget* parent=NULL);
	~ActionTool();

private:
	ActionDefine* parent_action;
};

#endif // ACTIONTOOL_H
