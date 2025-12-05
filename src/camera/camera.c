#include "minirt.h"

t_vector	*camera_normalizer(t_vector *vector)
{
	float	normal;

	normal = 1 / vector_length(*vector);
	vector->X *= normal;
	vector->Y *= normal;
	vector->Z *= normal;
	return (vector);
}
