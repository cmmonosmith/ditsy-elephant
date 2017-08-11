// 0=================================================================O
//
//  Project Name:    Ditsy Elephant version 1.00 Final
//  File Name:       routines.h
//  Author:          Chris Monosmith - Sparky0216@aol.com
//  Graphics:        Chris Monosmith - Sparky0216@aol.com
//  Date Started:    05 / 04 / 2002
//  Description:     all the other routines and sprites and data
//
//          © 2002 by Legacy Calcware  (jk... it's all freeware!)
//  
// 0=================================================================0

unsigned long horzBACK[] = { // the back side of a horizontal card
	0x7FFFF800,0xB3333400,0xCCCCCC00,0xB3333400,0xCCCCCC00,0xB3333400,0xCCCCCC00,0xB3333400,
	0xCCCCCC00,0xB3333400,0xCCCCCC00,0xB3333400,0xCCCCCC00,0xB3333400,0x7FFFF800,0x00000000
};
unsigned short vertBACK[] = { // the back side of a vertical card
	0x7FFC,0xAAAA,0xD556,0xD556,0xAAAA,0xAAAA,0xD556,0xD556,
	0xAAAA,0xAAAA,0xD556,0xD556,0xAAAA,0xAAAA,0xD556,0xD556,
	0xAAAA,0xAAAA,0xD556,0xD556,0xAAAA,0x7FFC,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
};
unsigned long horzFRONT[] = { // the front side of a horizontal card ( blank )
	0x7FFFF800,0x80000400,0x80000400,0x80000400,0x80000400,0x80000400,0x80000400,0x80000400,
	0x80000400,0x80000400,0x80000400,0x80000400,0x80000400,0x80000400,0x7FFFF800,0x00000000
};
unsigned short vertFRONT[] = { // the front side of a vertical card ( blank )
	0x7FFC,0x8002,0x8002,0x8002,0x8002,0x8002,0x8002,0x8002,
	0x8002,0x8002,0x8002,0x8002,0x8002,0x8002,0x8002,0x8002,
	0x8002,0x8002,0x8002,0x8002,0x8002,0x7FFC,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
};
unsigned long horzMASK[] = { // the mask for a horizontal card
	0x800007FF,0x000003FF,0x000003FF,0x000003FF,0x000003FF,0x000003FF,0x000003FF,0x000003FF,
	0x000003FF,0x000003FF,0x000003FF,0x000003FF,0x000003FF,0x000003FF,0x800007FF,0xFFFFFFFF
};
unsigned short vertMASK[] = { // the mask for a vertical card
	0x8003,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x8003,0xFFFF,0xFFFF,
	0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF
};
unsigned char faces[13][8] = {
	{0x38,0x44,0x04,0x18,0x04,0x44,0x38,0x00}, // 3
	{0x44,0x44,0x44,0x7C,0x04,0x04,0x04,0x00}, // 4
	{0x7C,0x40,0x78,0x44,0x04,0x44,0x38,0x00}, // 5
	{0x38,0x44,0x40,0x78,0x44,0x44,0x38,0x00}, // 6
	{0x7C,0x04,0x08,0x10,0x20,0x40,0x40,0x00}, // 7
	{0x38,0x44,0x44,0x38,0x44,0x44,0x38,0x00}, // 8
	{0x38,0x44,0x44,0x3C,0x04,0x44,0x38,0x00}, // 9
	{0x48,0x54,0x54,0x54,0x54,0x54,0x48,0x00}, // 10
	{0x38,0x10,0x10,0x10,0x10,0x50,0x20,0x00}, // J
	{0x38,0x44,0x44,0x44,0x54,0x4C,0x3C,0x00}, // Q
	{0x44,0x48,0x50,0x60,0x50,0x48,0x44,0x00}, // K
	{0x10,0x28,0x44,0x44,0x7C,0x44,0x44,0x00}, // A
	{0x38,0x44,0x04,0x08,0x10,0x20,0x7C,0x00}  // 2
};
unsigned char suits[4][8] = {
	{0x10,0x38,0x7C,0xFE,0xFE,0x7C,0x10,0x38}, // spade
	{0x6C,0xFE,0xFE,0xFE,0x7C,0x38,0x10,0x00}, // heart
	{0x38,0x38,0xD6,0xEE,0xD6,0x10,0x38,0x00}, // club
	{0x10,0x38,0x7C,0xFE,0x7C,0x38,0x10,0x00}  // diamond
};
unsigned char arrow[] = { // the arrow that points at the cards
	0x20,0x20,0xA8,0x70,0x20
};
unsigned char arrowMASK[] = { // the mask for the arrow
	0x00,0x00,0x00,0x00,0x00
};

