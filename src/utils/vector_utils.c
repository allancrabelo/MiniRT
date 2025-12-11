#include "minirt.h"

/**
 * @brief Calculates the length (magnitude) of a vector.
 * 
 * @param vector Input vector.
 * @return float Length of the vector.
 */
float	vector_length(t_vector vector)
{
	float	len_x;
	float	len_y;
	float	len_z;
	float	total;

	len_x = vector.x * vector.x;
	len_y = vector.y * vector.y;
	len_z = vector.z * vector.z;
	total = len_x + len_y + len_z;
	return (sqrt(total));
}
