#include "minirt.h"

/**
 * @brief Parses color string(s) for objects with optional secondary colors.
 * 
 * Supports single color or primary;secondary color format.
 * 
 * @param str Color string(s) to parse.
 * @param primary_color Primary color structure to populate.
 * @param second_color Secondary color structure to populate (optional).
 * @return int SUCCESS if parsing succeeds, FAILURE if format is invalid.
 */
int	colors_parser(char *str, t_color *primary_color, t_color *second_color)
{
	char	**colors;
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	colors = ft_split(str, ';');
	if (array_size(colors) < 1)
		return (free_array(colors), EXIT_FAILURE);
	while (colors && colors[i])
	{
		if (i == 0)
			ret = color_parser(colors[0], primary_color);
		if (i == 1)
			ret = color_parser(colors[1], second_color);
		i++;
	}
	free_array(colors);
	return (ret);
}

/**
 * @brief Parses a single RGB color string.
 * 
 * Converts "R,G,B" string to normalized color values (0-1 range).
 * 
 * @param str RGB color string in format "255,255,255".
 * @param color Color structure to populate.
 * @return int SUCCESS if parsing succeeds, FAILURE if format is invalid.
 */
int	color_parser(char *str, t_color *color)
{
	int		i;
	char	**rgb;

	i = 0;
	rgb = ft_split(str, ',');
	while (rgb && rgb[i])
	{
		if (!is_ulong(rgb[i]))
			return (free_array(rgb), EXIT_FAILURE);
		i++;
	}
	if (array_size(rgb) != 3)
		return (free_array(rgb), EXIT_FAILURE);
	else
	{
		color->r = (float) ft_atoc(rgb[0]) / 255;
		color->g = (float) ft_atoc(rgb[1]) / 255;
		color->b = (float) ft_atoc(rgb[2]) / 255;
	}
	free_array(rgb);
	return (EXIT_SUCCESS);
}
