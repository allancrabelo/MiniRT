#include "minirt.h"

float	vector_length(t_vector vector)
{
	float	len_x;
	float	len_y;
	float	len_z;
	float	total;

	len_x = vector.X * vector.X;
	len_y = vector.Y * vector.Y;
	len_z = vector.Z * vector.Z;

	total = len_x + len_y + len_z;
	return (sqrt(total));
}