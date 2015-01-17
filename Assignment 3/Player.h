#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>

#include "Object.h"

class Player
{
public:
	Player();
	~Player();

	std::string GetInput();
	void PrintInventory();

	void AddInventory(std::string newItem);
	void RemoveInventory(std::string delItem);
	bool CheckForItem(std::string itemToCheck);

private:
	std::vector<Object> inventoryList;

};

#endif