
/*	  EXTREME BLOCKS - Copyright (C) 2010 by Oscar D. Olarte  *
 
 *    (c) RPR-GDevelopment - 2010                             *
 *    Written by Oscar Olarte                                 *

 *    This source code is released under the The GNU          *
 *    General Public License (GPL). Please refer to the       *
 *    document license.txt in the source directory or         *
 *    http://www.gnu.org for license information.			  */

#include "ftetris.h"
#include "tgui.h"
#include "level.h"
#include "sounds.h"
#include "bgblocks.h"

BITMAP *map_buffer, *score_buffer, *next_buffer, *temp[8];
BLOCK blocks[7][4][4][4], next_block[4][4], current_block[4][4];

FONT *myfont;
DATAFILE *file1, *file2, *file3;
SAMPLE *sound[6];

int map[BOARD_WIDTH][BOARD_HEIGHT];
int speed, t_speed, stop, inv_s[41];
int score, rows_del, bonus[3];
int quitgame, move_level, lev_act, point_lev[7], practice_mode, time_level[7], pr_mod;
int change_dialog, in_game, entry;
int volume[2];

volatile int ticks, keyboard_counter, fps, fpscount, time_l, t_time;

char the_string[] = "ABC";

class cPiece current;
class cPiece next;

DIALOG_PLAYER *player[1];

DIALOG main_menu[] =
{
	/* (dialog proc)     (x)   (y)   (w)   (h)   (fg)    (bg)  (key)    (flags)   (d1)  (d2)          (dp)               (dp2)   (dp3) */
	{ d_clear_proc,      0,      0,    0,   0,     0,       0,    0,         0,     0,   0,           NULL,               NULL,   NULL  },
	{ d_bitmap_proc,     0,      0,  640, 480,     0,       0,    0,         0,     0,   0,           NULL,               NULL,   NULL  },
	{ my_button_proc,    242,  200,  150,  30,     0,       0,  's',    D_EXIT,     0,   0,  (void *)"Start New Game",    NULL,  (void *)new_g },
	{ my_button_proc,    259,  250,  120,  30,     0,       0,  'p',    D_EXIT,     0,   0,  (void *)"Practice Mode",     NULL,  (void *)p_mode },
	{ my_button_proc,    275,  300,  90,   30,     0,       0,  'o',    D_EXIT,     0,   0,  (void *)"Options",           NULL,  (void *)opt },
	{ my_button_proc,    258,  350,  120,  30,     0,       0,  'h',    D_EXIT,     0,   0,  (void *)"Highscores",        NULL,  (void *)hscore },
	{ my_button_proc,    275,  400,  90,   30,     0,       0,  'q',    D_EXIT,     0,   0,  (void *)"Quit",              NULL,  (void *)quit  },
	{ NULL,              0,    0,    0,    0,      0,       0,    0,         0,     0,   0,           NULL,               NULL,   NULL  }
};

DIALOG options[] =
{
	/* (dialog proc)     (x)   (y)   (w)   (h)   (fg)    (bg)  (key)    (flags)   (d1)  (d2)          (dp)               (dp2)   (dp3) */
	{ d_clear_proc,      0,      0,    0,    0,    0,       0,    0,         0,     0,   0,           NULL,               NULL,   NULL  },
	{ d_bitmap_proc,     0,      0,  640,  480,    0,       0,    0,         0,     0,   0,           NULL,               NULL,   NULL  },
	{ my_button_proc,    247,  190,  140,   30,    0,       0,    0,    D_EXIT,     0,   0,  (void *)"Keyboard Controls", NULL,  (void *)keyboard },
	{ my_button_proc,    275,  230,  90,    30,    0,       0,    0,         0,     0,   0,  (void *)"Sound",             NULL,   NULL },
	{ d_slider_proc,     226,  280,  180,   15,    0,       0,    0,         0,   255,  127,           NULL,      (void *)drawing, NULL},
	{ mydraw_proc,       150,  280,  30,    15,    0,       0,    0,         0,     8,   0,           NULL,				  NULL,   NULL  },
	{ d_slider_proc,     226,  315,  180,   15,    0,       0,    0,         0,   255,  127,           NULL,      (void *)drawing, NULL},
	{ mydraw_proc,       150,  315,  30,    15,    0,       0,    0,         0,     9,   0,           NULL,				  NULL,   NULL  },
	{ my_button_proc,    275,  350,  90,    30,    0,       0,    0,    D_EXIT,     0,   0,  (void *)"Credits",           NULL,  (void *)credits },
	{ my_button_proc,    275,  400,  90,    30,    0,       0,    0,    D_EXIT,     0,   0,  (void *)"Back",              NULL,  (void *)back },
	{ mydraw_proc,       310,  150,  30,    15,    0,       0,    0,         0,    12,   0,           NULL,			      NULL,   NULL  },
	{ NULL,              0,    0,     0,     0,    0,       0,    0,         0,     0,   0,           NULL,               NULL,   NULL }
};

