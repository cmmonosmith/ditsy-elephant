// 0=================================================================O
//
//  Project Name:    Ditsy Elephant version 1.00 Final
//  File Name:       gameplay.h
//  Author:          Chris Monosmith - Sparky0216@aol.com
//  Graphics:        Chris Monosmith - Sparky0216@aol.com
//  Date Started:    05 / 04 / 2002
//  Description:     the actual gameplay routines. the turns, playing
//
//          Freeware 2002 by Legacy Calcware
//
// 0=================================================================0

short outofCARDS(short turn)
{
	short loop0, loop1 = 0;

	// check to see if a player is out of cards
	for (loop0 = 0; loop0 < HAND_SIZE; loop0++)
	{
		if (ps[turn].in[loop0] > 0)
			break;
		loop1++;
	}
	if (loop1 == 13)
		return 1;
	return 0;
}

// 0=================================================================O
//  the player's turn. select and play cards, blah blah blah...
// 0=================================================================0
short pTURN(short turn)
{
	short loop0, loop1, loop2;
	short picked[5] = {-1, -1, -1, -1, 0};
	short numF = -1;

	LCD_BUFFER temp;

	while (isKEYPRESSED())
		;

	around++;
	if (around > 3)
		around = 0;

	for (picked[4] = 0; picked[4] < HAND_SIZE; picked[4]++)
	{
		if (ps[turn].in[picked[4]])
			break;
	}

	if (around > 0)
		numF = lc[0].face;
	if (around == 0)
		numF = -1;

	drawHANDsel(picked[0], picked[1], picked[2], picked[3], picked[4]);

	while (TRUE)
	{
	top:
		// if left is pressed
		if (_keytest(RR_LEFT))
		{
			picked[4] -= 1;
			if (picked[4] < 0)
				picked[4] = 12;
			while (!ps[0].in[picked[4]])
			{
				picked[4] -= 1;
				if (picked[4] < 0)
					picked[4] = 12;
			}
			drawHANDsel(picked[0], picked[1], picked[2], picked[3], picked[4]);
			delay(KEY_DELAY);
		}
		// if right is pressed
		if (_keytest(RR_RIGHT))
		{
			picked[4] += 1;
			if (picked[4] > 12)
				picked[4] = 0;
			while (!ps[0].in[picked[4]])
			{
				picked[4] += 1;
				if (picked[4] > 12)
					picked[4] = 0;
			}
			drawHANDsel(picked[0], picked[1], picked[2], picked[3], picked[4]);
			delay(KEY_DELAY);
		}
		// if [2nd] or F1 are pressed. [2nd] is best for 89s, but out of the way
		// for 92 Plusses, so F1 takes its place
		if (_keytest(RR_2ND) || _keytest(RR_F1))
		{
			// if the card is already picked
			for (loop0 = 0; loop0 < 4; loop0++)
			{
				if (picked[loop0] == picked[4])
				{
					picked[loop0] = -1;
					drawHANDsel(picked[0], picked[1], picked[2], picked[3], picked[4]);
					while (isKEYPRESSED())
						;
					goto top;
				}
			}
			// find an open spot in the picked array and set it
			loop1 = 0;
			for (loop0 = 0; loop0 < 4; loop0++)
			{
				if (picked[loop0] < 0)
					loop1++;
			}
			// if this is the first card, just set it and go
			if (loop1 == 4)
			{
				for (loop0 = 0; loop0 < 4; loop0++)
				{
					if (ps[0].hand[picked[4]].face > numF)
					{
						picked[loop0] = picked[4];
						break;
					}
				}
				drawHANDsel(picked[0], picked[1], picked[2], picked[3], picked[4]);
				while (isKEYPRESSED())
					;
				goto top;
			}
			// if it's not the first, see if the card matches the others
			for (loop0 = 0; loop0 < 4; loop0++)
			{
				if (picked[loop0] > -1 &&
					ps[0].hand[picked[4]].face == ps[0].hand[picked[loop0]].face)
				{
					for (loop1 = 0; loop1 < 4; loop1++)
					{
						if (picked[loop1] < 0)
						{
							picked[loop1] = picked[4];
							break;
						}
					}
					drawHANDsel(picked[0], picked[1], picked[2], picked[3], picked[4]);
					delay(KEY_DELAY);
					goto top;
				}
			}
			drawHANDsel(picked[0], picked[1], picked[2], picked[3], picked[4]);
			while (isKEYPRESSED())
				;
		}
		// several buttons work to play the selected cards in different places on the
		// calculators to ensure that at least one is always easy to press for all
		// the different calcs
		if (_keytest(RR_SHIFT) || _keytest(RR_DIAMOND) || _keytest(RR_ENTER) || _keytest(RR_ENTER1) || _keytest(RR_ENTER2))
		{
			loop1 = 0;
			loop2 = 0;
			for (loop0 = 0; loop0 < 4; loop0++)
			{
				if (picked[loop0] > -1)
					loop1++;
				if (lc[loop0].face > -1)
					loop2++;
			}
			// if you picked no cards
			if (loop1 == 0)
			{
				while (isKEYPRESSED())
					;
				LCD_save(temp);
				drawDIALOG(38, 28, 122, 70);
				FontSetSys(F_6x8);
				DrawStr(43, 33, "Really Pass?", A_NORMAL);
				DrawStr(49, 48, "[ESC] : no", A_NORMAL);
				DrawStr(46, 58, "other : yes", A_NORMAL);
				while (!isKEYPRESSED())
					;
				if (KEYisESC())
				{
					while (isKEYPRESSED())
						;
					LCD_restore(temp);
					goto top;
				}
				LCD_restore(temp);
				break;
			}
			// if you picked insufficient cards
			if (loop1 < loop2 && around != 0)
			{
				while (isKEYPRESSED())
					;
				LCD_save(temp);
				drawDIALOG(26, 28, 134, 70);
				FontSetSys(F_6x8);
				DrawStr(31, 33, "Can't Play Those", A_NORMAL);
				DrawStr(40, 48, "[ESC] : retry", A_NORMAL);
				DrawStr(43, 58, "other : pass", A_NORMAL);
				while (!isKEYPRESSED())
					;
				if (KEYisESC())
				{
					drawHANDS();
					drawHANDsel(picked[0], picked[1], picked[2], picked[3], picked[4]);
					while (isKEYPRESSED())
						;
					LCD_restore(temp);
					goto top;
				}
				LCD_restore(temp);
				break;
			}
			// if it's okay, just play them...
			// first erase the previously played cards
			for (loop0 = 0; loop0 < 4; loop0++)
			{
				if (picked[loop0] > -1)
				{
					around = 0;
					for (loop1 = 0; loop1 < 4; loop1++)
					{
						lc[loop1].face = -1;
						lc[loop1].suit = -1;
					}
					break;
				}
			}
			loop1 = 0;
			// then fill in the played cards
			for (loop0 = 0; loop0 < 4; loop0++)
			{
				if (picked[loop0] > -1)
				{
					lc[loop1].face = ps[turn].hand[picked[loop0]].face;
					lc[loop1].suit = ps[turn].hand[picked[loop0]].suit;
					ps[turn].in[picked[loop0]] = 0;
					ps[turn].in[picked[loop0]] = 0;
					loop1++;
				}
			}
			// if you're out of cards, set around so that the next person
			// can play anything they want
			if (outofCARDS(turn))
			{
				around = -1;
			}
			break;
		}
		// and of course, if you press [ESC], ask if you really want to quit.
		// why would anyone really want to quit?
		if (KEYisESC())
		{
			while (isKEYPRESSED())
				;
			LCD_save(temp);
			drawDIALOG(38, 28, 122, 70);
			FontSetSys(F_6x8);
			DrawStr(43, 33, "Really Quit?", A_REPLACE);
			DrawStr(46, 48, "[ESC] : yes", A_REPLACE);
			DrawStr(49, 58, "other : no", A_REPLACE);
			while (!isKEYPRESSED())
				;
			if (KEYisESC())
			{
				LCD_restore(temp);
				return 0;
			}
			while (isKEYPRESSED())
				;
			LCD_restore(temp);
			drawHANDS();
			drawHANDsel(picked[0], picked[1], picked[2], picked[3], picked[4]);
		}
	}

	drawHANDS();
	return 1;
}

