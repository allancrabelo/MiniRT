#include "minirt.h"

/**
 * @brief Parses resolution parameters from configuration.
 * 
 * Processes window resolution: width and height.
 * 
 * @param mini Pointer to main program structure.
 * @param line Configuration line containing resolution parameters.
 * @return int SUCCESS if resolution parsed correctly, error code otherwise.
 */
int	resolution_parser(t_rt *mini, char *line)
{
	int		i;
	char	**parameters;

	i = 0;
	parameters = ft_split(line, ' ');
	if (array_size(parameters) != 3)
		return (ft_err_handler(mini, ERR_RESOLUTION_PARAM));
	while (parameters && parameters[++i] != NULL)
	{
		mini->parameter_nbr = i;
		if (i == 1 && float_parser(parameters[i], &mini->width))
			return (ft_err_handler(mini, ERR_NOT_FLOAT));
		if (i == 2 && float_parser(parameters[i], &mini->height))
			return (ft_err_handler(mini, ERR_NOT_FLOAT));
	}
	free_array(parameters);
	return (EXIT_SUCCESS);
}

/**
 * @brief Parses ambient lighting parameters from configuration.
 * 
 * Processes ambient parameters: lighting ratio and color.
 * Validates that only one ambient light exists.
 * 
 * @param mini Pointer to main program structure.
 * @param line Configuration line containing ambient parameters.
 * @return int SUCCESS if ambient parsed correctly, error code otherwise.
 */
int	ambient_parser(t_rt *mini, char *line)
{
	t_ambient	ambient;
	int			i;
	char		**parameters;

	i = 0;
	parameters = ft_split(line, ' ');
	if (mini->ambient.id)
		return (ft_err_handler(mini, ERR_OVER_AMBIENTS));
	if (array_size(parameters) != 3)
		return (ft_err_handler(mini, ERR_AMBIENT_PARAM));
	ft_bzero(&ambient, sizeof(t_ambient));
	ambient.id = OBJ_AMBIENT;
	while (parameters && parameters[++i] != NULL)
	{
		mini->parameter_nbr = i;
		if (i == 1 && float_parser(parameters[i], &ambient.lighting))
			return (ft_err_handler(mini, ERR_NOT_FLOAT));
		if (i == 2 && color_parser(parameters[i], &ambient.color))
			return (ft_err_handler(mini, ERR_NOT_FLOAT));
	}
	mini->ambient = ambient;
	free_array(parameters);
	return (EXIT_SUCCESS);
}

/**
 * @brief Parses camera parameters from configuration.
 * 
 * Processes camera parameters: coordinates, orientation, and field of view.
 * Validates that only one camera exists and normalizes orientation vector.
 * 
 * @param mini Pointer to main program structure.
 * @param line Configuration line containing camera parameters.
 * @param i Starting index for parameter processing.
 * @return int SUCCESS if camera parsed correctly, error code otherwise.
 */
int	camera_parser(t_rt *mini, char *line, int i)
{
	t_camera	camera;
	char		**parameters;

	parameters = ft_split(line, ' ');
	if (mini->camera.id)
		return (ft_err_handler(mini, ERR_OVER_CAMERAS));
	if (array_size(parameters) != 4)
		return (ft_err_handler(mini, ERR_CAMERA_PARAM));
	ft_bzero(&camera, sizeof(t_camera));
	camera.id = OBJ_CAMERA;
	while (parameters && parameters[i] != NULL)
	{
		mini->parameter_nbr = i;
		if (i == 1 && vector_parser(parameters[i], &camera.coordinates))
			return (ft_err_handler(mini, ERR_INVALID_COORD));
		if (i == 2 && vector_parser(parameters[i], &camera.orientation))
			return (ft_err_handler(mini, ERR_INVALID_ORIENT));
		if (i == 3 && ulong_parser(parameters[i], &camera.fov))
			return (ft_err_handler(mini, ERR_NOT_ULONG));
		i++;
	}
	camera_normalizer(&camera.orientation);
	mini->camera = camera;
	free_array(parameters);
	return (EXIT_SUCCESS);
}

/**
 * @brief Parses light parameters from configuration.
 * 
 * Processes light parameters: coordinates, brightness, and color.
 * Creates a light object and validates all parameters.
 * 
 * @param mini Pointer to main program structure.
 * @param line Configuration line containing light parameters.
 * @return int SUCCESS if light parsed correctly, error code otherwise.
 */
int	light_parser(t_rt *mini, char *line)
{
	t_light		*light;
	char		**parameters;
	int			i;

	i = 0;
	parameters = ft_split(line, ' ');
	if (array_size(parameters) != 4)
		return (ft_err_handler(mini, ERR_LIGHT_PARAM));
	light = light_generator(mini);
	while (parameters && parameters[++i] != NULL)
	{
		mini->parameter_nbr = i;
		if (i == 1 && vector_parser(parameters[i], &light->coordinates))
			return (ft_err_handler(mini, ERR_INVALID_COORD));
		if (i == 2 && float_parser(parameters[i], &light->brightness))
			return (ft_err_handler(mini, ERR_NOT_FLOAT));
		if (i == 3 && color_parser(parameters[i], &light->color))
			return (ft_err_handler(mini, ERR_INVALID_COLOR));
	}
	free_array(parameters);
	return (EXIT_SUCCESS);
}
