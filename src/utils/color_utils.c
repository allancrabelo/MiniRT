#include "minirt.h"

int	color_parser(char *str, t_color *color)
{
	int		i;
	char	**RGB;

	i = 0;
	RGB = ft_split(str, ',');
	while (RGB && RGB[i])
	{
		if (!is_ulong(RGB[i]))
			return (EXIT_FAILURE);
		i++;
	}
	if (array_size(RGB) != 3)
		return (EXIT_FAILURE);
	else
	{
		color->R = (float) ft_atoc(RGB[0]) / 255;
		color->G = (float) ft_atoc(RGB[1]) / 255;
		color->B = (float) ft_atoc(RGB[2]) / 255;
	}
	free_array(RGB);
	return (EXIT_SUCCESS);
}

