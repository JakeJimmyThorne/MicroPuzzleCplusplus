#include "Map.h"
#include "Player.h"
#include "Action.h"

#include <sstream> 
#include <fstream>
#include <string>
#include <cctype>  

#include <vector>

using namespace std;


Map::Map()
{
	specialActionAmount = 10;
	currentRoom = 1;
	b_firstRun = true;

	possibleDirections[0] = "N";
	possibleDirections[1] = "E";
	possibleDirections[2] = "S";
	possibleDirections[3] = "W";
	possibleDirections[4] = "U";
	possibleDirections[5] = "D";
}

Map::~Map()
{

}

void Map::Initilise(std::string gameToLoad, int amountOfRooms)
{
	LoadRooms(gameToLoad,amountOfRooms);
	LoadActions(gameToLoad,amountOfRooms);

	return;
}

void Map::LoadRooms(std::string gameToLoad, int amountOfRooms)
{
	roomAmount = amountOfRooms;

	std::string converted;
	for(int i = 0; i < gameToLoad.size(); ++i)
		converted += (toupper(gameToLoad[i]));

	gameName = converted;

	string txt[200][100];
	string defaultSettings[200];
    string line;

    int i=0;
    ifstream file;

	string toLoad = "games/" + gameToLoad;

	//load in all of the different rooms
	for(int r = 0; r < roomAmount; r++)
	{
		stringstream ss;
		ss << r + 1;

		file.open(toLoad + "/" + ss.str() + ".txt");
		if (file.is_open())
		{
			while (!file.eof())
			{
				getline(file,line);
				txt[i][r]=line;
				i++;
			}
		}

		i = 0;
		file.close();
	}

	//load in the default event text settings
	file.open(toLoad + "/default_text.txt");
	i = 0;
	if (file.is_open())
	{
		while (!file.eof())
		{
			getline(file,line);
			defaultSettings[i]=line;
			i++;
		}
	}

	file.close();

	SetRooms(txt);
	SetDefaults(defaultSettings);

	return;
}
void Map::LoadActions(std::string gameToLoad, int amountOfRooms)
{
	string txt[200][100];
	string defaultSettings[200];
    string line;

    int i=0;
    ifstream file;

	string toLoad = "games/" + gameToLoad + "/actions/";
	string actionList[9];

	//set all types of actions so we can have one for loop
	actionList[0] = "climb";
	actionList[1] = "leave";
	actionList[2] = "open";
	actionList[3] = "point";
	actionList[4] = "press";
	actionList[5] = "put";
	actionList[6] = "tie";
	actionList[7] = "type";
	actionList[8] = "unlock";

	//load in all of the different actions (9 types of actions)
	for(int a = 0; a < 9; a++)
	{
		file.open(toLoad + actionList[a] + ".txt");

		if (file.is_open())
		{
			while (!file.eof())
			{
				getline(file,line);
				txt[i][a]=line;
				i++;
			}
		}

		i = 0;
		file.close();
	}

	SetActions(txt, actionList);
	return;
}

