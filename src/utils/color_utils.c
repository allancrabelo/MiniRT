#include "minirt.h"

int	color_parser(char *str, t_color *color)
{
	int		i;
	int		ret;
	char	**RGB;

	i = 0;
	ret = 0;
	RGB = ft_split(str, ',');
	while (RGB && RGB[i])
	{
		if (!is_ulong(RGB[i]))
			ret = 1;
		i++;
	}
	if (array_size(RGB) != 3)
		ret = 1;
	else
	{
		color->R = (float) ft_atoc(RGB[0]) / 255;
		color->G = (float) ft_atoc(RGB[1]) / 255;
		color->B = (float) ft_atoc(RGB[2]) / 255;
	}
	free_array(RGB);
	return (ret);
}

