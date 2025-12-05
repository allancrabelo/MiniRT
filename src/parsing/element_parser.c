#include "minirt.h"

int	resolution_parser(t_rt *mini, char *line)
{
	int		i;
	char	**parameters;

	i = 0;
	parameters = ft_split(line, ' ');
	if (array_size(parameters) != 3)
		return(ft_err_handler(mini, ERR_RESOLUTION_PARAM));
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

int	ambient_parser(t_rt *mini, char *line)
{
	int			i;
	char		**parameters;
	t_ambient	ambient;

	i = 0;
	parameters = ft_split(line, ' ');
	if (mini->ambient.id)
		return (ft_err_handler(mini, ERR_OVER_AMBIENTS));
	if (array_size(parameters) != 3)
		return (ft_err_handler(mini, ERR_AMBIENT_PARAM));
	ft_bzero(&ambient, sizeof(t_ambient));
	ambient.id = OBJ_AMBIENT;
	while (parameters && parameters[++i]  != NULL)
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

int	camera_parser(t_rt *mini, char *line, int i)
{
	char		**parameters;
	t_camera	camera;

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

