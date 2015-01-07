#include "actiontool.h"

ActionTool::ActionTool(QString name, QString icon, ActionDefine* action, QWidget* parent) :
	QToolButton(parent),
	parent_action(action)
{
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	setMinimumWidth(50);
	setCursor(Qt::PointingHandCursor);
	setText(name);
	setIcon(QIcon(icon));
	setIconSize(QSize(24, 24));
	setCheckable(true);
	setAutoExclusive(true);
	setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

ActionTool::~ActionTool()
{
	delete parent_action;
}

