#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>

class Menu
{
public:
	Menu();
	~Menu();

	void LoadMaps();
	void PrintMenu();

	void SetSelection(int newSelect);
	std::string GetSelection();
	int GetSelectionSize();

private:
	int selection;
	std::vector<std::string> games;
	std::vector<int> gameRoomAmounts;

};

#endif