#ifndef ACTIONLIST_H
#define ACTIONLIST_H

#include "definitions.h"

#include <vector>

#include "action.h"

class ActionList
{
public:
	ActionList();

	void addAction(Action* input);
	void addAction(Action* input, int pos);
	void deleteAction();
	void deleteAction(int pos);
	void clearAll();

	int getSize()	{return base_list.size();}

	int getPos()	{return current_pos;}

	Action* getAction(int index)	{return base_list[index];}

	QString getCalls();

private:
	std::vector<Action*> base_list;
	int current_pos;
};

#endif // ACTIONLIST_H
