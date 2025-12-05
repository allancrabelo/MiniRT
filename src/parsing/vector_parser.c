#include "minirt.h"

int	vector_parser(char *str, t_vector *vector)
{
	char	**number;
	int		i;

	i = 0;
	number = ft_split(str, ',');
	while (number && number[i] != NULL)
	{
		if (!is_float(number[i]))
			return(EXIT_FAILURE);
		i++;
	}
	if (array_size(number) != 3)
		return (EXIT_FAILURE);
	else
	{
		vector->X = ft_atof(number[0]);
		vector->Y = ft_atof(number[1]);
		vector->Z = ft_atof(number[2]);
	}
	free_array(number);
	return (EXIT_SUCCESS);
}
