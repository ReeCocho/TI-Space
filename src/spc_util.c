/* Includes. */
#include "spc_util.h"

uint16_t to_screen_space(float pos)
{
	return (uint16_t)(pos * SPC_PPU);
}