// 0=================================================================O
//
//  Project Name:    Ditsy Elephant version 1.00 Final
//  File Name:       intro.h
//  Author:          Chris Monosmith - cmmonosmith@comcast.net
//  Graphics:        Chris Monosmith - cmmonosmith@comcast.net
//  Date Started:    05 / 04 / 2002
//  Description:     the intro and all related routines
//                   NOTE: this intro is now out of date, but I am
//                   too lazy to change it to bring up to how the
//                   rest of my projects are. not bad; old-fashioned
//
//          Freeware 2002 by Legacy Calcware
//
// 0=================================================================0

#include <gray.h>
#include <mem.h>
#include <stdlib.h>
#include <kbd.h>
#include <system.h>
#include <sprites.h>
#include <compat.h>

#include "LEGACYpic.h" // the LEGACY CALCWARE logo
#include "DEpic.h"	   // the DE logo, the fanned cards

short KEYisESC(void)
{
	// if [ESC] is pressed
	if (_keytest(RR_ESC))
		return 1;
	return 0;
}
short isKEYPRESSED(void)
{
	// if any key is pressed
	if (_rowread(0) & 0xff)
		return 1;
	return 0;
}

// a delay, gets integer time, which is the number of 20ths of a second to wait
void delay(short time)
{
	int t;
	for (t = 0; t < time; t++)
	{
		while (!OSTimerExpired(6))
			;
		OSTimerRestart(6);
	}
}

// draw a background
void drawBG(short bg)
{
	unsigned char *dest0;
	unsigned char *dest1;
	unsigned char *src0;
	unsigned char *src1;
	short loop;

	dest0 = GetPlane(0);
	dest1 = GetPlane(1);
	// choose background to draw based on bg
	if (bg == 0)
	{
		src0 = LEGACYpic0;
		src1 = LEGACYpic1;
	}
	else
	{
		src0 = DEpic0;
		src1 = DEpic1;
	}

	// clear the screen
	memset(GetPlane(0), 0, LCD_SIZE);
	memset(GetPlane(1), 0, LCD_SIZE);

	// copy the picture data to the grayscale planes
	for (loop = 0; loop < 100; loop++, src0 += 20, src1 += 20, dest0 += 30, dest1 += 30)
	{
		memcpy(dest0, src0, 20);
		memcpy(dest1, src1, 20);
	}
}

// 0=================================================================O
//  the intro!!! ^_^ fading in and out, cool logos, it's sweet...
// 0=================================================================0
short intro(void)
{
	short a;

	GrayOn();

	// darken the screen
	for (a = 0; a < 8; a++)
	{
		delay(SLOW_DELAY);
		OSContrastUp();
	}
	// draw the LEGACY CALCWARE logo
	drawBG(0);
	// lighten up the screen
	for (a = 0; a < 8; a++)
	{
		delay(SLOW_DELAY);
		OSContrastDn();
	}
	// pause
	delay(LONG_PAUSE);
	// darken the screen
	for (a = 0; a < 8; a++)
	{
		delay(SLOW_DELAY);
		OSContrastUp();
	}
	// fill the screen with 1s in both planes
	memset(GetPlane(0), 0xff, LCD_SIZE);
	memset(GetPlane(1), 0xff, LCD_SIZE);
	// draw "PRESENTS" in white text
	for (a = 0; a < 2; a++)
	{
		SetPlane(a);
		FontSetSys(F_8x10);
		DrawStr(47, 45, "PRESENTS", A_REVERSE);
	}
	// lighten up the screen
	for (a = 0; a < 8; a++)
	{
		delay(SLOW_DELAY);
		OSContrastDn();
	}
	// pause
	delay(LONG_PAUSE);
	// draw the DE logo
	drawBG(1);
	// pause
	delay(SHORT_PAUSE);
	// draw the text on the screen
	for (a = 0; a < 2; a++)
	{
		SetPlane(a);
		FontSetSys(F_8x10);
		DrawStr(30, 37, "DE v 1.00", A_NORMAL);
		DrawStr(34, 52, "FINAL", A_NORMAL);
		FontSetSys(F_4x6);
		DrawStr(65, 93, "-press a key; [ESC] to quit", A_NORMAL);
	}

	while (isKEYPRESSED())
		; // wait for all keys to be released
	while (!isKEYPRESSED())
		;			// wait for a key
	a = KEYisESC(); // if [ESC] is pressed
	GrayOff();
	if (a)
		return 0;
	return 1;
}
