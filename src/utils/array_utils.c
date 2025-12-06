#include "minirt.h"

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

int	array_size(char	**arr)
{
	int	size;

	size = 0;
	while (arr && arr[size])
		size++;
	return (size);
}