DIALOG prac_mode[] =
{
	/* (dialog proc)     (x)   (y)   (w)   (h)   (fg)    (bg)  (key)    (flags)   (d1)  (d2)          (dp)               (dp2)   (dp3) */
	{ d_clear_proc,      0,      0,    0,   0,     0,       0,    0,         0,     0,   0,           NULL,               NULL,   NULL  },
	{ d_bitmap_proc,     0,      0,  640, 480,     0,       0,    0,         0,     0,   0,           NULL,               NULL,   NULL  },
	{ mydraw_proc,       180,  220,  80,   15,     0,       0,    0,         0,     1,   0,           NULL,				  NULL,   NULL  },
	{ dselec_proc,       280,  220,  160,  19,     0,       0,    0,         0,     0,   1,   (void *)"No Blocks",        NULL,  (void *)no_blocks },
    { dselec_proc,       280,  239,  160,  19,     0,       0,    0,         0,     0,   1,   (void *)"With Random Blocks",NULL, (void *)ran_blocks },
	{ mydraw_proc,       240,  280,  30,   15,     0,       0,    0,         0,     2,   0,           NULL,				  NULL,   NULL  },
	{ d_slider_proc,     280,  280,  110,  15,     0,       0,    0,         0,    40,   0,           NULL,      (void *)drawing, NULL  },
	{ mydraw_proc,       390,  280,  30,   15,     0,       0,    0,         0,     3,   0,           NULL,				  NULL,   NULL  },
	{ my_button_proc,    242,  350,  150,  30,     0,       0,    0,    D_EXIT,     0,   0,   (void *)"Start Game",       NULL,   NULL  },
	{ my_button_proc,    275,  400,  90,   30,     0,       0,    0,    D_EXIT,     0,   0,   (void *)"Back",             NULL,  (void *)back },
	{ mydraw_proc,       310,  170,  30,   15,     0,       0,    0,         0,    11,   0,           NULL,				  NULL,   NULL  },
	{ NULL,              0,    0,    0,    0,    0,         0,    0,         0,     0,   0,           NULL,               NULL,   NULL  }
};

DIALOG new_game[] =
{
	/* (dialog proc)     (x)   (y)   (w)   (h)   (fg)    (bg)  (key)    (flags)   (d1)  (d2)          (dp)               (dp2)   (dp3) */
	{ d_clear_proc,      0,      0,    0,   0,     0,       0,    0,         0,     0,   0,           NULL,               NULL,   NULL  },
	{ d_bitmap_proc,     0,      0, 640,  480,     0,       0,    0,         0,     0,   0,           NULL,               NULL,   NULL  },
	{ my_button_proc,    350,  410,  90,   30,     0,       0,  'p',    D_EXIT,    20,   0,  (void *)"Pause",             NULL,  (void *)pause },
	{ my_button_proc,    450,  410,  90,   30,     0,       0,  'm',    D_EXIT,    20,   0,  (void *)"Main Menu",         NULL,  (void *)ret_mm},
	{ NULL,              0,    0,    0,    0,    0,         0,    0,         0,     0,   0,           NULL,               NULL,   NULL  }
};

