#ifndef SPC_UTIL_H
#define SPC_UTIL_H

/* Includes. */
#include <stdint.h>
#include "vectors.h"

/* Pixels per unit. */
#define SPC_SCL_FAC 2
#define SPC_PPU 32.0f

// Convert a position in world space into screen space.
extern uint16_t to_screen_space(float pos);

#endif