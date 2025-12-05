#include "minirt.h"

int	is_ulong(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i])
	{
		if (ft_isdigit(str[i]) != 1)
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

int	is_float(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_isdigit(str[i]) != 1 && str[i] != '-' && str[i] != '.')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

int	float_parser(char *str, float *num)
{
	if (!is_float(str))
		return (EXIT_FAILURE);
	*num = ft_atof(str);
	return (EXIT_SUCCESS);
}

int	ulong_parser(char *str, size_t *num)
{
	if (!is_ulong(str))
		return (EXIT_FAILURE);
	*num = (size_t)ft_atoi(str);
	return (EXIT_SUCCESS);
}
