
/*	  EXTREME BLOCKS - Copyright (C) 2010 by Oscar D. Olarte  *
 
 *    (c) RPR-GDevelopment - 2010                             *
 *    Written by Oscar Olarte                                 *

 *    This source code is released under the The GNU          *
 *    General Public License (GPL). Please refer to the       *
 *    document license.txt in the source directory or         *
 *    http://www.gnu.org for license information.			  */

#include "ftetris.h"

void createBlock(cPiece &falling, cPiece &after)
{
	falling.type = after.type; //Copy the next piece to the falling piece
	falling.rotation = after.rotation;

	changePiece(falling, falling.type, falling.rotation);

	falling.setPosX(4); //Set the new position of the piece
	falling.setPosY(0);

	after.type = gRandom(7, 0); //Select the new next piece and his color
	after.rotation = gRandom(4, 0);

	changePiece(after, after.type, after.rotation);
}

void changePiece(cPiece &falling, int p, int rotation)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++) 
		{
			//Rotate the piece
			falling.piece[i][j].ID = blocks[p][rotation][i][j].ID;
			falling.piece[i][j].full = blocks[p][rotation][i][j].full;
		}
	}
}

int rotateBlock(int rotate, int actual)
{
	if (rotate) //Rotate block to right of left depending on the current rotation and the pressed key of the player
	{
		if (actual == 3)
		{
			actual = 0;
		}
		else
			actual++;
	}

	else
	{
		if (actual == 0)
		{
			actual = 3;
		}
		else
			actual--;
	}

	return actual;
}

void cleanPiece(cPiece &temp)
{
	//Clear the piece for create new one.
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp.piece[i][j].ID = 0;
			temp.piece[i][j].full = EMPTY;
		}
	}
}









