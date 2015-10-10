
/*	  EXTREME BLOCKS - Copyright (C) 2010 by Oscar D. Olarte  *
 
 *    (c) RPR-GDevelopment - 2010                             *
 *    Written by Oscar Olarte                                 *

 *    This source code is released under the The GNU          *
 *    General Public License (GPL). Please refer to the       *
 *    document license.txt in the source directory or         *
 *    http://www.gnu.org for license information.			  */

#include "ftetris.h"
#include "level.h"

void mappingLevel(int lev_act)
{
	//Map the levels by the previous design
	srand((unsigned int) time(NULL));

	switch(lev_act)
	{
	case 0:
		{
			speed = 40;
			lev_act = 0;
			break;
		}

	case 1:
		{
			map[0][19] = map[1][18] = map[4][18] = map[5][19] = map[8][18] =  map[8][17] = gRandom(7,1);
			map[1][19] = map[2][19] = map[4][17] = map[6][18] = map[9][15] = gRandom(6,2);
			map[2][18] = map[4][19] = map[9][19] = map[8][19] = map[9][16] = map[5][18] = gRandom(5,1);
			map[2][17] = map[5][18] = map[6][19] = map[7][18] = map[7][19] = map[9][18] = map[9][17] = gRandom(4,1);

			speed = 35;
			lev_act = 1;
			break;
		}

	case 2:
		{
			map[0][13] = map[0][16] = map[1][17] = map[2][19] = map[4][18] = map[8][17] = map[7][16] = map[8][15] = gRandom(6,1);
			map[1][14] = map[0][18] = map[0][19] = map[5][16] = map[6][19] = map[8][18] = map[9][17] = map[8][16] = gRandom(7,1);
			map[0][15] = map[0][17] = map[3][18] = map[4][17] = map[7][18] = map[9][18] = map[7][15] = map[9][15] = gRandom(5,1);
			map[1][19] = map[3][19] = map[5][17] = map[8][19] = map[7][14] = map[9][14] = map[5][19] = map[7][17] = gRandom(6,2);	
			map[0][14] = map[1][18] = map[5][18] = map[7][19] = map[9][19] = map[9][16] = map[8][14] = map[8][13] = gRandom(4,1);			
			map[2][18] = 1;

			speed = 28;
			lev_act = 2;
			break;
		}

	case 3:
		{
			map[0][14] = map[1][15] = map[1][17] = map[2][19] = map[5][17] = map[5][14] = map[7][16] = map[8][19] = map[9][17] = gRandom(7,1);
			map[1][16] = map[2][14] = map[2][15] = map[4][16] = map[6][15] = map[7][19] = map[9][15] = map[9][12] = map[4][18] = gRandom(6,1);
			map[0][13] = map[0][18] = map[1][19] = map[4][19] = map[5][15] = map[7][18] = map[9][16] = map[9][11] = map[2][17] = gRandom(5,1);
			
			srand((unsigned int) time(NULL));
			map[0][16] = map[1][13] = map[2][16] = map[2][18] = map[4][17] = map[5][13] = map[6][18] = map[9][19] = map[9][14] = gRandom(7,1);
			map[0][19] = map[1][14] = map[3][18] = map[5][19] = map[5][16] = map[6][14] = map[7][17] = map[9][18] = map[9][13] = gRandom(6,1);
			map[0][15] = map[0][17] = map[1][18] = map[3][19] = map[3][17] = map[5][18] = map[6][16] = map[6][17] = map[8][11] = gRandom(5,1);

			speed = 24;
			lev_act = 3;
			break;
		}

	case 4:
		{
			map[0][13] = map[1][15] = map[1][18] = map[3][17] = map[4][14] = map[5][18] = map[7][17] = map[9][15] = map[9][12] = map[7][10] = gRandom(7,1);
			map[0][19] = map[0][15] = map[2][13] = map[3][15] = map[2][18] = map[6][17] = map[7][14] = map[8][19] = map[9][14] = map[9][17] = gRandom(6,2);
			map[0][17] = map[0][14] = map[2][17] = map[2][12] = map[3][19] = map[4][16] = map[6][19] = map[7][16] = map[8][18] = map[9][11] = gRandom(4,1);

			srand((unsigned int) time(NULL));
			map[0][12] = map[1][19] = map[2][14] = map[2][16] = map[4][19] = map[9][19] = map[7][18] = map[8][16] = map[4][13] = map[8][10] = gRandom(6,1);
			map[0][16] = map[0][18] = map[1][14] = map[3][18] = map[3][16] = map[6][18] = map[9][18] = map[9][16] = map[7][15] = map[8][11] = gRandom(5,1);
			map[1][17] = map[1][16] = map[2][15] = map[4][17] = map[4][15] = map[5][19] = map[7][19] = map[8][17] = map[8][15] = map[9][13] = gRandom(7,1);
			map[1][13] = 1;

			speed = 19;
			lev_act = 4;
			break;
		}

	case 5:
		{
			map[9][9] = map[0][11] = map[4][13] = map[5][16] = map[8][16] = map[0][17] = map[3][17] = map[4][18] = map[7][18] = map[9][19] = gRandom(6,1);
			map[9][10] = map[0][10] = map[5][12] = map[2][15] = map[6][15] = map[0][16] = map[8][17] = map[2][18] = map[4][19] = map[8][19] = gRandom(5,1);
			map[8][10] = map[1][10] = map[4][14] = map[4][16] = map[6][16] = map[2][17] = map[7][17] = map[0][19] = map[3][19] = map[6][19] = gRandom(7,1);

			srand((unsigned int) time(NULL));
			map[0][9] = map[9][11] = map[5][13] = map[5][15] = map[2][16] = map[5][17] = map[0][18] = map[6][18] = map[2][19] = map[7][19] = gRandom(7,1);
			map[9][8] = map[0][12] = map[4][15] = map[3][16] = map[4][17] = map[6][17] = map[1][18] = map[3][18] = map[5][18] = map[5][19] = gRandom(6,2);

			speed = 15;
			lev_act = 5;
			break;
		}
	}
}

void modePract(int practice_mode)
{
	switch(practice_mode)
	{
	case 0:
		{
			initMap();
			break;
		}

	case 1:
		{
			fillMap();
			break;
		}
	}
}

void fillMap()
{
	srand((unsigned int) time(NULL));

	int t_blocks = gRandom(25,8);
	int sal;
	initMap();

	for (int i = 0; i < t_blocks; i++)
	{
		sal = 0;
		while(!sal)
		{
			int n_level = gRandom(5,15);
			int b = gRandom(11,0);
			int c = gRandom(7,1);
			int j = 0; 

			while (j < BOARD_WIDTH)  
			{  
				if (map[j][n_level] == 0) //Checks if the row is fill or not
				{
					break;  
				}

				j++;  
			}  
  
			if (j == BOARD_WIDTH) //If it's fill doesn't put more blocks on this
			{
				continue;
			}
			
			if (isFreeBlock(b, n_level))
			{
				map[b][n_level] = c; //Put a block in the random position
				sal = 1;
			}
		}
	}
}

void changeBG(DIALOG *d, int lev_act, int mode)
{
	switch(mode)
	{
	case 0:
		{
			d[1].dp = (BITMAP *)file1[lev_act].dat; //Assign the background of the level to the dialog
			break;
		}

	case 1:
		{
			srand((unsigned int) time(NULL));
			int ind = rand()%6;

			d[1].dp = (BITMAP *)file1[ind].dat; //Assign a random background to the dialog
			break;
		}
	}
}




