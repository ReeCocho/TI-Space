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
	// Countdown timer
	uint8_t countdown;

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
	
	// Instructions
	gfx_ZeroScreen();
	gfx_PrintStringXY("Press ENTER to begin.", (LCD_WIDTH / 2) - 76, (LCD_HEIGHT / 2) + 24);
	gfx_PrintStringXY("Press CLEAR to quit.", (LCD_WIDTH / 2) - 72, (LCD_HEIGHT / 2) + 8);
	gfx_PrintStringXY("Use ARROWS to move.", (LCD_WIDTH / 2) - 68, (LCD_HEIGHT / 2) - 8); 
	gfx_PrintStringXY("Use ALPHA to shoot.", (LCD_WIDTH / 2) - 68, (LCD_HEIGHT / 2) - 24); 
	gfx_SwapDraw();
	
	// Wait for begin
	while(1)
	{
		kb_Scan();
		if(kb_Data[6] & kb_Clear) goto skip_game_over;
		if(!(kb_Data[6] & kb_Enter)) continue;
		
		// Countdown
		for(countdown = 3; countdown <= 3; --countdown)
		{
			gfx_ZeroScreen();
			gfx_SetTextXY(LCD_WIDTH / 2, LCD_HEIGHT / 2);
			gfx_PrintUInt(countdown, 1);
			gfx_SwapDraw();
			delay(1000);
		}
	
		// Run game
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
			draw_score();
		
			// Swap back buffer
			gfx_SwapDraw();
		}
		
		break;
	}

	// Game over text
	gfx_ZeroScreen();
	gfx_PrintStringXY("GAME OVER", (LCD_WIDTH/2)-32, LCD_HEIGHT/2);
	gfx_SwapDraw();

	delay(500);
	
	// Wait for a key press
    while (!os_GetCSC());

	skip_game_over:
	
    // Close the graphics
    gfx_End();
}