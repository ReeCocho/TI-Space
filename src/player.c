/* Includes. */
#include <keypadc.h>
#include "palette.h"
#include "player.h"
#include "spc_util.h"

Projectile spc_projectiles[SPC_PROJ_COUNT];

/* Player sprite dimensions. */
#define SPC_PLAYER_WIDTH 16
#define SPC_PLAYER_HEIGHT 16

vec2 spc_player_position = { 4.0f, 7.0f };

unsigned int spc_player_score = 0;

/* Player sprite data. */
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

void init_player()
{
	uint8_t i;
	
	for(i = 0; i < SPC_PROJ_COUNT; ++i)
		spc_projectiles[i].enabled = 0;
}

void move_player()
{
	if(kb_Data[7] & kb_Left) spc_player_position.x -= spc_delta_time * 3.0f;
	if(kb_Data[7] & kb_Right) spc_player_position.x += spc_delta_time * 3.0f;
	if(spc_player_position.x < 0.5f) spc_player_position.x = 0.5f;
	if(spc_player_position.x > 9.5f) spc_player_position.x = 9.5f;
}

void shoot_player()
{
	static float timer = 0.0f;
	static uint8_t last_press = 0;
	uint8_t cur_press = kb_Data[2] & kb_Alpha;
	uint8_t i;
	
	timer += spc_delta_time;
	if(timer >= 0.5f)
	{
		if(!last_press && cur_press)
		{
			for(i = 0; i < SPC_PROJ_COUNT; ++i)
				if(!spc_projectiles[i].enabled)
				{
					spc_projectiles[i].enabled = 1;
					spc_projectiles[i].position = spc_player_position;
					break;
				}
				
			timer = 0.0f;
		}
	
		last_press = cur_press;
	}
}

void draw_projectiles()
{
	uint8_t i;							// Loop counter
	uint16_t x_pos, y_pos;				// Position for projectiles in screen space
	vec2 proj_vel = { 0.0f, 0.0f };		// Velocity of a projectile
	proj_vel.y = -spc_delta_time * 5.0f;
	
	gfx_SetColor(4);
	for(i = 0; i < SPC_PROJ_COUNT; ++i)
	{
		// Draw and move projectile
		if(spc_projectiles[i].enabled)
		{
			spc_projectiles[i].position = vec2_add(spc_projectiles[i].position, proj_vel);
			x_pos = to_screen_space(spc_projectiles[i].position.x);
			y_pos = to_screen_space(spc_projectiles[i].position.y);
			gfx_FillRectangle(x_pos - 1, y_pos - 1, 3, 3);
			
			// Disable out of bounds projectile
			if(spc_projectiles[i].position.y < 0.0f) spc_projectiles[i].enabled = 0;
		}
	}
}

void draw_player()
{
	// Convert world space into screen space
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
	
	// gfx_SetTextXY(32, 32);
	// gfx_PrintUInt((unsigned int)timer_1_Counter, 8);
}

void draw_score()
{
	gfx_SetTextXY(16, 16);
	gfx_PrintString("Score : ");
	gfx_PrintUInt(spc_player_score, 4);
}