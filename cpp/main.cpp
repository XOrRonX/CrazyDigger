
#define _CRT_SECURE_NO_WARNINGS


#ifdef _DEBUG
#pragma comment ( lib , "sfml-main-d.lib" )
#pragma comment ( lib , "sfml-system-d.lib" )
#pragma comment ( lib , "sfml-window-d.lib" )
#pragma comment ( lib , "sfml-graphics-d.lib" )
#elif defined (NDEBUG)
#pragma comment ( lib , "sfml-main.lib" )
#pragma comment ( lib , "sfml-system.lib" )
#pragma comment ( lib , "sfml-window.lib" )
#pragma comment ( lib , "sfml-graphics.lib" )
#else
#error "Unrecognized configuration!"
#endif


#include "Controller.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "Game.h"

void getAllFilesToScreen();

std::unique_ptr<Game> myGame(new Game());


int main()
{
	bool notExit = true;
	unsigned int firstTime = 1;

	// endless loop while the user want to play
	while (notExit)
	{
		//
		getAllFilesToScreen();
		notExit = myGame->run(firstTime);
		if (notExit)
			myGame.reset(new Game());
		firstTime = 0;
	}
		
	return 0;
}



// Look for all the board files with the right name
// if it is there then read it and create another controller
// the format of the files is board.bomb1.txt, board.bomb2.txt
// and so on untill there are no more files with the next 
// incremental number
void getAllFilesToScreen()
{
	char fileName[20] = "board", nextName[20];
	char num[10];
	int i = 0;
	bool moreScreens = true;

	while (moreScreens)
	{
		i++;
		// build the new name
		strcpy(nextName, fileName);
		_itoa(i, num, 10);
		strcat(nextName, num);
		strcat(nextName, ".txt");

		// check if it exist
		std::ifstream ifile(nextName);
		if (ifile)
			// if exist add a controller
			myGame->addController(nextName);
		else
			// if not then no more screens can stop the loop
			moreScreens = false;
	}
}