DIALOG sel_level[] =
{
	/* (dialog proc)     (x)   (y)   (w)   (h)   (fg)    (bg)  (key)    (flags)   (d1)  (d2)          (dp)               (dp2)   (dp3) */
	{ d_clear_proc,      0,      0,   0,   0,      0,       0,    0,         0,     0,   0,           NULL,               NULL,   NULL  },
	{ d_bitmap_proc,     0,      0,  640, 480,     0,       0,    0,         0,     0,   0,           NULL,               NULL,   NULL  },
	{ my_button_proc,    242,  220,  150,  30,     0,       0,    0,    D_EXIT,     0,   0,  (void *)"Start Game",        NULL,  (void *)s_level },
	{ d_text_list_proc,  237,  265,  160, 120,     0,       0,    0,         0,     0,   0,  (void *)listbox_getter,     NULL,   NULL  },
	{ my_button_proc,    275,  400,  90,   30,     0,       0,    0,    D_EXIT,     0,   0,  (void *)"Back",              NULL,  (void *)back },
	{ mydraw_proc,       310,  170,  30,   15,     0,       0,    0,         0,     10,  0,           NULL,				  NULL,   NULL  },
	{ NULL,              0,    0,    0,    0,      0,       0,    0,         0,     0,   0,           NULL,               NULL,   NULL  }
};

DIALOG show_hs[] =
{
	/* (dialog proc)     (x)   (y)   (w)   (h)   (fg)    (bg)  (key)    (flags)   (d1)  (d2)          (dp)               (dp2)   (dp3) */
	{ d_clear_proc,      0,      0,   0,   0,      0,       0,    0,         0,     0,   0,           NULL,               NULL,   NULL  },
	{ d_bitmap_proc,     0,      0, 640,  480,     0,       0,    0,         0,     0,   0,           NULL,               NULL,   NULL  },
	{ mydraw_proc,       305,  360,  30,   15,     0,       0,    0,         0,     5,   0,           NULL,				  NULL,   NULL  },
	{ my_button_proc,    275,  400,  90,   30,     0,       0,    0,    D_EXIT,     0,   0,   (void *)"Back",             NULL,  (void *)back },
	{ NULL,              0,    0,    0,    0,      0,       0,    0,         0,     0,   0,           NULL,               NULL,   NULL  }
};


DIALOG game_over[] =
{
	/* (dialog proc)     (x)   (y)   (w)   (h)   (fg)    (bg)  (key)    (flags)   (d1)  (d2)          (dp)               (dp2)   (dp3) */
	{ d_clear_proc,      0,      0,    0,   0,     0,       0,    0,         0,     0,   0,           NULL,               NULL,   NULL  },
	{ d_bitmap_proc,     0,      0, 640,  480,     0,       0,    0,         0,     0,   0,           NULL,               NULL,   NULL  },
	{ mydraw_proc,       300,  60,   30,   15,     0,       0,    0,         0,     7,   0,           NULL,				  NULL,   NULL  },
	{ d_shadow_box_proc, 230,  347, 180,   40,     0,       0,    0,  D_HIDDEN,     0,   0,           NULL,				  NULL,   NULL  },
	{ mydraw_proc,       285,  357,  30,   15,     0,       0,    0,  D_HIDDEN,     6,   0,           NULL,				  NULL,   NULL  },
	{ d_edit_proc,       370,  357,  35,   20,     0,       0,    0,  D_HIDDEN,   LEN,   0,       the_string,			  NULL,   NULL  },
	{ my_button_proc,    275,  400,  90,   30,     0,       0,    0,    D_EXIT,     0,   0,   (void *)"Continue",         NULL,  (void *)hscore },
	{ NULL,              0,    0,    0,    0,    0,         0,    0,         0,     0,   0,           NULL,               NULL,   NULL  }
};

DIALOG cred_key[] =
{
	/* (dialog proc)     (x)   (y)   (w)   (h)   (fg)    (bg)  (key)    (flags)   (d1)  (d2)          (dp)               (dp2)   (dp3) */
	{ d_clear_proc,      0,      0,    0,   0,     0,       0,    0,         0,     0,   0,           NULL,               NULL,   NULL  },
	{ d_bitmap_proc,     0,      0,  640, 480,     0,       0,    0,         0,     0,   0,           NULL,               NULL,   NULL  },
	{ mydraw_proc,       305,  360,  30,   15,     0,       0,    0,         0,     13,   0,           NULL,				  NULL,   NULL  },
	{ mydraw_proc,       305,  360,  30,   15,     0,       0,    0,         0,     14,   0,           NULL,				  NULL,   NULL  },
	{ my_button_proc,    275,  400,  90,   30,     0,       0,    0,    D_EXIT,     0,   0,   (void *)"Back",             NULL,  (void *)back },

	{ NULL,              0,    0,    0,    0,    0,         0,    0,         0,     0,   0,           NULL,               NULL,   NULL  }
};