void initDECK(void) {
	int loop;
	
	// initialize the deck in a nice neat order
	for (loop = 0; loop < DECK_SIZE; loop++) {
		deck[loop].face = loop % 13;
		deck[loop].suit = loop / 13;
	}
}

void sortHANDS(void) {
	short loop0, loop1, loop2;
	CARD card;
	// it's messy, but it replaces qsort(), because I needed to sort the suits
	// WITH the faces, which qsort() could not do... ( qsort() only sorts 1 array )
	for (loop0 = 0; loop0 < PLAYERS; loop0++) {	
		for (loop1 = 0; loop1 < HAND_SIZE - 1; loop1++) {
			for (loop2 = 0; loop2 < HAND_SIZE - 1; loop2++) {
				if (ps[loop0].hand[loop2].face > ps[loop0].hand[loop2+1].face) {
					card.face                    = ps[loop0].hand[loop2].face;
					card.suit                    = ps[loop0].hand[loop2].suit;
					ps[loop0].hand[loop2].face   = ps[loop0].hand[loop2+1].face;
					ps[loop0].hand[loop2].suit   = ps[loop0].hand[loop2+1].suit;
					ps[loop0].hand[loop2+1].face = card.face;
					ps[loop0].hand[loop2+1].suit = card.suit;
				}
			}
		}
	}
}

void setupDECK(void) {
	short loop0, loop1;
	short num0;
	CARD temp;
	
	// shuffle by switching 2 random cards 20*52 times
	for (loop0 = 0; loop0 < 20; loop0++) {
		for (loop1 = 0; loop1 < DECK_SIZE; loop1++) {
			num0        = rand() % DECK_SIZE;
			temp        = deck[loop1];
			deck[loop1] = deck[num0];
			deck[num0]  = temp;
		}
	}
	
	// deal out the cards to the players
	for (loop0 = 0; loop0 < PLAYERS; loop0++) {
		for (loop1 = 0; loop1 < HAND_SIZE; loop1++) {
			ps[loop0].hand[loop1].face = deck[loop1*4+loop0].face;
			ps[loop0].hand[loop1].suit = deck[loop1*4+loop0].suit;
			ps[loop0].in[loop1]        = 1;
		}
	}
	
	// run the sorting routine
	sortHANDS();
}

void switchCARDS(void) {
	short num0, num1;
	CARD card;
	
	// switch the cards from last to first and 3rd to second
	// which ones are explained in DErules.txt
	num0                   = places[0];
	num1                   = places[3];
	card.face              = ps[num0].hand[0].face;
	card.suit              = ps[num0].hand[0].suit;
	ps[num0].hand[0].face  = ps[num1].hand[12].face;
	ps[num0].hand[0].suit  = ps[num1].hand[12].suit;
	ps[num1].hand[12].face = card.face;
	ps[num1].hand[12].suit = card.suit;
	card.face              = ps[num0].hand[1].face;
	card.suit              = ps[num0].hand[1].suit;
	ps[num0].hand[1].face  = ps[num1].hand[11].face;
	ps[num0].hand[1].suit  = ps[num1].hand[11].suit;
	ps[num1].hand[11].face = card.face;
	ps[num1].hand[11].suit = card.suit;
	num0                   = places[1];
	num1                   = places[2];
	card.face              = ps[num0].hand[0].face;
	card.suit              = ps[num0].hand[0].suit;
	ps[num0].hand[0].face  = ps[num1].hand[12].face;
	ps[num0].hand[0].suit  = ps[num1].hand[12].suit;
	ps[num1].hand[12].face = card.face;
	ps[num1].hand[12].suit = card.suit;
}

