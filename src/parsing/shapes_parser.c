#include "minirt.h"

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
		if (i == 3 && colors_parser(parameters[i], &objects->primary_color, &objects->second_color))
			return (ft_err_handler(mini, ERR_INVALID_COLOR));
	}
	sphere.coordinates = objects->coordinates;
	objects->objects.sphere = sphere;
	return (EXIT_SUCCESS);
}

