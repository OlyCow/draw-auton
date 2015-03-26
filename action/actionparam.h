#ifndef ACTIONPARAM_H
#define ACTIONPARAM_H

#include <QString>

class ActionParam
{
public:
	ActionParam(int icon_index, QString param=QString());
	~ActionParam();

	void set_icon(int icon_index)	{ icon = icon_index; }
	void set_text(QString param)	{ text = param; }

	int get_icon()		{ return icon; }
	QString get_text()	{ return text; }

protected:
	ActionParam();

private:
	int icon;
	QString text;
};

#endif // ACTIONPARAM_H
