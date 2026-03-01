/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusto <aaugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:00:00 by aaugusto          #+#    #+#             */
/*   Updated: 2025/12/13 17:00:01 by aaugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Validates ratio is in range [0.0, 1.0].
 * 
 * @param ratio The ratio value to validate.
 * @return int SUCCESS if valid, FAILURE otherwise.
 */
int	validate_ratio(float ratio)
{
	if (ratio < 0.0 || ratio > 1.0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief Validates FOV is in range [0, 180].
 * 
 * @param fov The field of view value to validate.
 * @return int SUCCESS if valid, FAILURE otherwise.
 */
int	validate_fov(size_t fov)
{
	if (fov < 0 || fov > 180)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief Validates RGB color component is in range [0, 255].
 * 
 * @param value The color component value to validate.
 * @return int SUCCESS if valid, FAILURE otherwise.
 */
int	validate_color_component(int value)
{
	if (value < 0 || value > 255)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief Validates vector component is in range [-1.0, 1.0].
 * 
 * @param value The vector component to validate.
 * @return int SUCCESS if valid, FAILURE otherwise.
 */
int	validate_normalized_component(float value)
{
	if (value < -1.0 || value > 1.0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief Validates all components of normalized vector are in [-1.0, 1.0].
 * 
 * @param vec The vector to validate.
 * @return int SUCCESS if valid, FAILURE otherwise.
 */
int	validate_normalized_vector(t_vector vec)
{
	if (validate_normalized_component(vec.x))
		return (EXIT_FAILURE);
	if (validate_normalized_component(vec.y))
		return (EXIT_FAILURE);
	if (validate_normalized_component(vec.z))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
