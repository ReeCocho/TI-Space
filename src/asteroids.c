/* Includes. */
#include <graphx.h>
#include <stdio.h>
#include "spc_util.h"
#include "player.h"
#include "asteroids.h"

/* Asteroid structure. */
typedef struct
{
	vec2 position; 
	float radius;
	uint8_t color;
	uint8_t enabled;
} Asteroid;

/* Max asteroid count. */
#define SPC_ASTEROID_COUNT 6

/* Asteroids. */
Asteroid spc_asteroids[SPC_ASTEROID_COUNT];

void init_asteroids()
{
	uint8_t i;
	for(i = 0; i < SPC_ASTEROID_COUNT; ++i)
		spc_asteroids[i].enabled = 0;
}

void draw_asteroids()
{
	static float timer;
	vec2 vel = { 0.0f, 0.0f };
	int x_pos, y_pos;
	uint8_t i, j;
	vec2 diff;
	vel.y = spc_delta_time * 4.0f;
	
	// Spawn asteroid
	timer += spc_delta_time;
	if(timer >= 0.6f)
	{
		for(i = 0; i < SPC_ASTEROID_COUNT; ++i)
			if(!spc_asteroids[i].enabled)
			{
				spc_asteroids[i].enabled = 1;
				spc_asteroids[i].radius = 0.3f + ((float)(random() % 50) / 100.0f);
				spc_asteroids[i].color = 6 + (uint8_t)(random() % 3);
				spc_asteroids[i].position.y = -spc_asteroids[i].radius;
				spc_asteroids[i].position.x = 	(spc_asteroids[i].radius) + 
												(((float)(random() % 64)/64.0f) * 
												((LCD_WIDTH / SPC_PPU) - spc_asteroids[i].radius));
				break;
			}
		
		timer = 0.0f;
	}
	
	// Check for collisions and move asteroid
	for(i = 0; i < SPC_ASTEROID_COUNT; ++i)
	{	
		if(spc_asteroids[i].enabled)
		{		
			// Move asteroid
			spc_asteroids[i].position = vec2_add(spc_asteroids[i].position, vel);
			
			// Draw asteroid
			gfx_SetColor(spc_asteroids[i].color);
			x_pos = (int)(spc_asteroids[i].position.x * SPC_PPU);
			y_pos = (int)(spc_asteroids[i].position.y * SPC_PPU);
			gfx_FillCircle(x_pos, y_pos, (unsigned)(SPC_PPU * spc_asteroids[i].radius));
			
			// Player collision
			if(vec2_dist(spc_asteroids[i].position, spc_player_position) <= 0.45f + (spc_asteroids[i].radius))
				spc_game_running = 0;
			
			// Check OOB
			if(spc_asteroids[i].position.y >= 10.0f + spc_asteroids[i].radius)
				spc_asteroids[i].enabled = 0;
				
			// Projectile collisions
			for(j = 0; j < SPC_PROJ_COUNT; ++j)
			{
				if(spc_projectiles[j].enabled)
				{
					if(vec2_dist(spc_projectiles[j].position, spc_asteroids[i].position) <= spc_asteroids[i].radius)
					{
						spc_projectiles[j].enabled = 0;
						spc_asteroids[i].enabled = 0;
						++spc_player_score;
					}
				}
			}
		}		
	}
}