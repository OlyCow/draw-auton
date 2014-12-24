#ifndef ACTIONLIST_H
#define ACTIONLIST_H

#include <vector>
#include "action.h"

class ActionList
{
public:
	ActionList();

	void addAction(Action input);
	void addAction(Action input, int pos);
	void deleteAction();
	void deleteAction(int pos);
	void clearAll();

	int getPos()	{return current_pos;}

	QString getCalls();

private:
	std::vector<Action> base_list;
	int current_pos;
};

#endif // ACTIONLIST_H
