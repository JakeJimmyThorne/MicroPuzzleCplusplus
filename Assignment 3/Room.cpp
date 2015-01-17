#include "Room.h"

#include <string>

Room::Room()
{
}

Room::~Room()
{

}

std::string Room::GetDescription()
{
	return description;
}
std::string Room::GetExamineText()
{
	return examineText;
}
std::string Room::GetSpecialExamineText(int textToGet)
{
	return specialExamineText[textToGet];
}
std::string Room::GetEventText()
{
	return eventText;
}
int Room::GetNextRoom(std::string playerInput)
{
	for(int i = 0; i < 6; i++)
	{
		if(playerInput == directions[i].substr(0,1))
			return atoi(directions[i].substr(1,1).c_str());
	}

	return -1;
}
int Room::GetSpecialActionsRoom(std::string actionToGet)
{
	for(int t = 0; t < 9; t++)
	{
		int comma = specialActions[t].find(",");

		if(comma != -1 && specialActions[t].substr(0,comma) == actionToGet)
		{
			std::string temp = specialActions[t].
				substr(comma + 1,specialActions[t].size() - comma + 1);

			return atoi(temp.c_str());
		}
	}
}


void Room::PrintObjects()
{
	for(int i = 0; i < objectList.size(); i++)
	{
		std::cout << "THERE IS A " << objectList[i].GetName() << " HERE" << std::endl;
	}
}
void Room::PrintDirections()
{
	std::cout << "YOU CAN GO ";

	for(int i = 0; i < 6; i ++)
	{
		if(directions[i].size() != 0)
		{
			std::cout << directions[i].substr(0,1) << ",";
		}
	}

	return;
}

void Room::SetDescription(std::string newDesc)
{
	description = newDesc;
	return;
}
void Room::SetExamineText(std::string newExam)
{
	examineText = newExam;
	return;
}
void Room::SetSpecialExamineText(std::string newExam[10])
{
	for(int i = 0; i < 10; i++)
		if(newExam[i] != "-")
			specialExamineText[i] = newExam[i];
	return;
}
void Room::SetEventText(std::string newEvent)
{
	eventText = newEvent;
	return;
}
void Room::SetDirections(std::string newDir[10])
{
	for(int i = 0; i < 10; i++)
	{
		if(newDir[i] != "")
			directions[i] = newDir[i];
	}

	return;
}
void Room::SetObjects(std::string newObjects[10])
{
	for(int i = 0; i < 10; i++)
	{
		if(newObjects[i] != "")
		{
			Object newObject;
			newObject.SetName(newObjects[i]);

			objectList.push_back(newObject);
		}
	}

	return;
}
void Room::SetSpecialActions(std::string newSActions[10])
{
	for(int i = 0; i < 10; i++)
		if(newSActions[i] != "")
			specialActions[i] = newSActions[i];

	return;
}

void Room::ResetEventText(std::string defaultTxt)
{
	eventText = defaultTxt;
	return;
}

std::vector<Object> Room::GetObjectList()
{
	return objectList;
}

void Room::AddObject(std::string objectToAdd)
{
	Object newObject;
	newObject.SetName(objectToAdd);

	objectList.push_back(newObject);

	return;
}

void Room::RemoveObject(std::string objectToRemove)
{
	for(int i = 0; i < objectList.size(); i++)
	{
		if(objectList[i].GetName() == objectToRemove)
			objectList.erase(objectList.begin() + i);
	}

	return;
}

void Room::CheckAction()
{

}

int Room::GetID()
{
	return ID;
}
void Room::SetID(int newID)
{
	ID = newID;
	return;
}