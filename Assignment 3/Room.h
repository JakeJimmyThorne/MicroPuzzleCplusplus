#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <vector>
#include "Object.h"

class Room
{
public:
	Room();
	~Room();

	std::string GetDescription();
	std::string GetExamineText();
	std::string GetSpecialExamineText(int textToGet);
	std::string GetEventText();
	int GetNextRoom(std::string playerInput);
	int GetSpecialActionsRoom(std::string actionToGet);

	void PrintDirections();
	void PrintObjects();

	void SetDescription(std::string newDesc);
	void SetExamineText(std::string newExam);
	void SetSpecialExamineText(std::string newExam[10]);
	void SetEventText(std::string newEvent);
	void SetDirections(std::string newDir[10]);
	void SetObjects(std::string newObjects[10]);
	void SetSpecialActions(std::string newSActions[10]);

	void ResetEventText(std::string defaultTxt);

	std::vector<Object> GetObjectList();
	void AddObject(std::string objectToAdd);
	void RemoveObject(std::string objectToRemove);

	void CheckAction();

	int GetID();
	void SetID(int newID);

private:
	std::vector<Object> objectList;

	std::string directions[10];
	bool b_directionPassable[10];

	std::string description;
	std::string examineText;
	std::string specialExamineText[10];
	std::string eventText;

	std::string specialActions[10];

	int ID;
};

#endif