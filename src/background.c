/* Includes. */
#include <tice.h>
#include <graphx.h>
#include "spc_util.h"
#include "vectors.h"
#include "background.h"

/* Number of stars in the background. */
#define SPC_STAR_COUNT 64

/* Star structure. */
typedef struct
{
	uint24_t x; 
	uint8_t y;
} Star;

/* Y positions of stars. */
Star spc_stars[SPC_STAR_COUNT];

void init_background()
{
	uint16_t i;
	
	// Set random star positions
	for(i = 0; i < SPC_STAR_COUNT; ++i)
	{
		spc_stars[i].x = (uint24_t)random() % LCD_WIDTH;
		spc_stars[i].y = (uint8_t)random() % LCD_HEIGHT;
	}
}

void draw_background()
{
	static float timer = 0.0f;
	uint8_t i;
	uint8_t move_stars = 0;

	// Increment timer
	timer += spc_delta_time;
	
	// Check if we should move stars
	if(timer > 0.03f)
	{
		move_stars = 1;
		timer = 0.0f;
	}
	
	// Move all the stars down
	gfx_SetColor(2);
	for(i = 0; i < SPC_STAR_COUNT; ++i)
	{	
		if(move_stars)
		{
			// Move star down
			++spc_stars[i].y;
			
			// Loop star
			if(spc_stars[i].y > LCD_HEIGHT) spc_stars[i].y = 0;
		}
		
		// Draw star
		gfx_SetPixel(spc_stars[i].x, spc_stars[i].y);
	}
}