short findFIRST(void) {
	short loop0, loop1;
	
	// find the player with the 3 of spades, who will play first
	for (loop0 = 0; loop0 < PLAYERS; loop0++) {
		for (loop1 = 0; loop1 < HAND_SIZE; loop1++) {
			if (ps[loop0].hand[loop1].face == 0 &&
			    ps[loop0].hand[loop1].suit == 0) return loop0;
		}
	}
}

void playFIRST(short turn) {
	short loop0;
	
	// automatically play the 3 of spades and all other threes
	// in that player's hand
	for (loop0 = 0; loop0 < 4; loop0++) {
		if (ps[turn].hand[loop0].face == 0) {
			lc[loop0].face = ps[turn].hand[loop0].face;
			lc[loop0].suit = ps[turn].hand[loop0].suit;
			ps[turn].in[loop0] = 0;
		}
	}
}

void drawHANDsel(short a, short b, short c, short d, short e) {
	short loop0;
	short up, l;
	unsigned char *buf;
	
	// clear the lower portion of the screen
	buf  = (unsigned char *)LCD_MEM;
	buf += (30 * 69);
	memset(buf, 0, (30 * 50));
	
	// draw player's hand, selected cards are elevated
	// played cards do not show up
	for (loop0 = 0; loop0 < HAND_SIZE; loop0++) {
		if ((ps[0].in[loop0] > 0)) {
			if (!(a == loop0 || b == loop0 || c == loop0 || d == loop0)) {
				Sprite16(loop0*12, 78, 32, vertMASK, LCD_MEM, SPRT_AND);
				Sprite16(loop0*12, 78, 32, vertFRONT, LCD_MEM, SPRT_OR);
				Sprite8(loop0*12+4, 81, 8, faces[ps[0].hand[loop0].face], LCD_MEM, SPRT_OR);
				Sprite8(loop0*12+4, 90, 8, suits[ps[0].hand[loop0].suit], LCD_MEM, SPRT_OR);
			} else {
				Sprite16(loop0*12, 75, 32, vertMASK, LCD_MEM, SPRT_AND);
				Sprite16(loop0*12, 75, 32, vertFRONT, LCD_MEM, SPRT_OR);
				Sprite8(loop0*12+4, 78, 8, faces[ps[0].hand[loop0].face], LCD_MEM, SPRT_OR);
				Sprite8(loop0*12+4, 87, 8, suits[ps[0].hand[loop0].suit], LCD_MEM, SPRT_OR);
			}
		}
	}
	// and draw the arrow
	Sprite8(e*12+5, 70, 5, arrow, LCD_MEM, SPRT_OR);
}

void drawHANDS(void) {
	short loop0, loop1;
	
	ClearScreen();
	
	// draw all the hands on the screen at once. played cards do not show up
	for (loop0 = 0; loop0 < HAND_SIZE; loop0++) {
		if (ps[0].in[loop0] > 0) {
			Sprite16(loop0*12, 78, 32, vertMASK, LCD_MEM, SPRT_AND);
			Sprite16(loop0*12, 78, 32, vertFRONT, LCD_MEM, SPRT_OR);
			Sprite8(loop0*12+4, 81, 8, faces[ps[0].hand[loop0].face], LCD_MEM, SPRT_OR);
			Sprite8(loop0*12+4, 90, 8, suits[ps[0].hand[loop0].suit], LCD_MEM, SPRT_OR);
		}
		if (ps[1].in[loop0] > 0) {
			Sprite32(0, loop0*3+15, 16, horzMASK, LCD_MEM, SPRT_AND);
			Sprite32(0, loop0*3+15, 16, horzBACK, LCD_MEM, SPRT_OR);
		}
		if (ps[2].in[loop0] > 0) {
			Sprite16(loop0*3+54, 0, 32, vertMASK, LCD_MEM, SPRT_AND);
			Sprite16(loop0*3+54, 0, 32, vertBACK, LCD_MEM, SPRT_OR);
		}
		if (ps[3].in[loop0] > 0) {
			Sprite32(138, loop0*3+15, 16, horzMASK, LCD_MEM, SPRT_AND);
			Sprite32(138, loop0*3+15, 16, horzBACK, LCD_MEM, SPRT_OR);
		}
	}
	
	// the draw the cards previously played, if any
	for (loop0 = 0; loop0 < 4; loop0++) {
		if (lc[loop0].face > -1) {
			Sprite16(loop0*12+54, 39, 32, vertMASK, LCD_MEM, SPRT_AND);
			Sprite16(loop0*12+54, 39, 32, vertFRONT, LCD_MEM, SPRT_OR);
			Sprite8(loop0*12+58, 42, 8, faces[lc[loop0].face], LCD_MEM, SPRT_OR);
			Sprite8(loop0*12+58, 51, 8, suits[lc[loop0].suit], LCD_MEM, SPRT_OR);
		}
	}
}

