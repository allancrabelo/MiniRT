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
