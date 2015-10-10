
/*	  EXTREME BLOCKS - Copyright (C) 2010 by Oscar D. Olarte  *
 
 *    (c) RPR-GDevelopment - 2010                             *
 *    Written by Oscar Olarte                                 *

 *    This source code is released under the The GNU          *
 *    General Public License (GPL). Please refer to the       *
 *    document license.txt in the source directory or         *
 *    http://www.gnu.org for license information.			  */

#include "ftetris.h"
#include "tgui.h"

int d_newgame()
{
	maintainDialog(sel_level, 0);

	if (change_dialog == TOMM){ //If the user press the back button return to main menu
		quitgame = 0;
		return TOMM;}

	//////*Initialize all the features fot the gameplay*//////
	newGame(0, NULL, 0);
	lev_act = typeGame(lev_act, 0, 0, 0);
	changeBG(new_game, lev_act, 0);
	//////////////////////////////////////////////////////////

	score = quitgame = move_level = keyboard_counter = ticks = 0;

	stop_sample(sound[0]);
	play_sample(sound[1], volume[0], 128, 1000, TRUE);

	player[0] = init_dialog(new_game, -1);	
				
	while (update_dialog(player[0]) && !quitgame)
	{
		in_game = 1; //The user is playing

		if (move_level == 1) //If the user pass the level, move to the next level or finis the game
		{
			if (lev_act == 5)
			{
				change_dialog = TOHS;
				move_level = 0;
				quitgame = 1;

				break;
			}
						
			else
			{
				bonusPoints(); //Add some bonus points

				stop_sample(sound[1]);
				game_over[1].dp = new_game[1].dp;
							
				play_sample(sound[4], 255, 128, 1000, TRUE);
				maintainDialog(game_over, 0);
				stop_sample(sound[4]);

				//Initialize again the game with the next level
				newGame(lev_act, NULL, 0);
				lev_act = typeGame(lev_act, NULL, 0, 1);
				changeBG(new_game, lev_act, 0);

				play_sample(sound[1], volume[0], 128, 1000, TRUE);
							
				player[0] = init_dialog(new_game, -1);	
				move_level = rows_del = keyboard_counter = ticks = 0;
			}
		}

		while (!move_level && in_game && !quitgame) //Logic of the game
		{
			update_dialog(player[0]);
			drawScreen();
			quitgame = playGame();
		}

		if(quitgame == 1 && change_dialog != TOMM){ //If the user lose go to the game over screen
			change_dialog = TOHS;}
	}

	if (change_dialog == TOMM){ //Return to main menu if the user press that button
		quitgame = 0;
		return TOMM;}
	
	stop_sample(sound[1]);
	
	if (change_dialog == TOHS)
	{
		bonusPoints(); //Add some bonus points
		if (score > highscore[0].score) //When the user entry to highscores
		{
			game_over[3].flags = game_over[4].flags = game_over[5].flags = 0; //Allow to write his name
			game_over[1].dp = new_game[1].dp;

			play_sample(sound[4], 255, 128, 1000, TRUE);
			maintainDialog(game_over, 0);
			stop_sample(sound[4]);
			entry = 1;
		}

		if (score < highscore[0].score) //When the user can't entry to highscores
		{
			game_over[1].dp = new_game[1].dp;

			play_sample(sound[5], 255, 128, 1000, TRUE);
			maintainDialog(game_over, 0);
			stop_sample(sound[5]);
			entry = 0;
		}
					
		if (entry == 1)
		{
			add_highscore(score, lev_act--); //Save the highscore
			save_highscore("HSTable.rpr");//Save the highscore table in the file
		}

		quitgame = 0;
	}

	return TOHS;
}


int d_pmode()
{
	player[0] = init_dialog(prac_mode, -1); //Initialize the screen of practice mode
	pr_mod = 0;

	while(pr_mod == 0) 
	{
		while(update_dialog(player[0]))
		{}
		
		if (change_dialog == TOMM){
		break;}
					
		if (pr_mod == 0) //Conditional for select a board feature for the game
		{
			alert("You Must Select A Board Feature", NULL, NULL, "OK", NULL, NULL, NULL);
		}
	}
	
	if (change_dialog == TOMM){ //If the user press the back button, return to main menu
		shutdown_dialog(player[0]);
		return TOMM;}
	
	shutdown_dialog(player[0]);

	stop_sample(sound[0]);
	play_sample(sound[1], volume[0], 128, 1000, TRUE);
				
	player[0] = init_dialog(new_game, -1);
	
	//Initialize all the components of the level
	newGame(0, 0, 0);
	changeBG(new_game, 0, 1);
	speed = inv_s[prac_mode[6].d2];
	practice_mode = pr_mod-1;	 //Initialize the board depending on the board feature
	modePract(practice_mode);
	time_l = keyboard_counter = ticks = score = 0;
	lev_act = 6; //Indicates that it's in practice mode

	while (update_dialog(player[0]) && !quitgame)
	{
		while (!quitgame)
		{
			scare_mouse();
			update_dialog(player[0]);
			unscare_mouse();
			drawScreen();
			quitgame = playGame();
			
		}
	}

	stop_sample(sound[1]);
	shutdown_dialog(player[0]);
	play_sample(sound[0], volume[0], 128, 1000, TRUE);

	quitgame = 0;

	return MM2PM; //Return to practice mode
}

int d_options()
{
	player[0] = init_dialog(options, -1); //Init the dialog of options
			
	while(update_dialog(player[0]))
	{
		volume[0] = options[4].d2;
		volume[1] = options[6].d2;
		//Adjust the volume of all samples that the game uses
		adjust_sample(sound[0], volume[0], 128, 1000, TRUE);
		adjust_sample(sound[1], volume[0], 128, 1000, TRUE);
	    adjust_sample(sound[2], volume[1], 128, 1000, TRUE);
		adjust_sample(sound[3], volume[1], 128, 1000, TRUE);
	}

	shutdown_dialog(player[0]);

	if(change_dialog == TOCK) //Change dialog to Credits or Keyboard Options
	{
		maintainDialog(cred_key, 0);
		cred_key[2].d2 = cred_key[3].d2 = 0;
		change_dialog = MM2OP;
		return MM2OP;
	}
				
	return TOMM;
}

int d_hs()
{
	stop_sample(sound[0]);
	play_sample(sound[1], volume[0], 128, 1000, TRUE);

	maintainDialog(show_hs, 0);

	stop_sample(sound[1]);
	play_sample(sound[0], volume[0], 128, 1000, TRUE);

	return TOMM;
}

