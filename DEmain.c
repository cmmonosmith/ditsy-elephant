// 0=================================================================O
//
//  Project Name:    Ditsy Elephant version 1.00 Final
//  File Name:       DEmain.c
//  Author:          Chris Monosmith - cmmonosmith@comcast.net
//  Graphics:        Chris Monosmith - cmmonosmith@comcast.net
//  Date Started:    05 / 04 / 2002
//  Description:     _main funtion, defines, setup/cleanup, etc...
//
//          Freeware 2002 by Legacy Calcware
//
// 0=================================================================0

#define USE_TI89		// make for TI-89
#define USE_TI92PLUS	// make for TI-92 Plus
#define USE_V200		// make for Voyage 200
#define NO_EXIT_SUPPORT // makes the program shorter, calls _main function directly
#define MIN_AMS 100		// minimum ASM version is 1.00

#define DECK_SIZE 52   // 52 cards in a deck
#define HAND_SIZE 13   // 13 cards for 4 hands
#define PLAYERS 4	   // 4 players
#define SLOW_DELAY 3   // 3/20 second delay
#define KEY_DELAY 5	   // 1/4 second delay
#define TURN_DELAY 20  // 1 second delay
#define LONG_PAUSE 30  // 3/2 second delay
#define SHORT_PAUSE 15 // 3/4 second delay

// the CARD and PLAYER structures
typedef struct
{
	short face;
	short suit;
} CARD;
typedef struct
{
	CARD hand[HAND_SIZE];
	short in[HAND_SIZE];
} PLAYER;

// the actual deck and player and last card variables
CARD deck[DECK_SIZE];
PLAYER ps[PLAYERS];
CARD lc[4];

// some more globals...
short places[4] = {-1, -1, -1, -1};
short place;
short around;

#include <graph.h>
#include <statline.h>
#include <intr.h>

#include "intro.h"
#include "routines.h"
#include "gameplay.h"

void _main(void)
{
	short turn, loop0, loop1;
	LCD_BUFFER screenbuffer;
	INT_HANDLER save_int_1;

	// save the screen contents to replace "#define SAVE_SCREEN"
	LCD_save(screenbuffer);

	// set USER_TIMER for a 1/20th of a second delay
	OSFreeTimer(6);
	OSRegisterTimer(6, 1);

	// turn off the status line only
	save_int_1 = GetIntVec(AUTO_INT_1);
	SetIntVec(AUTO_INT_1, DUMMY_HANDLER);

	// if you press [ESC] after the intro, quit
	if (!intro())
		goto end;

	randomize();

	// set up everything we need to play
	place = 0;
	turn = 0;
	around = 0;
	initDECK();
	setupDECK();
	for (loop0 = 0; loop0 < 4; loop0++)
	{
		lc[loop0].face = -1;
		lc[loop0].suit = -1;
		places[loop0] = -1;
	}
	turn = findFIRST();
	playFIRST(turn);
	turn++;
	if (turn > 3)
		turn = 0;
	drawHANDS();

// label for playing more than once
again:

	// play the game!!! ^_^
	while (TRUE)
	{
		if (outofCARDS(turn))
		{
			setPLACE(turn);
			around++;
			if (around == 0)
				around = -1;
			if (around > 3)
				around = 0;
			goto skip;
		}
		if (turn == 0)
		{
			if (!pTURN(turn))
				goto end;
		}
		if (turn > 0)
		{
			cTURN(turn);
		}
	skip:
		loop1 = 0;
		for (loop0 = 0; loop0 < 4; loop0++)
		{
			if (places[loop0] > -1)
				loop1++;
		}
		if (loop1 == 4)
			break;
		turn++;
		if (turn > 3)
			turn = 0;
	}

	// if you decide, for some reason, not to play again U_U, then quit
	if (!playAGAIN())
		goto end;

	// reset all the variables to play again with
	place = 0;
	turn = 0;
	around = 0;
	initDECK();
	setupDECK();
	switchCARDS();
	for (loop0 = 0; loop0 < 4; loop0++)
	{
		lc[loop0].face = -1;
		lc[loop0].suit = -1;
		places[loop0] = -1;
	}
	sortHANDS();
	turn = findFIRST();
	playFIRST(turn);
	turn++;
	if (turn > 3)
		turn = 0;
	drawHANDS();
	// and play again
	goto again;

end:
	// clean up and leave
	SetIntVec(AUTO_INT_1, save_int_1);
	ngetchx();
	OSFreeTimer(6);
	LCD_restore(screenbuffer);
	ST_helpMsg("Ditsy Elephant -- Legacy Calcware");
}