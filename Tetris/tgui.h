
/*	  EXTREME BLOCKS - Copyright (C) 2010 by Oscar D. Olarte  *
 
 *    (c) RPR-GDevelopment - 2010                             *
 *    Written by Oscar Olarte                                 *

 *    This source code is released under the The GNU          *
 *    General Public License (GPL). Please refer to the       *
 *    document license.txt in the source directory or         *
 *    http://www.gnu.org for license information.			  */


#ifndef TGUI_H
#define TGUI_H

#include "allegro.h"
#include "ftetris.h"

#define TOMM 0
#define MM2NG 1
#define MM2PM 2
#define MM2OP 3
#define TOHS 4
#define TOCK 5
#define MAX_BYTES_PER_CHAR 4
#define LEN 3

extern int change_dialog; //Indicates to what dialog the program changes depending of the user
extern int pr_mod; //Indicates what board feature the user selected
extern int volume[2]; //The volume of the sound effects and music

extern char the_string[(LEN + 1) * MAX_BYTES_PER_CHAR]; //String for the Game_Over dialog

/*Dialogs for the entire game*/
extern DIALOG_PLAYER *player[1];
extern DIALOG main_menu[];
extern DIALOG options[];
extern DIALOG prac_mode[];
extern DIALOG new_game[];
extern DIALOG sel_level[];
extern DIALOG game_over[];
extern DIALOG cred_key[];
extern DIALOG show_hs[];

//Function that initialize, update and destroy a dialog
void maintainDialog(DIALOG *d, int cont);
//My personal button for dialogs
int my_button_proc(int msg, DIALOG *d, int c);
//My personal select process for dialogs
int dselec_proc(int msg, DIALOG *d, int c);
//My personal draw process for dialogs
int mydraw_proc(int msg, DIALOG *d, int c);
//Process for the listbox that contains levels
char *listbox_getter(int index, int *list_size);
//Function for redrawing dialogs
int drawing(void *);

////*Personal Functions For Differentes Buttons In The Game*////
int quit(void);
int ret_mm(void);
int p_mode(void);
int opt(void);
int back(void);
int new_g(void);
int pause(void);
int no_blocks(void);
int ran_blocks(void);
int s_level(void);
int hscore(void);
int credits(void);
int keyboard(void);
////////////////////////////////////////////////////////////////

#endif