void Map::SetRooms(std::string roomTxt[200][100])
{
	std::cout < "\n\n\n";

	//go through all of the rooms and take the loaded in values
	//for each room and create new objects for those rooms
	for(int i = 0; i < roomAmount; i++)
	{			
		string roomDescription;
		string roomDirections[10];
		string roomItemList[10];
		string roomExamineText;
		string roomSpecialExamineText[10];
		string roomEventText;
		string roomSpecialActions[10];

				//line amount = 200
		for(int l = 0; l < 200; l++)
		{
			if(roomTxt[l][i] == "#description")
				roomDescription = roomTxt[l+1][i];

			if(roomTxt[l][i] == "#directions")
			{
				//possible for a room to go 6 directions
				//add the directions until a '-' is hit
				for(int d = 1; d < 10; d++)
				{
					if(roomTxt[l+d][i] != "-")
						roomDirections[d-1] = roomTxt[l+d][i];
					else break;
				}
			}

			if(roomTxt[l][i] == "#items")
			{
				for(int item = 1; item < 10; item++)
				{
					if(roomTxt[l+item][i] != "-")
						roomItemList[item-1] = roomTxt[l+item][i];
					else break;
				}
			}

			if(roomTxt[l][i] == "#examine")
				roomExamineText = roomTxt[l+1][i];

			if(roomTxt[l][i] == "#examine_special")
			{
				for(int es = 1; es < 10; es++)
				{
					if(roomTxt[l+es][i] != "-")
						roomSpecialExamineText[es-1] = roomTxt[l+es][i];
					else break;
				}
			}

			if(roomTxt[l][i] == "#event_text")
				roomEventText = roomTxt[l+1][i];

			if(roomTxt[l][i] == "#special_actions")
			{
				for(int sa = 1; sa < 10; sa++)
				{
					if(roomTxt[l+sa][i] != "-")
						roomSpecialActions[sa-1] = roomTxt[l+sa][i];
					else break;
				}
			}
		}

		//after sorting through all the data for that room
		//we create and populate a room object then add it
		//to the room list
		Room newRoom;

		newRoom.SetDescription(roomDescription);
		newRoom.SetDirections(roomDirections);
		newRoom.SetObjects(roomItemList);
		newRoom.SetExamineText(roomExamineText);
		newRoom.SetSpecialExamineText(roomSpecialExamineText);
		newRoom.SetEventText(roomEventText);
		newRoom.SetSpecialActions(roomSpecialActions);

		newRoom.SetID(i + 1);

		roomList.push_back(newRoom);
	}

	return;
}
void Map::SetActions(std::string actionTxt[200][100], std::string actionList[9])
{
	std::cout < "\n\n\n";

	for(int i = 0; i < 9; i++)
	{
		vector<int> roomID;
		vector<string> itemToUseOn;
		vector<string> eventText;
		vector<string> LINK;
		vector<string> aPREQ;

		for(int l = 0; l < 200; l++)
		{
			if(actionTxt[l][i].substr(0,1) == "#")
			{
				roomID.push_back(atoi(actionTxt[l][i].substr(1,1).c_str()));
				itemToUseOn.push_back(actionTxt[l+1][i]);
				eventText.push_back(actionTxt[l+2][i]);
				LINK.push_back(actionTxt[l+3][i]);
				aPREQ.push_back(actionTxt[l+4][i]);
			}
		}

		for(int n = 0; n < roomID.size(); n++)
		{
			Action newAction;

			newAction.SetRoomID(roomID[n]);
			newAction.SetItem(itemToUseOn[n]);
			newAction.SetEventText(eventText[n]);
			newAction.Set_LINK(LINK[n]);
			newAction.Set_aPREQ(aPREQ[n]);

			switch(i)
			{
			case 0:
				climbActions.push_back(newAction);
				break;
			case 1:
				leaveActions.push_back(newAction);
				break;
			case 2:
				openActions.push_back(newAction);
				break;
			case 3:
				pointActions.push_back(newAction);
				break;
			case 4:
				pressActions.push_back(newAction);
				break;
			case 5:
				putActions.push_back(newAction);
				break;
			case 6:
				tieActions.push_back(newAction);
				break;
			case 7:
				typeActions.push_back(newAction);
				break;
			case 8:
				unlockActions.push_back(newAction);
				break;
			}
		}
	}

	return;
}
void Map::SetDefaults(std::string defaultTxt[200])
{
	for(int l = 0; l < 200; l++)
	{
		if(defaultTxt[l] == "#event_text")
			defaultEventText = defaultTxt[l+1];

		if(defaultTxt[l] == "#direction_error")
			defaultDirectionError = defaultTxt[l+1];

		if(defaultTxt[l] == "#invalid_input")
			defaultInvalidInput = defaultTxt[l+1];
	}

	return;
}

void Map::PrintRoom()
{
	cout << gameName << endl;
	cout << "============" << endl;

	cout << roomList[currentRoom - 1].GetDescription() << "\n";

	roomList[currentRoom - 1].PrintObjects();
	cout << "\n";

	roomList[currentRoom - 1].PrintDirections();
	cout << endl;

	cout << "------------------" << endl;

	cout << roomList[currentRoom - 1].GetEventText() << endl;

	return;
}