void setPLACE(short player) {
	short loop0;
	
	// set a player's place if they run out of cards and have not
	// already been given a position
	for (loop0 = 0; loop0 < PLAYERS; loop0++) {
		if (places[loop0] == player) return;
	}
	places[place] = player;
	place++;
}

short playAGAIN(void) {
	short loop0;
	short a;
	char texts[4][10] = {"1ST place","2ND place","3RD place","4TH place"};
	
	ClearScreen();
	
	// tells the player what place he/she got
	for (loop0 = 0; loop0 < 4; loop0++) {
		if (!places[loop0]) break;
	}
	FontSetSys(F_8x10);
	DrawStr(51,37,"you got",A_NORMAL);
	DrawStr(43,53,texts[loop0],A_NORMAL);
	
	while (isKEYPRESSED());
	while (!isKEYPRESSED());
	while (isKEYPRESSED());
	
	GrayOn();
	
	// redraw the title screen
	memset(GetPlane(0),0,LCD_SIZE);
	memset(GetPlane(1),0,LCD_SIZE);
	drawBG(1);
	delay(SHORT_PAUSE);
	// tell you to press a key to play again, or [ESC] to quit... duh
	for (a=0;a<2;a++) {
		SetPlane(a);
		FontSetSys(F_8x10);
		DrawStr(30,37,"DE v 1.00",A_NORMAL);
		DrawStr(34,52,"FINAL",A_NORMAL);
		FontSetSys(F_4x6);
		DrawStr(9,93,"-press a key to play again; [ESC] to quit",A_NORMAL);
	}
	
	while (!isKEYPRESSED());
	a = KEYisESC();
	GrayOff();
	if (a) return 0;
	return 1;
}

void drawDIALOG(short x0, short y0, short x1, short y1) {
	short x2, x3, y2, y3;
	short a, b;
	
	// make a dialog box appear to draw text in... it's kind of hard to follow
	a = ((y0+y1)/2)-1;
	b = ((y0+y1)/2);
	for (x2=((x0+x1)/2)-2,x3=x2+3;x2>=x0;x2--,x3++) {
		DrawLine(x2+1,a-1,x3-1,a-1,A_NORMAL);
		DrawLine(x2,a,x3,a,A_NORMAL);
		DrawLine(x2,b,x3,b,A_NORMAL);
		DrawLine(x2+1,b+1,x3-1,b+1,A_NORMAL);
	}
	delay(5);
	for (y2=((y0+y1)/2)-2,y3=y2+3;y2>=y0;y2--,y3++) {
		DrawLine(x2+1,y2,x3-1,y2,A_NORMAL);
		DrawLine(x2,y2+1,x3,y2+1,A_NORMAL);
		DrawLine(x2,y3-1,x3,y3-1,A_NORMAL);
		DrawLine(x2+1,y3,x3-1,y3,A_NORMAL);
		DrawLine(x2,y2+1,x2,y3-1,A_NORMAL);
		DrawLine(x2+1,y2,x2+1,y3,A_NORMAL);
		DrawLine(x3-1,y2,x3-1,y3,A_NORMAL);
		DrawLine(x3,y2+1,x3,y3-1,A_NORMAL);
	}
	for (a=x2+2;a<=x3-2;a++) {
		DrawLine(a,y2+2,a,y3-2,A_REVERSE);
	}
	delay(5);
}
