#include "minirt.h"

t_color	color_add(t_color c1, t_color c2)
{
	t_color	result;

	result.r = fmin(c1.r + c2.r, 1.0);
	result.g = fmin(c1.g + c2.g, 1.0);
	result.b = fmin(c1.b + c2.b, 1.0);
	return (result);
}

t_color	color_mult(t_color c, float scalar)
{
	t_color	result;

	result.r = fmin(c.r * scalar, 1.0);
	result.g = fmin(c.g * scalar, 1.0);
	result.b = fmin(c.b * scalar, 1.0);
	return (result);
}

t_color	color_mult_color(t_color c1, t_color c2)
{
	t_color	result;

	result.r = fmin(c1.r * c2.r, 1.0);
	result.g = fmin(c1.g * c2.g, 1.0);
	result.b = fmin(c1.b * c2.b, 1.0);
	return (result);
}