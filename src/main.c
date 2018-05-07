/*
 *--------------------------------------
 * Program Name: Test Program
 * Author: Connor J. Bramham
 * License: None
 * Description: Platformer game.
 *--------------------------------------
*/

/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

/* Standard headers (recommended) */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Other */
#include <graphx.h>
#include <keypadc.h>
#include "spc_util.h"
#include "palette.h"
#include "player.h"
#include "background.h"
#include "asteroids.h"

void main(void) 
{
	// Clear the screen
    os_ClrHome();
	
	// Initialize the 8bpp graphics
    gfx_Begin();
	
	// Enable double buffering
	gfx_SetDrawBuffer();
	
	// Set color palette
	gfx_SetPalette(spc_color_palette, sizeof(uint16_t) * SPC_COLOR_COUNT, 0);
	gfx_SetTransparentColor(1);
	gfx_SetTextFGColor(2);
	gfx_SetColor(2);
	
	// Random seed
	srandom(rtc_Time());
	
	// Initialize game
	init_background();
	init_asteroids();
	init_player();
	
	// Set timer target
	timer_1_MatchValue_1 = (unsigned int)(-1); 
	
	// Set timer value
	timer_1_Counter = 0;
	
	// Enable the timer, set it to the 32768 kHz clock, enable 
	// an interrupt once it reaches 0, and make it count up.
    timer_Control = TIMER1_ENABLE | TIMER1_32K | TIMER1_NOINT | TIMER1_UP;
	
	// Wait for a key to be pressed
    while (spc_game_running)
	{
		// Update kb_Data
		kb_Scan();
	
		// Close game
		if(kb_Data[6] & kb_Clear) spc_game_running = 0;
	
		// Clear screen
		gfx_ZeroScreen();
		
		// Game logic
		calculate_delta_time();
		draw_background();
		move_player();
		shoot_player();
		draw_projectiles();
		draw_asteroids();
		draw_player();
	
		// Swap back buffer
		gfx_SwapDraw();
	}

    // Close the graphics
    gfx_End();
}