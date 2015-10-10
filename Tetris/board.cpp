
/*	  EXTREME BLOCKS - Copyright (C) 2010 by Oscar D. Olarte  *
 
 *    (c) RPR-GDevelopment - 2010                             *
 *    Written by Oscar Olarte                                 *

 *    This source code is released under the The GNU          *
 *    General Public License (GPL). Please refer to the       *
 *    document license.txt in the source directory or         *
 *    http://www.gnu.org for license information.			  */

#include "ftetris.h"
#include "tgui.h"

void putBlock(cPiece &falling, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if(falling.piece[j][i].ID != 0)
			{
				map[x+i][y+j] = falling.piece[j][i].ID; //Put the piece in the map
			}
		}
	}

	score = score + 10; //Add points to the score
}

int noCollision(cPiece &falling, int x, int y)
{
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++)
		{
			if ((x+i) < 0 || (x+i) > BOARD_WIDTH - 1 || (y+j) > BOARD_HEIGHT - 1) //Checks limits of the board
			{
				if (falling.piece[j][i].ID != 0)
				{
					return false;
				}
			}
			
			if ((y+j) >= 0)
			{
				if (falling.piece[j][i].full == FILL && (!isFreeBlock(x+i, y+j))) //Checks the next position of the current block for collision
				{
					return false;
				}
			}
		}
	}

	return true;
}

int gameOver()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		if (map[i][0] != 0) //Verify the row of the top if has any block
		{
			return 1;
		}
	}

	return 0;
}

void deleteRow(int row)
{
    for (int j = row; j > 0; j--)  
    {  
        for (int i = 0; i < BOARD_WIDTH; i++)  
        {  
            map[i][j] = map[i][j-1];  //Move the all map one row down from the deleted row
        }  
    }  
}

void possibleRows()
{
	int count;
	count = 0;

	for (int j = 0; j < BOARD_HEIGHT; j++)  
    {  
        int i = 0;  
        while (i < BOARD_WIDTH)  
        {  
            if (map[i][j] == 0) //Checks if the row it's full
			{
				break;  
			}

            i++;  
        }  
  
        if (i == BOARD_WIDTH) //If it's full delete the row
		{
			deleteRow (j);
			count++;
		}
    }

	rows_del = rows_del + count;
	score = score + (count*100) + (point_lev[lev_act]*2);

	/*Changes speed and add point bonus depending on how many lines the player make*/
	if (count == 1)
	{
		play_sample(sound[3], volume[1], 128, 1000, FALSE);
		speed = speed + 1;
		bonus[0]++;

		if (speed > 49)
		{
			speed = 49;
		}
	}

	else if (count == 2 || count == 3)
	{
		play_sample(sound[3], volume[1], 128, 1000, FALSE);
		bonus[1]++;
		speed = speed + 3;

		if (speed > 49)
		{
			speed = 49;
		}
	}

	else if (count == 4)
	{
		play_sample(sound[3], volume[1], 128, 1000, FALSE);
		bonus[2]++;
		speed = speed + 5;

		if (speed > 49)
		{
			speed = 49;
		}
	}
}

int isFreeBlock(int x, int y)
{
	if (map[x][y] == EMPTY) //Verify if the position is empty
	{
		return 1;
	}

	else
		return 0;
}

void bonusPoints()
{
	//Gives a extra points at the end of each level
	bonus[0] = bonus[0]*100;
	bonus[1] = bonus[1]*200;
	bonus[2] = bonus[2]*500;

	score = score + bonus[0] + bonus[1] + bonus[2];
}
