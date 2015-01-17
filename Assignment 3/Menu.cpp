#include "Menu.h"

#include <iostream>
#include <sstream> 
#include <fstream>
#include <string>  

using namespace std;


Menu::Menu()
{

}
Menu::~Menu()
{

}

void Menu::LoadMaps()
{
	string txt[200];
    string line;

    int i=0;
    ifstream file;

	file.open("games/games.txt");

	if (file.is_open())
	{
		while (!file.eof())
		{
			getline(file,line);
			txt[i]=line;
			i++;
		}
	}

	file.close();

	for(int i = 0; i < 100; i++)
	{
		if(txt[i].substr(0,1) == "#")
		{
			games.push_back(txt[i].substr(1,txt[i].size() - 1));
			gameRoomAmounts.push_back(atoi(txt[i+1].c_str()));
		}
	}

	return;
}

void Menu::PrintMenu()
{
	cout << "--Jake's Text Adventure Engine--\n\n";
	cout << "Please select a game to launch:" << endl;

	for(int i = 0; i < games.size(); i++)
		cout << i + 1 << ") " << games[i] << endl;

	cout << "? ";

	bool picking = true;

	while(picking)
	{
		cin >> selection;

		if(selection > 0 && selection < games.size() + 1)
			picking = false;
		else
			cout << "Invalid selection." << endl
			     << "? ";
	}

	return;
}

void Menu::SetSelection(int newSelect)
{
	return;
}
std::string Menu::GetSelection()
{
	return games[selection - 1];
}
int Menu::GetSelectionSize()
{
	return gameRoomAmounts[selection - 1];
}