/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusto <aaugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:46:49 by aaugusto          #+#    #+#             */
/*   Updated: 2025/12/13 16:46:50 by aaugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
