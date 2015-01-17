#include "Player.h"
#include <string>

using namespace std;

Player::Player()
{

}

Player::~Player()
{

}

std::string Player::GetInput()
{
	string playerInput;

	cout << "WHAT WILL YOU DO NOW?" << endl
		 << "? ";

	//cin.ignore();
	getline(cin,playerInput);

	return playerInput;
}

void Player::PrintInventory()
{
	cout << "YOU ARE CARRYING:" << endl;

	for(int i = 0; i < inventoryList.size(); i++)
	{
		cout << inventoryList[i].GetName() << ",";
	}

	cout << "\nPRESS RETURN TO CONTINUE";
	cin.ignore();

	return;
}

void Player::AddInventory(std::string newItem)
{
	Object newObject;
	newObject.SetName(newItem);

	inventoryList.push_back(newObject);
	return;
}

void Player::RemoveInventory(std::string delItem)
{
	for(int i = 0; i < inventoryList.size(); i++)
	{
		if(inventoryList[i].GetName() == delItem)
			inventoryList.erase(inventoryList.begin() + i);
	}

	return;
}





bool Player::CheckForItem(std::string itemToCheck)
{
	for(int i = 0; i < inventoryList.size(); i++)
	{
		if(inventoryList[i].GetName() == itemToCheck)
			return true;
	}

	return false;
}