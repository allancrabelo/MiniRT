#include "minirt.h"

t_vector	*camera_normalizer(t_vector *vector)
{
	float	normal;

	normal = 1 / vector_length(*vector);
	vector->x *= normal;
	vector->y *= normal;
	vector->z *= normal;
	return (vector);
}
