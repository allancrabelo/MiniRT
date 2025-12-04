#include "minirt.h"

int	resolution_parser(t_rt *mini, char *line)
{
	int		i;
	char	**parameters;

	i = 0;
	parameters = ft_split(line, ' ');
	if (array_size(parameters) != 3)
		return(ft_err_handler(mini, ERR_RESOLUTION_PARAM));
	while (parameters && parameters[++i])
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
	while (parameters && parameters[++i])
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
