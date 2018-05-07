/* Includes. */
#include <tice.h>
#include "spc_util.h"

uint8_t spc_game_running = 1;
float spc_delta_time = 0.0f;
uint32_t last_timer_val = 0;

void calculate_delta_time()
{
	uint32_t new_timer_val = (uint32_t)timer_1_Counter;
	spc_delta_time = (float)(new_timer_val - last_timer_val) / 32768.0f;
	last_timer_val = new_timer_val;
}

uint16_t to_screen_space(float pos)
{
	return (uint16_t)(pos * SPC_PPU);
}