
/*	  EXTREME BLOCKS - Copyright (C) 2010 by Oscar D. Olarte  *
 
 *    (c) RPR-GDevelopment - 2010                             *
 *    Written by Oscar Olarte                                 *

 *    This source code is released under the The GNU          *
 *    General Public License (GPL). Please refer to the       *
 *    document license.txt in the source directory or         *
 *    http://www.gnu.org for license information.			  */

#include "ftetris.h"
#include "tgui.h"

int playGame()
{
	int tempx = current.getPosX(); //Temp variables for position
	int tempy = current.getPosY();

	if (keyboard_counter > 0 && keypressed()) //Keyboard Delay
	{
		if (key[KEY_LEFT]) //Move to the left
		{
			if (noCollision(current, tempx - 1, tempy)) //Checks collisions with the left movement
			{
				tempx--; //If there is not collision move the piece
				current.setPosX(tempx);
			}
		}
			
		if (key[KEY_RIGHT])
		{
			if (noCollision(current, tempx + 1, tempy))
			{
				tempx++;
				current.setPosX(tempx);
			}
		}
		
		if (key[KEY_DOWN])
		{
			if (noCollision(current, tempx, tempy + 1))
			{
				tempy++;
				current.setPosY(tempy);
			}
		}
		
		if (key[KEY_UP]) //Rotate the piece to the right
		{	
			/*Create a temp piece for the request rotation*/

			cPiece temp;
				
			temp.type = current.type;
			temp.rotation = rotateBlock(1, current.rotation);
				
			cleanPiece(temp);
			changePiece(temp, temp.type, temp.rotation);
			temp.setPosX(current.getPosX());
			temp.setPosY(current.getPosY());
				
			if (noCollision(temp, temp.getPosX(), temp.getPosY())) //Checks collision for the temp piece
			{
				//If there is not collision, the real falling(current) piece rotates to the right
				current.rotation = rotateBlock(1, current.rotation);
				cleanPiece(current);
				changePiece(current, current.type, current.rotation);
			}
		}

		if (key[KEY_T]) //Up the volume of the music
		{
			volume[0]+= 5;
			if (volume[0] > 255){
				volume[0] = 255;}

			options[4].d2 = volume[0];
			adjust_sample(sound[0], volume[0], 128, 1000, TRUE);
			adjust_sample(sound[1], volume[0], 128, 1000, TRUE);
		}

		if (key[KEY_G]) //Down the volume of the music
		{
			volume[0]-= 5;
			if (volume[0] < 0){
				volume[0] = 0;}

			options[4].d2 = volume[0];
			adjust_sample(sound[0], volume[0], 128, 1000, TRUE);
			adjust_sample(sound[1], volume[0], 128, 1000, TRUE);
		}

		if (key[KEY_Y]) //Up the volume of the sound effects
		{
			volume[1]+= 5;
			if (volume[1] > 255){
				volume[1] = 255;}

			options[6].d2 = volume[1];
			adjust_sample(sound[2], volume[1], 128, 1000, TRUE);
			adjust_sample(sound[3], volume[1], 128, 1000, TRUE);
		}

		if (key[KEY_H]) //Down the volume of the sound effects
		{
			volume[1]-= 5;
			if (volume[1] < 0){
				volume[1] = 0;}

			options[6].d2 = volume[1];
			adjust_sample(sound[2], volume[1], 128, 1000, TRUE);
			adjust_sample(sound[3], volume[1], 128, 1000, TRUE);
		}

	keyboard_counter--;
	}

    fpscount++;
	
	if (ticks > speed) 
	{
		tempx = current.getPosX();
		tempy = current.getPosY();
		
		if (noCollision(current, tempx, tempy + 1)) //Checks collision for the falling
		{
			tempy++;
			current.setPosY(tempy);
		}
		
		else
		{
			play_sample(sound[2], volume[1], 128, 1000, FALSE);
			putBlock(current, tempx, tempy); //Put block on the board

			possibleRows(); //Check if a row is fill

			if (gameOver()) //Checks if the game is over
			{
				quitgame = 1;
			}
			
			else
				createBlock(current, next); //If the game it's not over create new pieces

		}

		ticks = 0;

	}

	return quitgame;
}

