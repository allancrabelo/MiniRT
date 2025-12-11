#include "minirt.h"

/**
 * @brief Calculates cross product of two vectors.
 * 
 * @param a First vector.
 * @param b Second vector.
 * @return t_vector Cross product vector.
 */
t_vector	vector_cross(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

/**
 * @brief Normalizes a vector to unit length.
 * 
 * @param v Vector to normalize.
 * @return t_vector Normalized vector, or original if length is zero.
 */
t_vector	vector_normalize(t_vector v)
{
	float		len;
	t_vector	result;

	len = vector_length(v);
	if (len == 0)
		return (v);
	result.x = v.x / len;
	result.y = v.y / len;
	result.z = v.z / len;
	return (result);
}
