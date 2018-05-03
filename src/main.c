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
#include "palette.h"
#include "player.h"

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
	
	// Wait for a key to be pressed
    while (1)
	{
		// Update kb_Data
		kb_Scan();
	
		// Close game
		if(kb_Data[6] & kb_Clear) break;
	
		// Clear screen
		gfx_ZeroScreen();
		
		// Draw player
		move_player();
		draw_player();
		
		// Swap back buffer
		gfx_SwapDraw();
	}

    // Close the graphics
    gfx_End();
}