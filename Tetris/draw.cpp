
/*	  EXTREME BLOCKS - Copyright (C) 2010 by Oscar D. Olarte  *
 
 *    (c) RPR-GDevelopment - 2010                             *
 *    Written by Oscar Olarte                                 *

 *    This source code is released under the The GNU          *
 *    General Public License (GPL). Please refer to the       *
 *    document license.txt in the source directory or         *
 *    http://www.gnu.org for license information.			  */

#include "ftetris.h"

void drawPiece(cPiece &fig, int tipo)
{
	int color = 0;
	int x = fig.getPosX(); //Get current position of the piece in the board
	int y = fig.getPosY();

	color = fig.type + 1; //Select the color of the piece

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (fig.piece[i][j].full == FILL && tipo == 0) //Draw the current piece
			{
				draw_sprite(map_buffer, temp[color], (x*BLOCK_SIZE) + (j*BLOCK_SIZE), (y*BLOCK_SIZE) + (i*BLOCK_SIZE));
			}

			if (fig.piece[i][j].full == FILL && tipo == 1) //Draw the next piece
			{
				draw_sprite(next_buffer, temp[color], (j*BLOCK_SIZE), (i*BLOCK_SIZE));
			}
		}
	}
}

void drawBoard()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			if (!isFreeBlock(i, j)) //Draws the all board, except the empty spaces
			{
				draw_sprite(map_buffer, temp[map[i][j]], (i*BLOCK_SIZE),(j*BLOCK_SIZE));
			}
		}
	}	
}

void drawInfo(int score, int level, int t, int del, FONT *f, int speed)
{
	//rectfill(screen, 350, 40, 530, 200, makecol(255,255,255));
	//Display information in the score_buffer
	textprintf_ex(score_buffer, f, 5,5, makecol(0,0,0), -1, "Score: %d", score);
	textprintf_ex(score_buffer, f, 5,5, makecol(0,0,0), -1, "Score: %d", score);
	
	if(lev_act == 6){
		textprintf_ex(score_buffer, f, 5,30,makecol(0,0,0), -1, "Level: Practice");}
	else{
		textprintf_ex(score_buffer, f, 5,30,makecol(0,0,0), -1, "Level: %d", level);}
	textprintf_ex(score_buffer, f, 5,55, makecol(0,0,0), -1, "Time: %d ", t);
	textprintf_ex(score_buffer, f, 5,80, makecol(0,0,0), -1, "Finish Level: %d ", time_level[level]);
	textprintf_ex(score_buffer, f, 5,105, makecol(0,0,0), -1, "Delete Rows: %d", del);
	textprintf_ex(score_buffer, f, 5,130, makecol(0,0,0), -1, "Speed: %d", inv_s[speed]-9);

}

void clearScreen()
{
	//Clear all the diferentes bitmaps in the screen
	clear(map_buffer);
	clear_to_color(score_buffer, makecol(255, 255, 255));
	clear(next_buffer);
}