//A random highscore table
HS highscore[10] = 
{
  { "HER",      5000,   0},
  { "DAO",     10000,   1},
  { "FEL",     15000,   1},
  { "ODO",     20000,   2},
  { "POP",     25000,   2},
  { "DS2",     30000,   3},
  { "ME2",     35000,   3},
  { "AC2",     40000,   4},
  { "OSC",	   45000,   4},
  { "RPR",     50000,   5},
};

cPiece::cPiece()
{
	pos_x = 4; //Initial positions
	pos_y = 0;
}

void ticker(void)
{
	ticks++;
}
END_OF_FUNCTION(ticker)

void keyboard_timer()
{
	keyboard_counter++;

} END_OF_FUNCTION(keyboard_timer)

void fpscounter()    // frames per second counter
{
   fps = fpscount;   // fps = counted fps
   fpscount = 0;     // reset counter
   time_l++;

   if (time_l%20 == 0)
   {
	   speed = speed - 2;
	   if (speed < 9)
	   {
		   speed = 9;
	   }
   }

   if (in_game == 0)
   {}
   else{
	   changeLevel(lev_act);}

} END_OF_FUNCTION(fpscounter);

void main(void)
{
    allegro_init(); 
    install_keyboard(); 
	install_timer();
	install_mouse();

	LOCK_VARIABLE(ticks);
	LOCK_FUNCTION(ticker);

	LOCK_VARIABLE(keyboard_counter);
    LOCK_FUNCTION(keyboard_timer);

	LOCK_VARIABLE(fps);
	LOCK_VARIABLE(fpscount);
	LOCK_VARIABLE(time_l);
	LOCK_VARIABLE(t_time);
	LOCK_FUNCTION(fpscounter);

	install_int_ex(fpscounter, SECS_TO_TIMER(1));
	install_int_ex(keyboard_timer, BPS_TO_TIMER(10));
	install_int_ex(ticker, BPS_TO_TIMER(60));


	setupscreen();

	/////*Setup the colors of the all dialogs*/////

	gui_fg_color = makecol(0, 0, 0); 
	gui_mg_color = makecol(128, 128, 128);
	gui_bg_color = makecol(255, 255,255); 

	set_dialog_color(new_game, gui_fg_color, gui_bg_color); 
	set_dialog_color(main_menu, gui_fg_color, gui_bg_color);  
	set_dialog_color(options, gui_fg_color, gui_bg_color);
	set_dialog_color(show_hs, gui_fg_color, gui_bg_color);  
	set_dialog_color(prac_mode, gui_fg_color, gui_bg_color);
	set_dialog_color(sel_level, gui_fg_color, gui_bg_color);  
	set_dialog_color(game_over, gui_fg_color, gui_bg_color);
	set_dialog_color(cred_key, gui_fg_color, gui_bg_color); 

	//////////////////////////////////////////////////////

	in_game = 0; //Indicates if the user is playing the game or not

	//Initialize the bitmaps for each dialog
	main_menu[1].dp =  options[1].dp = prac_mode[1].dp =  sel_level[1].dp = (BITMAP *)file2[MAINMENU].dat;
	cred_key[1].dp = show_hs[1].dp = (BITMAP *)file2[BHS].dat;

	play_sample(sound[0], volume[0], 128, 1000, TRUE);

	maintainDialog(main_menu, 0);
	
	load_highscore("HSTable.rpr"); //Load the highscore table

	while(!quitgame)
	{
		switch(change_dialog)
		{
		case MM2NG:
			{
				change_dialog = d_newgame();
				break;
			}
		
		case MM2PM:
			{
				change_dialog = d_pmode();
				break;
			}
		
		case MM2OP:
			{
				change_dialog = d_options();
				break;
			}
		
		case TOMM:
			{
				maintainDialog(main_menu, 0);
				break;
			}

		case TOHS:
			{
				change_dialog = d_hs();
				break;
			}
		}
	}
	save_highscore("HSTable.rpr");

	destroyEverything();

	allegro_exit();
	return;
}
END_OF_MAIN()


