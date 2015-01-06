#ifndef ACTIONTOOL_H
#define ACTIONTOOL_H

#include <QString>

#include <QToolButton>

class DrawWindow;

class ActionTool
{

	friend class DrawWindow;

public:
	ActionTool(QString name, QString icon, QWidget* parent=NULL);
	~ActionTool();

private:
	QToolButton* toolButton;
};

#endif // ACTIONTOOL_H
