#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include <vector>

using namespace std;

class Action
{
public:
	Action();
	~Action();

	void SetRoomID(int newID);
	void SetItem(string newItem);
	void SetEventText(string newEvent);
	void Set_LINK(string newLINK);
	void Set_aPREQ(string newAPREQ);

	int GetRoomID();
	string GetItem();
	string GetItemToUseOn();
	string GetEventText();

	string Get_LINK();
	string Get_aPREQ();

	bool Get_LINK_Done();
	bool Get_aPREQ_Done();

	void Set_LINK_Done();
	void Set_aPREQ_Done();

private:
	//only trigger the action if the 
	//player is in a specific room
	int roomID;

	string item;
	//what item this action item needs to be
	//used on to trigger event text and LINKS/aPREQs
	//e.g. Tie thread to tree, tree being the itemToUseOn
	string itemToUseOn;

	//what event text will this action generate
	string eventText;

	//a LINK is an action that needs to be completed
	//before another action can be done
	string LINK;
	bool b_LINK;

	//a aPREQ (short for anti-prerequisite). Opposite of
	//a LINK, the action before must NOT be carried out to
	//access this action
	string aPREQ;
	bool b_aPREQ;
};

#endif