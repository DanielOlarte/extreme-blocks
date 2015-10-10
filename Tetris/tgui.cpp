
/*	  EXTREME BLOCKS - Copyright (C) 2010 by Oscar D. Olarte  *
 
 *    (c) RPR-GDevelopment - 2010                             *
 *    Written by Oscar Olarte                                 *

 *    This source code is released under the The GNU          *
 *    General Public License (GPL). Please refer to the       *
 *    document license.txt in the source directory or         *
 *    http://www.gnu.org for license information.			  */

#include "ftetris.h"
#include "tgui.h"

void maintainDialog(DIALOG *d, int cont)
{
	//Create the dialog and keep updating until the user decides
	player[cont] = init_dialog(d, -1);
	while(update_dialog(player[cont]))
	{}
	shutdown_dialog(player[cont]);
}

int my_button_proc(int msg, DIALOG *d, int c)
{
	//My personal button

	if ((d->flags & D_GOTFOCUS) && (!(d->flags & D_SELECTED) || !(d->flags & D_EXIT)))
	{
		if (msg == MSG_DRAW || msg == MSG_WANTFOCUS)
		{
			if(d->d1 == 20)
			{
				msg = MSG_IDLE;
			}
		}
	}

   int ret = d_button_proc(msg, d, c);


   if (ret == D_CLOSE && d->dp3)
      return ((int (*)(void))d->dp3)();
   return ret;
}

int dselec_proc(int msg, DIALOG *d, int c)
{
	//My personal button of selection
	  int ret = d_radio_proc(msg, d, c);

	  if (d->flags & D_SELECTED && d->dp3)
		  return ((int (*)(void))d->dp3)();

	  return ret;
}

