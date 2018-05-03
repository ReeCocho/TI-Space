/* Includes. */
#include <tice.h>
#include <keypadc.h>
#include "palette.h"
#include "player.h"
#include "spc_util.h"

vec2 spc_player_position = { 4.0f, 7.0f };

uint8_t spc_player_sprite[2 + (SPC_PLAYER_WIDTH * SPC_PLAYER_HEIGHT)] =
{
	SPC_PLAYER_WIDTH, SPC_PLAYER_HEIGHT,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 3, 1, 2, 2, 1, 3, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 2, 1, 2, 2, 1, 2, 1, 1, 1, 1, 1,
	1, 1, 1, 5, 1, 2, 2, 2, 2, 2, 2, 1, 5, 1, 1, 1,
	1, 1, 1, 2, 1, 2, 2, 1, 1, 2, 2, 1, 2, 1, 1, 1,
	1, 1, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 1, 1,
	1, 1, 1, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 1, 1, 1,
	1, 1, 1, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 1, 1, 1,
	1, 1, 1, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 1, 1, 1
};

void move_player()
{
	if(kb_Data[7] & kb_Left)
		spc_player_position.x -= 0.1f;
	
	if(kb_Data[7] & kb_Right)
		spc_player_position.x += 0.1f;
	
	if(spc_player_position.x < 0.5f)
		spc_player_position.x = 0.5f;
	
	if(spc_player_position.x > 9.5f)
		spc_player_position.x = 9.5f;
}

void shoot_player()
{
	static uint8_t last_press = 0;
	
	if(!last_press && (last_press = kb_Data[1] & kb_Alpha))
	{
		gfx_PrintUInt(rtc_Time(), 8);
	}
}

void draw_player()
{
	uint16_t x_pos = to_screen_space(spc_player_position.x) - ((SPC_PLAYER_WIDTH * SPC_SCL_FAC) / 2);
	uint16_t y_pos = to_screen_space(spc_player_position.y) - ((SPC_PLAYER_HEIGHT * SPC_SCL_FAC) / 2);
	
	gfx_ScaledTransparentSprite_NoClip
	(
		(gfx_sprite_t*)spc_player_sprite,
		(uint24_t)x_pos,
		(uint8_t)y_pos,
		SPC_SCL_FAC,
		SPC_SCL_FAC
	);
}