#ifndef TIP_VECTORS_H
#define TIP_VECTORS_H

/* Vector structure. */
typedef struct
{
	float x, y;
} vec2;

/* Operations. */
extern vec2 vec2_add(vec2 v1, vec2 v2);
extern vec2 vec2_sub(vec2 v1, vec2 v2);
extern vec2 vec2_mul(vec2 v1, vec2 v2);
extern vec2 vec2_div(vec2 v1, vec2 v2);
extern float vec2_dot(vec2 v1, vec2 v2);
extern float vec2_mag(vec2 v);
extern vec2 vec2_norm(vec2 v);
extern vec2 vec2_scl(vec2 v, float s);
extern float vec2_ang(vec2 v1, vec2 v2);

#endif