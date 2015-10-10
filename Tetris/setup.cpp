
/*	  EXTREME BLOCKS - Copyright (C) 2010 by Oscar D. Olarte  *
 
 *    (c) RPR-GDevelopment - 2010                             *
 *    Written by Oscar Olarte                                 *

 *    This source code is released under the The GNU          *
 *    General Public License (GPL). Please refer to the       *
 *    document license.txt in the source directory or         *
 *    http://www.gnu.org for license information.			  */

#include "ftetris.h"
#include "tgui.h"
#include "bgblocks.h"
#include "sounds.h"

void setupscreen()
{
	int init;
  
    set_color_depth(24);
    init = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);

	set_window_title("Extreme Blocks - Copyright (C) 2010");

    if (init != 0) {
        allegro_message(allegro_error);
        return;
    }

	if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0) 
    {
        allegro_message("Error initializing sound system. Please restart the application");
    }

	/////*Bitmaps For The Game*////
	map_buffer = create_bitmap(200, 400);
	score_buffer = create_bitmap (180, 160);
	next_buffer = create_bitmap(80, 80);
	///////////////////////////////

	if (map_buffer == NULL || score_buffer == NULL || next_buffer == NULL)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Error creating double buffering. Please restart the application");
        return;
    }

	clear(map_buffer);
	clear(score_buffer);
	clear(next_buffer);

	file1 = load_datafile("levels.dat");
	file2 = load_datafile("bgblocks.dat");
	file3 = load_datafile("sounds.dat");

	if (!file1 || !file2 || !file3)
	{
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Error loading the files for the game. Please reinstall the game");
        return;
	}

	ticks = keyboard_counter = fps = fpscount = score = rows_del = 0;

	/////*Loading the sounds for the game*/////
	sound[0] = (SAMPLE *)file3[MENU].dat;
	sound[1] = (SAMPLE *)file3[PLAY].dat;
	sound[2] = (SAMPLE *)file3[PUT].dat;
	sound[3] = (SAMPLE *)file3[LINE].dat;
	sound[4] = (SAMPLE *)file3[CHEER].dat;
	sound[5] = (SAMPLE *)file3[AWWW].dat;
	///////////////////////////////////////////

	volume[0] = options[4].d2;
	volume[1] = options[6].d2;

	////*Loading the fonts used in the game*////
	font = (FONT *)file3[TXS].dat; 
	myfont = (FONT *)file3[TXB].dat;
	////////////////////////////////////////////

	set_display_switch_mode(SWITCH_NONE);
	show_mouse(screen);
}