int mydraw_proc(int msg, DIALOG *d, int c)
{
	//My own drawing function were I decide many stuff to draw in differents moments of the game
   BITMAP *gui_bmp;
   FONT *f_temp; //For save a allegro font

   int state1, state2, g, draw;
   int s = 10;
   ASSERT(d);

   char str[65];

   switch(d->d1)
   {
   case 1:{
		   uszprintf(str, sizeof(str), "BOARD FEATURES: ");
		   draw = 1;
		   break;}
   case 2:{
		   uszprintf(str, sizeof(str), "SPEED: ");
		   draw = 1;
		   break;}
   case 3:{
		   uszprintf(str, sizeof(str), "%d", prac_mode[6].d2);
		   draw = 1;
		   break;}
   case 8:{
	   	   uszprintf(str, sizeof(str), "Volume Music: ");
		   draw = 1;
		   break;}
   case 9:{
	   	   uszprintf(str, sizeof(str), "Volume Effects: ");
		   draw = 1;
		   break;}
   }

   gui_bmp = gui_get_screen();

   switch (msg) 
   {
      case MSG_DRAW:
	  {
	    g = 1;
	    state1 = d->bg;
	    state2 = (d->flags & D_DISABLED) ? gui_mg_color : d->fg;

		f_temp = font;
		font = myfont;

		if(d->d1 == 5)
		{
			uszprintf(str, sizeof(str), "HIGHSCORES");
			gui_textout_ex(gui_bmp, str, 326, 58.5 -text_height(font)/2, state1, -1, TRUE);

			for (int i = 0; i < 10; i++)
			{
				uszprintf(str, sizeof(str), " %d. ", s);
				s--;
				gui_textout_ex(gui_bmp, str, d->x + d->w/2 + g - 130, d->y +g - 30*(i), state1, -1, TRUE);
				uszprintf(str, sizeof(str), " %s ", highscore[i].name);
				gui_textout_ex(gui_bmp, str, d->x + d->w/2 + g - 65, d->y +g - 30*(i), state1, -1, TRUE);
				uszprintf(str, sizeof(str), " %d ", highscore[i].score);
				gui_textout_ex(gui_bmp, str, d->x + d->w/2 + g + 30, d->y +g - 30*(i), state1, -1, TRUE);
				uszprintf(str, sizeof(str), " %d ", highscore[i].level);
				gui_textout_ex(gui_bmp, str, d->x + d->w/2 + g + 115, d->y +g - 30*(i), state1, -1, TRUE);
			}
		}

		else if (d->d1 == 7)
		{
			uszprintf(str, sizeof(str), " BONUS ");
			gui_textout_ex(gui_bmp, str, d->x + d->w/2 + g, d->y +g + 45, d->fg, -1, TRUE);
			uszprintf(str, sizeof(str), " Single Line: ");
			gui_textout_ex(gui_bmp, str, d->x + d->w/2 + g - 30, d->y +g + 100, d->fg, -1, TRUE);
			uszprintf(str, sizeof(str), " Double And Triple Lines: ");
			gui_textout_ex(gui_bmp, str, d->x + d->w/2 + g - 30, d->y +g + 150, d->fg, -1, TRUE);
			uszprintf(str, sizeof(str), " Quadruple Lines: ");
			gui_textout_ex(gui_bmp, str, d->x + d->w/2 + g - 30, d->y +g + 200, d->fg, -1, TRUE);
			uszprintf(str, sizeof(str), " %d ", bonus[0]);
			gui_textout_ex(gui_bmp, str, d->x + d->w/2 + g + 50, d->y +g + 100, d->fg, -1, TRUE);
			uszprintf(str, sizeof(str), " %d ", bonus[1]);
			gui_textout_ex(gui_bmp, str, d->x + d->w/2 + g + 110, d->y +g + 150, d->fg, -1, TRUE);
			uszprintf(str, sizeof(str), " %d ", bonus[2]);
			gui_textout_ex(gui_bmp, str, d->x + d->w/2 + g + 75, d->y +g + 200, d->fg, -1, TRUE);
			uszprintf(str, sizeof(str), " Score:  %d", score);
			gui_textout_ex(gui_bmp, str, d->x + d->w/2 + g - 10, d->y +g + 250, d->fg, -1, TRUE);
		}

		else if(d->d1 == 10)
		{
			uszprintf(str, sizeof(str), "SELECT A LEVEL ");
			gui_textout_ex(gui_bmp, str, d->x+d->w/2+g, d->y+d->h/2-text_height(font)/2+g, d->fg, -1, TRUE);
		}

		else if(d->d1 == 11)
		{
			uszprintf(str, sizeof(str), "PRACTICE MODE ");
			gui_textout_ex(gui_bmp, str, d->x+d->w/2+g, d->y+d->h/2-text_height(font)/2+g, d->fg, -1, TRUE);
		}

		else if(d->d1 == 12)
		{
			uszprintf(str, sizeof(str), "OPTIONS ");
			gui_textout_ex(gui_bmp, str, d->x+d->w/2+g, d->y+d->h/2-text_height(font)/2+g, d->fg, -1, TRUE);
		}

		else if(d->d1 == 6)
		{
			font = f_temp;
			uszprintf(str, sizeof(str), "Enter Your Name: ");
			gui_textout_ex(gui_bmp, str, d->x+d->w/2+g, d->y+d->h/2-text_height(font)/2+g, d->fg, -1, TRUE);}

		else if(d->d1 == 13 && d->d2 == 1)
		{
			uszprintf(str, sizeof(str), "CREDITS");
			gui_textout_ex(gui_bmp, str, 326, 58.5 -text_height(font)/2, state1, -1, TRUE);
			uszprintf(str, sizeof(str), "Programming And Design - Oscar Olarte");
			gui_textout_ex(gui_bmp, str, 326, 100 - text_height(font)/2, state1, -1, TRUE);
			uszprintf(str, sizeof(str), "Logo Of The Game And Other Features - David Vargas");
			gui_textout_ex(gui_bmp, str, 326, 140 -text_height(font)/2, state1, -1, TRUE);
			uszprintf(str, sizeof(str), "Pinball Spring, Half Bit - Kevin MacLeod (incompetech.com)");
			gui_textout_ex(gui_bmp, str, 326, 180 -text_height(font)/2, state1, -1, TRUE);
			uszprintf(str, sizeof(str), "Images For The Blocks - Solink");
			gui_textout_ex(gui_bmp, str, 326, 220 -text_height(font)/2, state1, -1, TRUE);
			uszprintf(str, sizeof(str), "Sound Effects - FreeSoundEffects.com");
			gui_textout_ex(gui_bmp, str, 326, 260 -text_height(font)/2, state1, -1, TRUE);
			uszprintf(str, sizeof(str), "Font Texture Road - Galdino Otten");
			gui_textout_ex(gui_bmp, str, 326, 300 -text_height(font)/2, state1, -1, TRUE);
			uszprintf(str, sizeof(str), "Thanks to GameDev community for the help");
			gui_textout_ex(gui_bmp, str, 326, 340 -text_height(font)/2, state1, -1, TRUE);
			uszprintf(str, sizeof(str), "Thanks to Allegro community for the help");
			gui_textout_ex(gui_bmp, str, 326, 380 -text_height(font)/2, state1, -1, TRUE);
		}

		else if(d->d1 == 14 && d->d2 == 2)
		{
			uszprintf(str, sizeof(str), "KEYBOARD OPTIONS");
			gui_textout_ex(gui_bmp, str, 326, 58.5 -text_height(font)/2, state1, -1, TRUE);
			uszprintf(str, sizeof(str), "Extreme Blocks is a simple Tetris clon with the purpose of");
			gui_textout_ex(gui_bmp, str, 326, 100 - text_height(font)/2, state1, -1, TRUE);
			uszprintf(str, sizeof(str), "teache me how Allegro works in all possible ways.");
			gui_textout_ex(gui_bmp, str, 326, 120 -text_height(font)/2, state1, -1, TRUE);
			uszprintf(str, sizeof(str), "Those are the keys that you need for play this game:");
			gui_textout_ex(gui_bmp, str, 326, 155 -text_height(font)/2, state1, -1, TRUE);
			uszprintf(str, sizeof(str), "Left Arrow - Right Arrow:  Move the piece to each side");
			gui_textout_ex(gui_bmp, str, 326, 200 -text_height(font)/2, state1, -1, TRUE);
			uszprintf(str, sizeof(str), "Down Arrow:  Make the piece fall more faster");
			gui_textout_ex(gui_bmp, str, 326, 230 -text_height(font)/2, state1, -1, TRUE);
			uszprintf(str, sizeof(str), "Up Arrow:  Rotate the piece to the right");
			gui_textout_ex(gui_bmp, str, 326, 260 -text_height(font)/2, state1, -1, TRUE);
			uszprintf(str, sizeof(str), "T - G:  Up and down respectively the volume of music");
			gui_textout_ex(gui_bmp, str, 326, 290 -text_height(font)/2, state1, -1, TRUE);
			uszprintf(str, sizeof(str), "Y - H:  Up and down respectively the volume of sound effects");
			gui_textout_ex(gui_bmp, str, 326, 320 -text_height(font)/2, state1, -1, TRUE);
			uszprintf(str, sizeof(str), "P - Pause The Game   M - Main Menu ");
			gui_textout_ex(gui_bmp, str, 326, 350 -text_height(font)/2, state1, -1, TRUE);
		}
	
		else if (draw == 1){
			font = f_temp;
			gui_textout_ex(gui_bmp, str, d->x+d->w/2+g, d->y+d->h/2-text_height(font)/2+g, state1, -1, TRUE);}

		font = f_temp;

		break;
	  }
  }

   return D_O_K;
}

