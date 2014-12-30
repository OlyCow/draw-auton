#include "actioncustom.h"

ActionCustom::ActionCustom(QWidget* parent) :
	setup_widget(new ActionWidget(parent, 0))
{

}

ActionCustom::~ActionCustom()
{
	delete setup_widget;
}

