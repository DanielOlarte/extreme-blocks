
/*	  EXTREME BLOCKS - Copyright (C) 2010 by Oscar D. Olarte  *
 
 *    (c) RPR-GDevelopment - 2010                             *
 *    Written by Oscar Olarte                                 *

 *    This source code is released under the The GNU          *
 *    General Public License (GPL). Please refer to the       *
 *    document license.txt in the source directory or         *
 *    http://www.gnu.org for license information.			  */

#ifndef FTETRIS_H
#define FTETRIS_H

#include "allegro.h"
#include <stdio.h>
#include <cstring>
#include <string.h>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define BLOCK_SIZE 20
#define BOARD_POSITION 300
#define EMPTY 0
#define FILL 1

typedef struct BLOCK
{
	int ID; //Color of the block
	int full; //Block EMPTY or FILL
}BLOCK;

typedef struct highscores
{
	char name[4]; //Name of the player
	int score; //Score of the player
	int level; //Level the player finally get defeat or win
}HS;

class cPiece
{
public:

	cPiece();

	BLOCK piece[4][4]; //Piece with 4x4 dimensions
	int rotation; //Rotation of the piece
	int type; //Type of the piece

	int getPosX() { return pos_x; } //Get the current position in x
	int getPosY() { return pos_y; } //Get the current position in y
	void setPosX(int x) { pos_x = x; } //Modify the position in x
	void setPosY(int y) { pos_y = y; } //Modify the position in y

private:

	int pos_x, pos_y; //Position in x and y
};

extern class cPiece current; //Piece which is on board
extern class cPiece next; //Next piece

extern BLOCK blocks[7][4][4][4]; //Multi-dimensional array for every piece, with every rotation
extern BITMAP *temp[8]; //Used for the images of the blocks

extern HS highscore[10]; //Struct for the highscores

extern int map[BOARD_WIDTH][BOARD_HEIGHT]; //Board

extern BITMAP *map_buffer; //Buffer for the board
extern BITMAP *score_buffer; //Buffer for shows the score, speed, time...
extern BITMAP *next_buffer; //Buffer for shows the next piece in the board

extern FONT *myfont; //My personal font
extern SAMPLE *sound[6]; //Array with the sounds of the game
extern DATAFILE *file1, *file2, *file3; //Datafile with all the resources

//board.cpp

/*Put the current piece in the map*/
void putBlock(cPiece &falling, int x, int y);
/*Check collisions with the board (WIDTH, HEIGHT) and with the other blocks on the map*/
int noCollision(cPiece &falling, int x, int y);
/*Checks if the row of the top have any block, what menas the game is over*/
int gameOver();
/*Delete one row from the map, who only happen when the row is completely full*/
void deleteRow(int row);
/*Checks all the rows in the map for delete with the previous function, add score, and change the speed*/
void possibleRows();
/*Verify if a position in the map it's fill or empty and return the value*/
int isFreeBlock(int x, int y);
/*Gives extra points at the final of each level depending in various factors*/
void bonusPoints();

//draw.cpp

/*Draw the pieces (falling and next)*/
void drawPiece(cPiece &fig, int tipo);
/*Draw the board*/
void drawBoard();
/*Show the info of the current game*/
void drawInfo(int score, int level, int t, int del, FONT *f, int speed);
/*Clear the screen and buffer*/
void clearScreen();

//fblocks.cpp

/*Copy the next piece to falling piece, and create a new next piece*/
void createBlock(cPiece &falling, cPiece &after);
/*Modify a piece depending of his type, and rotation*/
void changePiece(cPiece &falling, int p, int rotation);
/*Rotate the piece depending of the key pressed by the player*/
int rotateBlock(int rotate, int actual);
/*Clean the struct of the piece for create a new one*/
void cleanPiece(cPiece &temp);

//setup.cpp

/*Setup every elements needed for start the game*/
void setupscreen();	
/*Setup the blocks and pieces used in the game*/
void setupblocks();
/*Initialize the first falling(current) and next piece*/
void initPieces(cPiece &falling, cPiece &after);
/*Initialize the board empty*/
void initMap();
/*Destroy evey bitmap, or pointer that may casue a memory leak*/
void destroyEverything();
/*Gives a random number*/
int gRandom(int limit, int s);

//levels.cpp

/*Select the type of practice*/
void modePract(int practice_mode);
/*Fill the map with random blocks*/
void fillMap();
/*Fill the map with blocks depending on the type of game chosen and the level*/
void mappingLevel(int lev_act);
/*Change background of the game depending on the type of game (levels or practice)*/
void changeBG(DIALOG *d, int lev_act, int mode); 

//game.cpp

/*Loop of the game*/
int playGame();
/*Initialize a new game*/
void newGame(int l, int p, int t);
/*Select the type of game selected*/
int typeGame(int lev, int p_m, int type, int change);
/*Change the level if the user defeat the current level*/
void changeLevel(int lev_act);
/*Draw everything on the scren*/
void drawScreen();
/*Load a highscore file or if this one is corrupted or doesn't exist creates a new list*/
void load_highscore(const char *filename);
/*Saves a list of highscore in a file*/
void save_highscore(const char *filename);
/*Adds a new highscore to the list*/
void add_highscore(int score, int level);


//dialogs.cpp

/*The gameplay for the practice mode*/
int d_pmode();
/*The options menu with all his features*/
int d_options();
/*The highscore table*/
int d_hs();

int d_newgame();

//Variables for the FPS and the keyboard delay
extern volatile int ticks;
extern volatile int keyboard_counter;
extern volatile int fps ;
extern volatile int fpscount;
extern volatile int time_l;
extern volatile int t_time; 

extern int speed; //Speed of the falling pieces
extern int t_speed; //Temp for save the speed of the falling pieces
extern int score; //Score of the player
extern int lev_act; //Actual level
extern int move_level; //Verify if the player defeat the current level
extern int rows_del; //Number of rows deleted in the current level
extern int point_lev[7]; //Points assigned for each level
extern int practice_mode; //Type of the practice mode (no blocks or with random blocks)
extern int quitgame; //Verify if the player exit a game.
extern int stop; //Verify if the user press pause
extern int inv_s[41]; //Function for inverse numeber
extern int entry; //Verify if the player entry to highscores
extern int bonus[3]; //Array with values for the bonus at the end of each level
extern int time_level[7]; //Stores the neccesary time to defeat each level
extern int in_game; //Indicates if the user is playing the game

#endif