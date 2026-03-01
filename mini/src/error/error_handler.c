/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusto <aaugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:48:42 by aaugusto          #+#    #+#             */
/*   Updated: 2025/12/13 17:33:14 by aaugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Prints scene element range validation error messages (part 2).
 * 
 * Handles error messages for value range validations including
 * ambient ratio, brightness, FOV, color, and vector ranges.
 * 
 * @param code Error code to display message for.
 */
void	err_message_elements_ranges(int code)
{
	if (code == ERR_AMBIENT_RATIO)
		ft_putstr_fd("Element error: ambient ratio must be in \
range [0.0, 1.0]\n", 2);
	else if (code == ERR_BRIGHTNESS_RATIO)
		ft_putstr_fd("Element error: brightness ratio must be in \
range [0.0, 1.0]\n", 2);
	else if (code == ERR_FOV_RANGE)
		ft_putstr_fd("Element error: FOV must be in range [0, 180]\n", 2);
	else if (code == ERR_COLOR_RANGE)
		ft_putstr_fd("Element error: RGB values must be in \
range [0, 255]\n", 2);
	else if (code == ERR_VECTOR_RANGE)
		ft_putstr_fd("Element error: normalized vector components must be in \
range [-1.0, 1.0]\n", 2);
}

/**
 * @brief Handles errors and program cleanup.
 * 
 * Cleans up MLX resources, frees memory, and exits with appropriate code.
 * 
 * @param mini Pointer to main program structure.
 * @param code Error code (0=success, negative=normal exit, positive=error).
 * @return int Always returns 0 for success codes, exits for error/normal exit.
 */
int	ft_err_handler(t_rt *mini, int code)
{
	if (code == 0)
		return (0);
	if (mini && mini->img.mlx_img)
		mlx_destroy_image(mini->mlx_ptr, mini->img.mlx_img);
	if (mini && mini->win_ptr)
		mlx_destroy_window(mini->mlx_ptr, mini->win_ptr);
	if (mini && mini->mlx_ptr)
	{
		mlx_destroy_display(mini->mlx_ptr);
		free(mini->mlx_ptr);
	}
	gc_free_all(mini);
	if (mini)
		free(mini);
	err_message(code);
	if (code > 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
