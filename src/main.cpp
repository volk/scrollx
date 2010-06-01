#include <iostream>
#include <sstream>
#include <allegro.h>
#include <stdlib.h>
#include "Video.cpp"
#include "Gravity.cpp"

int main()
{
	//Loading all materials except for the player material
	Video* game = new Video(480,640,32);
	game->addMaterial("grass01", "../data/grass.bmp",50,50);
	game->addBasePlatform("grass01", 40);
	game->addPlatform("grass01", 640/2, 480/2, 640, 480/2+40);
	game->addPlayer("Player", "../data/player.bmp", 25, 40, 50, 250);
//	game->addPlayer("NameOfPlayer", "texture_name", width, height, start xo, start yo);
	while ( !key[KEY_ESC] )
	{
		game->clearKeyboardBuffer();


		if(key[KEY_RIGHT])
		{
			game->update(EAST, NEITHER);
		}
		else if(key[KEY_LEFT])
		{
			game->update(WEST, NEITHER);
		}
		else if(key[KEY_UP])
		{
			game->update(NEITHER, NORTH);
		}
		else
		{
			game->update(NEITHER, NEITHER);
		}

		rest(1);
	}
	
	return 0;
}



