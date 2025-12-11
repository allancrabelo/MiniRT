#include "minirt.h"

/**
 * @brief Adds two vectors.
 * 
 * @param a First vector.
 * @param b Second vector.
 * @return t_vector Sum of the two vectors.
 */
t_vector	vector_add(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

/**
 * @brief Subtracts vector b from vector a.
 * 
 * @param a First vector.
 * @param b Second vector to subtract.
 * @return t_vector Result of a - b.
 */
t_vector	vector_sub(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

/**
 * @brief Multiplies a vector by a scalar.
 * 
 * @param v Vector to multiply.
 * @param scalar Scalar value.
 * @return t_vector Scaled vector.
 */
t_vector	vector_mult(t_vector v, float scalar)
{
	t_vector	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}

/**
 * @brief Divides a vector by a scalar.
 * 
 * @param v Vector to divide.
 * @param scalar Divisor (must not be zero).
 * @return t_vector Divided vector, or original vector if scalar is 0.
 */
t_vector	vector_div(t_vector v, float scalar)
{
	t_vector	result;

	if (scalar == 0)
		return (v);
	result.x = v.x / scalar;
	result.y = v.y / scalar;
	result.z = v.z / scalar;
	return (result);
}

/**
 * @brief Calculates dot product of two vectors.
 * 
 * @param a First vector.
 * @param b Second vector.
 * @return float Dot product.
 */
float	vector_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
