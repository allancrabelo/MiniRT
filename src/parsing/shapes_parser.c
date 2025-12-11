#include "minirt.h"

/**
 * @brief Parses sphere parameters and populates object data.
 * 
 * Processes sphere parameters from configuration file:
 * coordinates, diameter, and colors.
 * Validates each parameter and stores in object structure.
 * 
 * @param mini Pointer to main program structure for error handling.
 * @param parameters Array of sphere parameter strings.
 * @param objects Pointer to object structure to populate with sphere data.
 * @return int SUCCESS if all parameters are valid, error code otherwise.
 */
int	sphere_parser(t_rt *mini, char **parameters, t_obj *objects)
{
	t_sphere	sphere;
	int			i;

	i = 0;
	ft_bzero(&sphere, sizeof(t_sphere));
	while (parameters && parameters[++i])
	{
		mini->parameter_nbr = i;
		if (i == 1 && vector_parser(parameters[i], &objects->coordinates))
			return (ft_err_handler(mini, ERR_INVALID_COORD));
		if (i == 2 && float_parser(parameters[i], &sphere.diameter))
			return (ft_err_handler(mini, ERR_NOT_FLOAT));
		if (i == 3 && colors_parser(parameters[i],
				&objects->primary_color, &objects->second_color))
			return (ft_err_handler(mini, ERR_INVALID_COLOR));
	}
	sphere.coordinates = objects->coordinates;
	objects->objects.sphere = sphere;
	return (EXIT_SUCCESS);
}

/**
 * @brief Parses plane parameters and populates object data.
 * 
 * Processes plane parameters from configuration file:
 * coordinates, orientation, and colors.
 * Validates each parameter and normalizes orientation vector.
 * 
 * @param mini Pointer to main program structure for error handling.
 * @param parameters Array of plane parameter strings.
 * @param objects Pointer to object structure to populate with plane data.
 * @return int SUCCESS if all parameters are valid, error code otherwise.
 */
int	plane_parser(t_rt *mini, char **parameters, t_obj *objects)
{
	t_plane		plane;
	int			i;

	i = 0;
	ft_bzero(&plane, sizeof(t_plane));
	while (parameters && parameters[++i])
	{
		mini->parameter_nbr = i;
		if (i == 1 && vector_parser(parameters[i], &objects->coordinates))
			return (ft_err_handler(mini, ERR_INVALID_COORD));
		if (i == 2 && vector_parser(parameters[i], &plane.orientation))
			return (ft_err_handler(mini, ERR_INVALID_ORIENT));
		if (i == 3 && colors_parser(parameters[i],
				&objects->primary_color, &objects->second_color))
			return (ft_err_handler(mini, ERR_INVALID_COLOR));
	}
	plane.coordinates = objects->coordinates;
	camera_normalizer(&plane.orientation);
	objects->objects.plane = plane;
	return (EXIT_SUCCESS);
}

/**
 * @brief Parses cylinder parameters and populates object data.
 * 
 * Processes cylinder parameters from configuration file:
 * coordinates, orientation, diameter, height, and colors.
 * Validates each parameter and normalizes orientation vector.
 * 
 * @param mini Pointer to main program structure for error handling.
 * @param parameters Array of cylinder parameter strings.
 * @param objects Pointer to object structure to populate with cylinder data.
 * @return int SUCCESS if all parameters are valid, error code otherwise.
 */
int	cylinder_parser(t_rt *mini, char **parameters, t_obj *objects)
{
	t_cylinder	cylinder;
	int			i;

	i = 0;
	ft_bzero(&cylinder, sizeof(t_cylinder));
	while (parameters && parameters[++i])
	{
		mini->parameter_nbr = i;
		if (i == 1 && vector_parser(parameters[i], &objects->coordinates))
			return (ft_err_handler(mini, ERR_INVALID_COORD));
		if (i == 2 && vector_parser(parameters[i], &cylinder.orientation))
			return (ft_err_handler(mini, ERR_INVALID_ORIENT));
		if (i == 3 && float_parser(parameters[i], &cylinder.diameter))
			return (ft_err_handler(mini, ERR_NOT_FLOAT));
		if (i == 4 && float_parser(parameters[i], &cylinder.height))
			return (ft_err_handler(mini, ERR_NOT_FLOAT));
		if (i == 5 && colors_parser(parameters[i],
				&objects->primary_color, &objects->second_color))
			return (ft_err_handler(mini, ERR_INVALID_COLOR));
	}
	cylinder.coordinates = objects->coordinates;
	camera_normalizer(&cylinder.orientation);
	objects->objects.cylinder = cylinder;
	return (EXIT_SUCCESS);
}
