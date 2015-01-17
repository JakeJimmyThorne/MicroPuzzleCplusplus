#ifndef MAP_H
#define MAP_H

#include<iostream>
#include <vector>

#include "Room.h"
#include "Player.h"
#include "Action.h"

class Map
{
public:
	Map();
	~Map();

	void Initilise(std::string gameToLoad, int amountOfRooms);

	void LoadRooms(std::string gameToLoad, int amountOfRooms);
	void LoadActions(std::string gameToLoad, int amountOfRooms);

	void SetRooms(std::string roomTxt[200][100]);
	void SetActions(std::string actionTxt[200][100],std::string actionList[9]);
	void SetDefaults(std::string defaultTxt[200]);
	void PrintRoom();

	void ProcessInput(std::string playerInput, Player &p);

	void UpdateActionsList();

private:
	bool b_firstRun;

	std::vector<Room> roomList;
	int currentRoom;

	int roomAmount;

	std::string possibleDirections[12];

	std::string defaultEventText;
	std::string defaultDirectionError;
	std::string defaultInvalidInput;

	//special action variables
	int specialActionAmount;
	std::vector< std::vector<Action> > actionsList;

	std::vector<Action> climbActions;
	std::vector<Action> leaveActions;
	std::vector<Action> openActions;
	std::vector<Action> pointActions;
	std::vector<Action> pressActions;
	std::vector<Action> putActions;
	std::vector<Action> tieActions;
	std::vector<Action> typeActions;
	std::vector<Action> unlockActions;

	std::string gameName;
};

#endif