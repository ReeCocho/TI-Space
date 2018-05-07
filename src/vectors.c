/* Includes. */
#include <math.h>
#include "vectors.h"

vec2 vec2_add(vec2 v1, vec2 v2)
{
	vec2 new_vec;
	new_vec.x = v1.x + v2.x;
	new_vec.y = v1.y + v2.y;
	return new_vec;
}

vec2 vec2_sub(vec2 v1, vec2 v2)
{
	vec2 new_vec;
	new_vec.x = v1.x - v2.x;
	new_vec.y = v1.y - v2.y;
	return new_vec;
}

vec2 vec2_mul(vec2 v1, vec2 v2)
{
	vec2 new_vec;
	new_vec.x = v1.x * v2.x;
	new_vec.y = v1.y * v2.y;
	return new_vec;
}

vec2 vec2_div(vec2 v1, vec2 v2)
{
	vec2 new_vec;
	new_vec.x = v1.x / v2.x;
	new_vec.y = v1.y / v2.y;
	return new_vec;
}

float vec2_dot(vec2 v1, vec2 v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}

float vec2_mag(vec2 v)
{
	return sqrt(vec2_dot(v, v));
}

float vec2_dist(vec2 v1, vec2 v2)
{
	return vec2_mag(vec2_sub(v1, v2));
}

vec2 vec2_norm(vec2 v)
{
	return vec2_scl(v, 1.0f/vec2_mag(v));
}

vec2 vec2_scl(vec2 v, float s)
{
	vec2 new_vec;
	new_vec.x = v.x * s;
	new_vec.y = v.y * s;
	return new_vec;
}

float vec2_ang(vec2 v1, vec2 v2)
{
	float m1 = vec2_mag(v1);
	float m2 = vec2_mag(v2);
	float d = vec2_dot(v1, v2);
	return acos(d/(m1 * m2));
}