// 0=================================================================O
//  the computer's turn. find and play cards, blah blah blah...
// 0=================================================================0
void cTURN(short turn)
{
	short loop0, loop1, loop2, loop3;
	short numLC = 0, numCP = 0, numF = -1;
	short picked = -1;
	short FLAG0 = 0;

	// tell everyone that the computer is playing its cards
	FontSetSys(F_6x8);
	DrawStr(49, 26, "playing...", A_NORMAL);

	around++;
	if (around > 3)
		around = 0;

	if (around > 0)
	{
		for (loop0 = 0; loop0 < 4; loop0++)
		{
			if (lc[loop0].face > -1)
				numLC++;
		}
		numF = lc[0].face;
	}

	if (around == 0)
	{
		numLC = 1;
		numF = -1;
	}

	// while no cards are found
	while (!FLAG0)
	{
		for (loop0 = 0; loop0 < HAND_SIZE; loop0++)
		{
			numCP = 0;
			picked = -1;
			// search for playable cards!!!
			if (ps[turn].in[loop0] > 0 && ps[turn].hand[loop0].face > numF)
			{
				picked = ps[turn].hand[loop0].face;
				numCP++;
				for (loop1 = loop0 + 1; loop1 <= loop0 + 3; loop1++)
				{
					if (loop1 < 13)
					{
						if (ps[turn].in[loop1] > 0 && ps[turn].hand[loop1].face == picked)
						{
							numCP++;
						}
					}
				}
			}
			// if it found playable ones ^_^
			if (around == 0 && numCP > 0)
			{
				FLAG0++;
				break;
			}
			// if it found playable ones in a different way ^_^
			if (numCP >= numLC)
			{
				FLAG0++;
				break;
			}
		}
		// if it found none U_U
		if (FLAG0 > 0)
			break;
		picked = -1;
		numCP = 0;
		break;
	}

	// if the cards are insufficient to play, skip playing them
	if (picked < 0 || numCP == 0)
		goto bottom;
	if (numCP < numLC && around > 0)
		goto bottom;

	around = 0;
	// erase the previously played cards
	for (loop0 = 0; loop0 < 4; loop0++)
	{
		lc[loop0].face = -1;
		lc[loop0].suit = -1;
	}
	loop1 = 0;
	// and set in the new ones
	for (loop0 = 0; loop0 < HAND_SIZE; loop0++)
	{
		if (ps[turn].hand[loop0].face == picked)
		{
			lc[loop1].face = ps[turn].hand[loop0].face;
			lc[loop1].suit = ps[turn].hand[loop0].suit;
			ps[turn].in[loop0] = 0;
			loop1++;
		}
		// if it's out of cards, set around so that the next person
		// can play anything they want
		if (outofCARDS(turn))
		{
			around = -1;
		}
	}

	// a small delay to give the player a chance to read the new cards
	delay(TURN_DELAY);
bottom:
	drawHANDS();
}