void setupblocks()
{
	// 0: ****			1: ***
	//						*
	// 2: **			   3: **
	//    **				   **
	//		4:   **				5: ***
	//		    **				   *
	// 6: ***
	//		*

	/*Load the images for every single block of the game*/
	temp[0] = NULL;
	temp[1] = (BITMAP *)file2[BLOCK1].dat;
	temp[2] = (BITMAP *)file2[BLOCK2].dat;
	temp[3] = (BITMAP *)file2[BLOCK3].dat;
	temp[4] = (BITMAP *)file2[BLOCK4].dat;
	temp[5] = (BITMAP *)file2[BLOCK5].dat;
	temp[6] = (BITMAP *)file2[BLOCK6].dat;
	temp[7] = (BITMAP *)file2[BLOCK7].dat;

	for (int k = 0; k < 7; k++)
	{
		for (int m = 0; m < 4; m++)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					blocks[k][m][i][j].ID = 0;
					blocks[k][m][i][j].full = EMPTY;
				}
			}
		}
	}

	//ID for image of the block

	blocks[0][0][0][0].ID = blocks[0][0][0][1].ID = blocks[0][0][0][2].ID = blocks[0][0][0][3].ID = 1;
	blocks[0][1][0][0].ID = blocks[0][1][1][0].ID = blocks[0][1][2][0].ID = blocks[0][1][3][0].ID = 1;
	blocks[0][2][0][0].ID = blocks[0][2][0][1].ID = blocks[0][2][0][2].ID = blocks[0][2][0][3].ID = 1;
	blocks[0][3][0][0].ID = blocks[0][3][1][0].ID = blocks[0][3][2][0].ID = blocks[0][3][3][0].ID = 1;

	blocks[1][0][0][1].ID = blocks[1][0][1][0].ID = blocks[1][0][1][1].ID = blocks[1][0][1][2].ID = 2;
	blocks[1][1][0][0].ID = blocks[1][1][1][0].ID = blocks[1][1][1][1].ID = blocks[1][1][2][0].ID = 2;
	blocks[1][2][0][0].ID = blocks[1][2][0][1].ID = blocks[1][2][0][2].ID = blocks[1][2][1][1].ID = 2;
	blocks[1][3][0][1].ID = blocks[1][3][1][0].ID = blocks[1][3][1][1].ID = blocks[1][3][2][1].ID = 2;

	blocks[2][0][0][0].ID = blocks[2][0][0][1].ID = blocks[2][0][1][0].ID = blocks[2][0][1][1].ID = 3;
	blocks[2][1][0][0].ID = blocks[2][1][0][1].ID = blocks[2][1][1][0].ID = blocks[2][1][1][1].ID = 3;
	blocks[2][2][0][0].ID = blocks[2][2][0][1].ID = blocks[2][2][1][0].ID = blocks[2][2][1][1].ID = 3;
	blocks[2][3][0][0].ID = blocks[2][3][0][1].ID = blocks[2][3][1][0].ID = blocks[2][3][1][1].ID = 3;

	blocks[3][0][0][0].ID = blocks[3][0][0][1].ID = blocks[3][0][1][1].ID = blocks[3][0][1][2].ID = 4;
	blocks[3][1][0][1].ID = blocks[3][1][1][0].ID = blocks[3][1][1][1].ID = blocks[3][1][2][0].ID = 4;
	blocks[3][2][0][0].ID = blocks[3][2][0][1].ID = blocks[3][2][1][1].ID = blocks[3][2][1][2].ID = 4;
	blocks[3][3][0][1].ID = blocks[3][3][1][0].ID = blocks[3][3][1][1].ID = blocks[3][3][2][0].ID = 4;

	blocks[4][0][0][1].ID = blocks[4][0][0][2].ID = blocks[4][0][1][0].ID = blocks[4][0][1][1].ID = 5;
	blocks[4][1][0][0].ID = blocks[4][1][1][0].ID = blocks[4][1][1][1].ID = blocks[4][1][2][1].ID = 5;
	blocks[4][2][0][1].ID = blocks[4][2][0][2].ID = blocks[4][2][1][0].ID = blocks[4][2][1][1].ID = 5;
	blocks[4][3][0][0].ID = blocks[4][3][1][0].ID = blocks[4][3][1][1].ID = blocks[4][3][2][1].ID = 5;

	blocks[5][0][0][0].ID = blocks[5][0][1][0].ID = blocks[5][0][2][0].ID = blocks[5][0][2][1].ID = 6;
	blocks[5][1][0][0].ID = blocks[5][1][0][1].ID = blocks[5][1][0][2].ID = blocks[5][1][1][0].ID = 6;
	blocks[5][2][0][0].ID = blocks[5][2][0][1].ID = blocks[5][2][1][1].ID = blocks[5][2][2][1].ID = 6;
	blocks[5][3][0][2].ID = blocks[5][3][1][0].ID = blocks[5][3][1][1].ID = blocks[5][3][1][2].ID = 6;

	blocks[6][0][0][1].ID = blocks[6][0][1][1].ID = blocks[6][0][2][0].ID = blocks[6][0][2][1].ID = 7;
	blocks[6][1][0][0].ID = blocks[6][1][1][0].ID = blocks[6][1][1][1].ID = blocks[6][1][1][2].ID = 7;
	blocks[6][2][0][0].ID = blocks[6][2][0][1].ID = blocks[6][2][1][0].ID = blocks[6][2][2][0].ID = 7;
	blocks[6][3][0][0].ID = blocks[6][3][0][1].ID = blocks[6][3][0][2].ID = blocks[6][3][1][2].ID = 7;

	//Set the state of full when is occupied

	blocks[0][0][0][0].full = blocks[0][0][0][1].full = blocks[0][0][0][2].full = blocks[0][0][0][3].full = FILL;
	blocks[0][1][0][0].full = blocks[0][1][1][0].full = blocks[0][1][2][0].full = blocks[0][1][3][0].full = FILL;
	blocks[0][2][0][0].full = blocks[0][2][0][1].full = blocks[0][2][0][2].full = blocks[0][2][0][3].full = FILL;
	blocks[0][3][0][0].full = blocks[0][3][1][0].full = blocks[0][3][2][0].full = blocks[0][3][3][0].full = FILL;

	blocks[1][0][0][1].full = blocks[1][0][1][0].full = blocks[1][0][1][1].full = blocks[1][0][1][2].full = FILL;
	blocks[1][1][0][0].full = blocks[1][1][1][0].full = blocks[1][1][1][1].full = blocks[1][1][2][0].full = FILL;
	blocks[1][2][0][0].full = blocks[1][2][0][1].full = blocks[1][2][0][2].full = blocks[1][2][1][1].full = FILL;
	blocks[1][3][0][1].full = blocks[1][3][1][0].full = blocks[1][3][1][1].full = blocks[1][3][2][1].full = FILL;

	blocks[2][0][0][0].full = blocks[2][0][0][1].full = blocks[2][0][1][0].full = blocks[2][0][1][1].full = FILL;
	blocks[2][1][0][0].full = blocks[2][1][0][1].full = blocks[2][1][1][0].full = blocks[2][1][1][1].full = FILL;
	blocks[2][2][0][0].full = blocks[2][2][0][1].full = blocks[2][2][1][0].full = blocks[2][2][1][1].full = FILL;
	blocks[2][3][0][0].full = blocks[2][3][0][1].full = blocks[2][3][1][0].full = blocks[2][3][1][1].full = FILL;

	blocks[3][0][0][0].full = blocks[3][0][0][1].full = blocks[3][0][1][1].full = blocks[3][0][1][2].full = FILL;
	blocks[3][1][0][1].full = blocks[3][1][1][0].full = blocks[3][1][1][1].full = blocks[3][1][2][0].full = FILL;
	blocks[3][2][0][0].full = blocks[3][2][0][1].full = blocks[3][2][1][1].full = blocks[3][2][1][2].full = FILL;
	blocks[3][3][0][1].full = blocks[3][3][1][0].full = blocks[3][3][1][1].full = blocks[3][3][2][0].full = FILL;

	blocks[4][0][0][1].full = blocks[4][0][0][2].full = blocks[4][0][1][0].full = blocks[4][0][1][1].full = FILL;
	blocks[4][1][0][0].full = blocks[4][1][1][0].full = blocks[4][1][1][1].full = blocks[4][1][2][1].full = FILL;
	blocks[4][2][0][1].full = blocks[4][2][0][2].full = blocks[4][2][1][0].full = blocks[4][2][1][1].full = FILL;
	blocks[4][3][0][0].full = blocks[4][3][1][0].full = blocks[4][3][1][1].full = blocks[4][3][2][1].full = FILL;

	blocks[5][0][0][0].full = blocks[5][0][1][0].full = blocks[5][0][2][0].full = blocks[5][0][2][1].full = FILL;
	blocks[5][1][0][0].full = blocks[5][1][0][1].full = blocks[5][1][0][2].full = blocks[5][1][1][0].full = FILL;
	blocks[5][2][0][0].full = blocks[5][2][0][1].full = blocks[5][2][1][1].full = blocks[5][2][2][1].full = FILL;
	blocks[5][3][0][2].full = blocks[5][3][1][0].full = blocks[5][3][1][1].full = blocks[5][3][1][2].full = FILL;

	blocks[6][0][0][1].full = blocks[6][0][1][1].full = blocks[6][0][2][0].full = blocks[6][0][2][1].full = FILL;
	blocks[6][1][0][0].full = blocks[6][1][1][0].full = blocks[6][1][1][1].full = blocks[6][1][1][2].full = FILL;
	blocks[6][2][0][0].full = blocks[6][2][0][1].full = blocks[6][2][1][0].full = blocks[6][2][2][0].full = FILL;
	blocks[6][3][0][0].full = blocks[6][3][0][1].full = blocks[6][3][0][2].full = blocks[6][3][1][2].full = FILL;
	
	//Initialize the point's level for the score
	for (int i = 0; i < 7; i++)
	{
		if (i == 6)
		{
			point_lev[6] = 2;
		}

		point_lev[i] = i*5;
	}

	//For reverse the values of speed
	int j = 0;
	for (int i = 49; i >= 9; i--)
	{
		inv_s[j] = i;
		j++;
	}

	//Time neccesary to beat each level
	time_level[0] = time_level[1] = 300;
	time_level[2] = time_level[3] = 250;
	time_level[4] = 200;
	time_level[5] = 150;
	time_level[6] = 0;

}

void initMap()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			map[i][j] = EMPTY; //Clean the map
		}
	}
}

void initPieces(cPiece &falling, cPiece &after)
{
	srand((unsigned int) time(NULL));

	//Generates the current piece
	falling.type = gRandom(7, 0);
	falling.rotation = gRandom(4, 0);

	changePiece(falling, falling.type, falling.rotation);

	//Set a initial position
	falling.setPosX(4);
	falling.setPosY(0);

	//Generates the next piece
	after.type = gRandom(7, 0);
	after.rotation = gRandom(4, 0);
	
	changePiece(after, after.type, after.rotation);

	after.setPosX(360);
	after.setPosY(160);
}

int gRandom(int limit, int s)
{
	return rand()%limit + s;
}

void destroyEverything()
{
	//Destroy all the pointers, bitmaps, sounds, fonts
	destroy_bitmap(map_buffer);
	destroy_bitmap(score_buffer);
	destroy_bitmap(next_buffer);

	unload_datafile(file1);
	unload_datafile(file2);
	unload_datafile(file3);

	remove_sound();
}

