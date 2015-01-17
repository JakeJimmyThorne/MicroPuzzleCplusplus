#include <iostream>
#include <string>

#include <windows.h>

#include "Map.h"
#include "Menu.h"
#include "Player.h"

void ClearScreen();

//TODO add menu system
//reads all game names in games.txt and has them as menu options

int main()
{
	int life = 100;
	bool b_won = false;

	std::string winText;

	Map map;
	Menu menu;
	Player player;

	menu.LoadMaps();
	menu.PrintMenu();

	map.Initilise(menu.GetSelection(),
				menu.GetSelectionSize());

	do
	{
		ClearScreen();
		map.PrintRoom();
	
		map.ProcessInput(player.GetInput(), player);
		life--;

	} while(life > 0);

	std::cin.ignore();

	return 0;
}

void ClearScreen()
{
	//A windows API specific way to clear the console. 
	//brought in from:
	// http://www.cplusplus.com/articles/4z18T05o/

	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
	hStdOut,
	(TCHAR) ' ',
	cellCount,
	homeCoords,
	&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
	hStdOut,
	csbi.wAttributes,
	cellCount,
	homeCoords,
	&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition( hStdOut, homeCoords );

	return;
}