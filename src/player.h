#ifndef SPC_PLAYER_H
#define SPC_PLAYER_H

/* Includes. */
#include "vectors.h"

/* Player projectile */
typedef struct
{
	/* Position in space. */
	vec2 position;
	
} Projectile;

/* Player position. */
extern vec2 spc_player_position;

/* Sprite. */
#define SPC_PLAYER_WIDTH 16
#define SPC_PLAYER_HEIGHT 16
extern uint8_t spc_player_sprite[2 + (SPC_PLAYER_WIDTH * SPC_PLAYER_HEIGHT)];

/* Move the player on screen. */
extern void move_player();

/* Have the player shoot. */
extern void shoot_player();

/* Draw the player on screen. */
extern void draw_player();

#endif