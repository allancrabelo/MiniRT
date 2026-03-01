/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusto <aaugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:46:57 by aaugusto          #+#    #+#             */
/*   Updated: 2025/12/13 16:46:58 by aaugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Frees a null-terminated array of strings.
 * 
 * @param arr Array to free.
 */
void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/**
 * @brief Calculates the size of a null-terminated array.
 * 
 * @param arr Array to measure.
 * @return int Number of elements in the array.
 */
int	array_size(char	**arr)
{
	int	size;

	size = 0;
	while (arr && arr[size])
		size++;
	return (size);
}
