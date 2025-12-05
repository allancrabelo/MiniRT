#include "minirt.h"

int	color_parser(char *str, t_color *color)
{
	int		i;
	char	**rgb;

	i = 0;
	rgb = ft_split(str, ',');
	while (rgb && rgb[i])
	{
		if (!is_ulong(rgb[i]))
			return (EXIT_FAILURE);
		i++;
	}
	if (array_size(rgb) != 3)
		return (EXIT_FAILURE);
	else
	{
		color->r = (float) ft_atoc(rgb[0]) / 255;
		color->g = (float) ft_atoc(rgb[1]) / 255;
		color->b = (float) ft_atoc(rgb[2]) / 255;
	}
	free_array(rgb);
	return (EXIT_SUCCESS);
}
