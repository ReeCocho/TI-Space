#ifndef SPC_PLAYER_H
#define SPC_PLAYER_H

/* Includes. */
#include <tice.h>
#include "vectors.h"

/* Player projectile */
typedef struct
{
	/* Position in space. */
	vec2 position;
	
	/* Is the projectile enabled? */
	uint8_t enabled;
	
} Projectile;

/* Projectile count. */
#define SPC_PROJ_COUNT 4

/* Projectile buffer. */
extern Projectile spc_projectiles[SPC_PROJ_COUNT];

/* Position in world space. */
extern vec2 spc_player_position;

/* Player score. */
extern unsigned int spc_player_score;

/* Initialize player. */
extern void init_player();

/* Move the player on screen. */
extern void move_player();

/* Have the player shoot. */
extern void shoot_player();

/* Draw projectiles on screen. */
extern void draw_projectiles();

/* Draw the player on screen. */
extern void draw_player();

/* Draw the score counter. */
extern void draw_score();

#endif