void Map::ProcessInput(std::string playerInput, Player &p)
{
	std::string converted;
	for(int i = 0; i < playerInput.size(); ++i)
		converted += (toupper(playerInput[i]));

	playerInput = converted;
	
	#pragma region player controls

	for(int i = 0; i < 6; i++)
	{
		//DIRECTION CONTROLS
		if(playerInput == possibleDirections[i])
		{
			int previousRoom = currentRoom;

			//based on the player's input, find the next room to go to
			currentRoom = roomList[currentRoom - 1].GetNextRoom(playerInput);

			//if new room isn't found, revert back to old room
			if(currentRoom == -1)
			{
				currentRoom = previousRoom;
				roomList[currentRoom - 1].SetEventText(defaultDirectionError);
			}
			else
			{
				//if the transfer was successful we want to reset the previous room's
				//event text to it's original text.
				roomList[previousRoom - 1].ResetEventText(defaultEventText);
			}

			return;
		}
		else if(playerInput.substr(0,7) == "EXAMINE")
		{
			//if the player has only typed examine
			if(playerInput.size() <= 8)
			{
				roomList[currentRoom - 1].
					SetEventText(roomList[currentRoom - 1].GetExamineText());
				return;
			}
			else 
			{    
				string itemToExamine = playerInput.substr(8,playerInput.size() - 8);

				if(roomList[currentRoom - 1].GetSpecialExamineText(0) != "-")
				{
					string roomSpecialItem[10];

					for(int i = 0; i < 10; i++)
					{
						//if the first entry after examine_special isn't '-', check
						//to see if the item the player gave equals the special event
						if(roomList[currentRoom - 1].GetSpecialExamineText(i) != "-")
						{
							int comma = roomList[currentRoom - 1].
								GetSpecialExamineText(i).find(',');

							roomSpecialItem[i] = roomList[currentRoom - 1].
								GetSpecialExamineText(i).substr(0,comma);

							if(roomSpecialItem[i] == itemToExamine)
							{
								string newExamineText = roomList[currentRoom - 1].
										GetSpecialExamineText(i);

								roomList[currentRoom - 1].
									SetEventText(newExamineText);

								return;
							}
						}
						else
						{
							//we just print the default examine text
							roomList[currentRoom - 1].
								SetEventText(roomList[currentRoom - 1].GetExamineText());

							return;
						}
					}
				}
			}
		}
		else if(playerInput == "I")
		{
			p.PrintInventory();
			return;
		}
		else if(playerInput.substr(0,4) == "TAKE")
		{
			//we don't want to execute any other code if the player has only
			//entered climb as we'll encounter memory access errors
			if(playerInput.size() <= 5)
			{
				roomList[currentRoom - 1].SetEventText("I NEED TWO WORDS");
				return;
			}

			string item = playerInput.substr(5,playerInput.size() - 5);
			vector<Object> tempObjList = roomList[currentRoom - 1].GetObjectList();

			for(int i = 0; i < tempObjList.size(); i++)
			{
				if(tempObjList[i].GetName() == item)
				{
					roomList[currentRoom - 1].SetEventText("YOU HAVE THE " + tempObjList[i].GetName());
					p.AddInventory(tempObjList[i].GetName());

					roomList[currentRoom - 1].RemoveObject(tempObjList[i].GetName());

					return;
				}
			}

			roomList[currentRoom - 1].SetEventText("IT IS NOT HERE");
			return;
		}
		else if(playerInput.substr(0,5) == "LEAVE")
		{
			//we don't want to execute any other code if the player has only
			//entered climb as we'll encounter memory access errors
			if(playerInput.size() <= 6)
			{
				roomList[currentRoom - 1].SetEventText("I NEED TWO WORDS");
				return;
			}

			string item = playerInput.substr(6,playerInput.size() - 6);

			//check special leave actions before the generic leave
			//for(int a = 0; a < leaveActions.size(); a++)
			//{
			//	if(leaveActions[a].GetItem() == item)
			//	{

			//	}
			//}

			if(p.CheckForItem(item))
			{
				p.RemoveInventory(item);
				roomList[currentRoom - 1].AddObject(item);
				roomList[currentRoom - 1].SetEventText("DONE");
				return;
			}

			roomList[currentRoom - 1].SetEventText("YOU DO NOT HAVE " + item);
			return;
		}
		//MISC CONTROLS
		else if(playerInput.substr(0,5) == "CLIMB")
		{
			//we don't want to execute any other code if the player has only
			//entered climb as we'll encounter memory access errors
			if(playerInput.size() <= 6)
			{
				roomList[currentRoom - 1].SetEventText("I NEED TWO WORDS");
				return;
			}

			string itemToClimb = playerInput.substr(6,playerInput.size() - 6);
			UpdateActionsList();

			//go through all of the actions to see if the item is there
			for(int al = 0; al < actionsList.size(); al++)
			{
				for(int a = 0; a < actionsList[al].size(); a++)
				{
					//if the action is there 
					if(actionsList[al][a].GetItem() == itemToClimb)
					{
						//if the action has been done and we're in the right room
						if(actionsList[al][a].Get_LINK_Done()
							&& actionsList[al][a].GetRoomID() == currentRoom)
						{
							currentRoom = roomList[currentRoom - 1].
								GetSpecialActionsRoom("CLIMB");

							roomList[currentRoom - 1].
								SetEventText(actionsList[al][a].GetEventText());

							return;
						}
	
					}
				}
			}

			//to make this part seem sensible there are messages not in the
			//original. In the original these bits are really specific so here
			//i've made them generic
			if(!p.CheckForItem(itemToClimb))
			{
				roomList[currentRoom - 1].
					SetEventText("YOU DO NOT HAVE " + itemToClimb);
				return;
			}
			else if(p.CheckForItem(itemToClimb))
			{
				roomList[currentRoom - 1]. 
					SetEventText("YOU HAVE NOT USED " + itemToClimb);
				return;
			}
		}
		else if(playerInput.substr(0,4) == "OPEN")
		{

		}
		else if(playerInput.substr(0,5) == "POINT")
		{

		}
		else if(playerInput.substr(0,5) == "PRESS")
		{

		}
		else if(playerInput.substr(0,3) == "PUT")
		{

		}
		else if(playerInput.substr(0,3) == "TIE")
		{
			//we don't want to execute any other code if the player has only
			//entered climb as we'll encounter memory access errors
			if(playerInput.size() <= 4)
			{
				roomList[currentRoom - 1].SetEventText("I NEED TWO WORDS");
				return;
			}

			string item = playerInput.substr(4,playerInput.size() - 4);
			string tieTo;

			for(int t = 0; t < tieActions.size(); t++)
			{
				//if it's a valid item and the player has it
				if(tieActions[t].GetItem() == item && p.CheckForItem(item))
				{
					//ask what they want to tie it to and convert it to
					//uppercase to evaluate it
					cout << "TIE THE " << item << " TO WHAT" << endl
						 << "? ";

					getline(cin,tieTo);

					std::string tieToUPPER;
					for(int i = 0; i < tieTo.size(); ++i)
						tieToUPPER += (toupper(tieTo[i]));

					tieTo = tieToUPPER;

					//make sure the player is in the right room and they type the right
					//thing to tie it to then successfully tie it
					if(tieActions[t].GetRoomID() == currentRoom 
						&& tieActions[t].GetItemToUseOn() == tieTo)
					{
						//tell the engine that the item has been tied
						//then remove the item from the players inventory
						tieActions[t].Set_LINK_Done();
						tieActions[t].Set_aPREQ_Done();

						p.RemoveInventory(item);

						roomList[currentRoom - 1].SetEventText(tieActions[t].GetEventText());
						return;
					}
					//else if the room is not the right room or the player
					//tries to tie it to something else then print this
					else if(tieActions[t].GetRoomID() != currentRoom
						|| tieActions[t].GetItemToUseOn() != tieTo)
					{
						roomList[currentRoom - 1].
							SetEventText("YOU CANNOT TIE IT TO " + tieTo);
						return;
					}
				}
			}

			//if the player doesn't have the item print this
			for(int t = 0; t < tieActions.size(); t++)
			{
				if(tieActions[t].GetItem() == item)
				{
					roomList[currentRoom - 1].SetEventText("YOU DO NOT HAVE " + item);
					return;
				}
			}

			//else if the item doesn't exist (in the game) print this
			roomList[currentRoom - 1].SetEventText("CANNOT TIE " + item);
			return;
		}
		else if(playerInput.substr(0,4) == "TYPE")
		{

		}
		else if(playerInput.substr(0,6) == "UNLOCK")
		{

		}
	}

	#pragma endregion

	//we want the first room's event text to be printed, not the invalid
	//input message which was printing first
	if(!b_firstRun)
		roomList[currentRoom - 1].SetEventText(defaultInvalidInput);
	else
	{
		roomList[0].SetEventText(roomList[0].GetEventText());
		b_firstRun = false;
	}

	return;
}

void Map::UpdateActionsList()
{
	actionsList.clear();

	actionsList.push_back(climbActions);
	actionsList.push_back(leaveActions);
	actionsList.push_back(openActions);
	actionsList.push_back(pointActions);
	actionsList.push_back(pressActions);
	actionsList.push_back(putActions);
	actionsList.push_back(tieActions);
	actionsList.push_back(typeActions);
	actionsList.push_back(unlockActions);

	return;
}