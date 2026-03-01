/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusto <aaugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:46:48 by aaugusto          #+#    #+#             */
/*   Updated: 2025/12/13 16:46:49 by aaugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Normalizes a camera orientation vector.
 * 
 * Scales the vector to unit length (magnitude 1).
 * 
 * @param vector Pointer to vector to normalize.
 * @return t_vector* Pointer to the normalized vector (same as input).
 */
t_vector	*camera_normalizer(t_vector *vector)
{
	float	normal;

	normal = 1 / vector_length(*vector);
	vector->x *= normal;
	vector->y *= normal;
	vector->z *= normal;
	return (vector);
}
