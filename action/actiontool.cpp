#include "actiontool.h"

ActionTool::ActionTool(QString name, QString icon, ActionDefine* parentDefine, QWidget* parentWidget) :
	parent(parentDefine),
	QToolButton(parentWidget)
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
	// TODO: pointer to parent should NOT be deleted here?
}
