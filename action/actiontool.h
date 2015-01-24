#ifndef ACTIONTOOL_H
#define ACTIONTOOL_H

#include <QString>

#include <QObject>
#include <QToolButton>

class ActionDefine;
class DrawWindow;

class ActionTool : public QToolButton
{
	Q_OBJECT

	friend class DrawWindow;

public:
	ActionTool(QString name, QString icon, ActionDefine* action, QWidget* parent=NULL);
	~ActionTool();

	void setDefine(ActionDefine* input)	{define = input;}

private:
	ActionDefine* define;
};

#endif // ACTIONTOOL_H
