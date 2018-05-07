/* Includes. */
#include "palette.h"

uint16_t spc_color_palette[SPC_COLOR_COUNT] = 
{
	gfx_RGBTo1555(  0,   0,   0),	// Black
	gfx_RGBTo1555(255,   0, 255),	// Transparent
	gfx_RGBTo1555(255, 255, 255),	// White
	gfx_RGBTo1555(255,   0,   0),	// Red
	gfx_RGBTo1555(  0, 255,   0), 	// Green
	gfx_RGBTo1555(  0,   0, 255),	// Blue
	gfx_RGBTo1555(124,  85,  59),	// Brown 1
	gfx_RGBTo1555(188, 129,  90),	// Brown 2
	gfx_RGBTo1555(130, 112, 100)	// Brown 3
};