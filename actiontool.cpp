#include "actiontool.h"

ActionTool::ActionTool(QString name, QString icon, QWidget* parent) :
	toolButton(new QToolButton(parent))
{
	toolButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	toolButton->setMinimumWidth(50);
	toolButton->setCursor(Qt::PointingHandCursor);
	toolButton->setText(name);
	toolButton->setIcon(QIcon(icon));
	toolButton->setIconSize(QSize(24, 24));
	toolButton->setCheckable(true);
	toolButton->setAutoExclusive(true);
	toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

ActionTool::~ActionTool()
{
	delete toolButton;
}