void newGame(int l, int p, int t)
{
	//Setup the new game features
	clearScreen();
	setupblocks();
	initMap();
	initPieces(current, next);
	time_l = rows_del = 0; //Initialize the variable that checks time of the level
	bonus[0] = bonus[1] = bonus[2] = 0;
}

int typeGame(int lev, int p_m, int type, int change)
{
	switch (type)
	{
	case 0: //Mode of the game with levels
		{
			initMap();
			
			if (change){ //If the player pass the next level, move to the next level.
				lev++; 
				mappingLevel(lev);}
			else
				mappingLevel(lev);

			return lev;
			break;
		}

	case 1: //Practice mode
		{
			initMap();
			modePract(p_m); //Initialize the mode of the practice

			return 0;
			break;
		}
	}

	return 0;

}

void changeLevel(int lev_act)
{
	//Checks if the user defeat the current level depending of the during time.
	switch(lev_act)
	{
	case 0:
	case 1:
		if (time_l > time_level[lev_act]){
			move_level = 1;}
		break;
	case 2:
	case 3:
		if (time_l > time_level[lev_act]){
			move_level = 1;}
		break;
	case 4:
		if(time_l > time_level[lev_act]){
			move_level = 1;}
		break;
	case 5:
		if (time_l > time_level[lev_act]){
			move_level = 1;}
		break;
	}
}

void drawScreen()
{
	//Draw everything need for play the game
	clearScreen();

	acquire_bitmap(score_buffer);
	drawInfo(score, lev_act, time_l, rows_del, myfont, speed-9);
	
	acquire_bitmap(map_buffer);
	drawBoard();
	drawPiece(current, 0);

	acquire_bitmap(next_buffer);
	drawPiece(next, 1);

	blit (map_buffer, screen, 0, 0, 100, 40, 200, 400);
	blit (score_buffer, screen, 0, 0, 350, 40, 180, 160);
	blit (next_buffer, screen, 0, 0, 350, 210, 80, 80);

	release_bitmap(map_buffer);
	release_bitmap(score_buffer);
	release_bitmap(next_buffer);

}

void load_highscore(const char *filename)
{
    FILE *score_file;
	fopen_s(&score_file, filename, "a+");

    for (int i = 0; i < 10; ++i)
    {
       int ret = fscanf_s(score_file, "%s %d %d\n", highscore[i].name, 4,  &highscore[i].score, &highscore[i].level);

        if( ret != 3 || ret == EOF ) 
        {
           //Handle an error here. 
        }
	}

	fscanf_s(score_file, "\n");

    fclose(score_file);
    return;
}

void save_highscore(const char *filename)
{
	FILE *score_file;
	fopen_s(&score_file, filename, "r+");

    for (int i = 0; i < 10; ++i)
    {
        int ret = fprintf_s(score_file, "%s %d %d\n", highscore[i].name, highscore[i].score, highscore[i].level);

        if( ret != 3 || ret == EOF ) 
        {
           //Handle an error here.
        }
	}

	fprintf_s(score_file, "\n");

    fclose(score_file);
    return;
}

void add_highscore(int score, int level)
{
	int temp;
	char temp_n[4];

	if (score < highscore[0].score)
	{
		game_over[2].flags =  game_over[3].flags = game_over[4].flags = D_HIDDEN; //Hide the buttons if the user doesn't beat any score
	}

	else
	{
		//Checks in what position the new score has to be
		for (int j = 0; j < 4; j++){
			highscore[0].name[j] = the_string[j];}				
		
		highscore[0].score = score;
		highscore[0].level = level;

		for (int i = 0; i < 10 - 1; i++)
		{
			for (int j = i+1; j < 10; j++)
			{
				if (highscore[i].score > highscore[j].score)
				{
					 	  	 	
				temp = highscore[i].score;
				highscore[i].score = highscore[j].score;
				highscore[j].score = temp;

				temp = highscore[i].level;
				highscore[i].level = highscore[j].level;
				highscore[j].level = temp;

				for (int k = 0; k < 4; k++){
					temp_n[k] = highscore[i].name[k];}
				for (int k = 0; k < 4; k++){
					highscore[i].name[k] = highscore[j].name[k];}
				for (int k = 0; k < 4; k++){
					highscore[j].name[k] = temp_n[k];}

				}
			}
		}
	}
}