char *listbox_getter(int index, int *list_size)
{
	//The list with the name of each level
   static char *strings[] =
   {
      "   Level 0 - Zero",  "   Level 1 - One",   "   Level 2 - Two",   
	  "   Level 3 - Three", "   Level 4 - Four",  "   Level 5 - Five"
   };

   if (index < 0) {
      *list_size = 6;
      return NULL;
   }
   else {
      return strings[index]; 
   }
}

int drawing(void *)
{
	return D_REDRAW;
}

int ret_mm(void)
{
	//For return to main menu or keep playing
	t_time = time_l;
	t_speed = speed;
	time_l = -2000;

	if (alert("You Really Wanna Quit The Actual Game?", NULL, NULL, "&Yes", "&No", 'y', 'n') == 1)
	{
		quitgame = 1;
		change_dialog = TOMM;
		time_l = keyboard_counter = ticks = 0;

		stop_sample(sound[1]);
		play_sample(sound[0], volume[0], 128, 1000, TRUE);

		return D_CLOSE;
	}

	else{
		time_l = t_time;
		speed = t_speed;

		return D_O_K;}
}


int quit(void)
{
	//For quit the game
	if (alert("You Really Wanna Quit?", NULL, NULL, "&Yes", "&No", 'y', 'n') == 1){
		quitgame = 1;
	  return D_CLOSE;}

	else{
		return D_O_K;}
}

int p_mode(void)
{
	change_dialog = MM2PM;
	return D_CLOSE;
}

int opt(void)
{
	change_dialog = MM2OP;
	return D_CLOSE;
}

int back(void)
{
	change_dialog = TOMM;
	return D_CLOSE;
}

int new_g(void)
{
	change_dialog = MM2NG;
	return D_CLOSE;
}

int pause(void)
{
	//Pause the game with all the variables
	stop = 1;
	t_time = time_l;
	t_speed = speed;
	time_l = -2000;

	if (stop == 1)
	{
		alert(NULL, "PAUSE IN THE GAME", NULL, "Continue", NULL, 'p', 0);
		stop = 0;
	}
	
	speed = t_speed;
	time_l = t_time;
	keyboard_counter = ticks = fps = fpscount = 0;

	return D_O_K;
}

int no_blocks(void)
{
	pr_mod = 1;
	return D_O_K;
}

int ran_blocks(void)
{
	pr_mod = 2;	
	return D_O_K;
}

int s_level(void)
{
	//Select the level in the selection level 
	lev_act = sel_level[3].d1;
	return D_CLOSE;
}

int hscore(void)
{
	change_dialog = TOHS;
	return D_CLOSE;
}

int credits(void)
{
	change_dialog = TOCK;
	cred_key[2].d2 = 1;
	return D_CLOSE;
}

int keyboard(void)
{
	change_dialog = TOCK;
	cred_key[3].d2 = 2;
	return D_CLOSE;
}





