#include "actionlist.h"

ActionList::ActionList() :
	base_list(),
	current_pos(0)
{
}

void ActionList::addAction(Action* input)
{
	base_list.push_back(input);
	current_pos = base_list.size() - 1; // because array index (untested)
}

void ActionList::addAction(Action* input, int pos)
{
	std::vector<Action*>::iterator pointer = base_list.begin() + pos;
	base_list.insert(pointer, input);
	current_pos = pos;
}

void ActionList::deleteAction()
{
	base_list.pop_back();
	current_pos = base_list.size() - 1; // because array index (untested)
}

void ActionList::deleteAction(int pos)
{
	std::vector<Action*>::iterator pointer = base_list.begin();
	pointer += pos;
	base_list.erase(pointer);
	current_pos = pos - 1;
}

void ActionList::clearAll()
{
	base_list.clear();
	current_pos = 0;
}

QString ActionList::getCalls()
{
	QString output;
	for (unsigned int i=0; i<base_list.size(); i++) {
		output += "\t";
		if ((base_list[i])->isType() == TYPE_CUSTOM) {
			output += dynamic_cast<ActionCustom*>(base_list[i])->getCall();
		} else {
			output += (base_list[i])->getCall();
		}
	}
	return output;
}
