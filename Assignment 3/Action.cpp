#include "Action.h"

Action::Action()
{

}
Action::~Action()
{

}

void Action::SetRoomID(int newID)
{
	roomID = newID;
	return;
}
void Action::SetItem(string newItem)
{
	int comma = newItem.find(',');

	//if there is a comma
	if(comma != -1)
	{
		item = newItem.substr(0,comma);
		itemToUseOn = newItem.substr(comma + 1,newItem.size() - comma + 1);
	}
	else
	{
		item = newItem;
		itemToUseOn = "-";
	}

	return;
}
void Action::SetEventText(string newEvent)
{
	eventText = newEvent;
	return;
}
void Action::Set_LINK(string newLINK)
{
	LINK = newLINK;
	b_LINK = false;

	return;
}
void Action::Set_aPREQ(string newAPREQ)
{
	aPREQ = newAPREQ;
	b_aPREQ = false;

	return;
}

int Action::GetRoomID()
{
	return roomID;
}
string Action::GetItem()
{
	return item;
}
string Action::GetItemToUseOn()
{
	return itemToUseOn;
}
string Action::GetEventText()
{
	return eventText;
}

string Action::Get_LINK()
{
	return LINK;
}
string Action::Get_aPREQ()
{
	return aPREQ;
}

bool Action::Get_LINK_Done()
{
	return b_LINK;
}
bool Action::Get_aPREQ_Done()
{
	return b_aPREQ;
}

void Action::Set_LINK_Done()
{
	b_LINK = true;
	return;
}
void Action::Set_aPREQ_Done()
{
	b_aPREQ = true;
	return;
}