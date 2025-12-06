#include "minirt.h"

static int	shape_parser(t_rt *mini, char *line, t_object_type id, int nb)
{
	t_obj	*objects;
	char	**parameters;

	parameters = ft_split(line, ' ');
	if (array_size(parameters) < nb)
		return (ft_err_handler(mini, ERR_INVALID_PARAM));
	objects = object_generator(mini, id);
	if (id == OBJ_SPHERE && sphere_parser(mini, parameters, objects))
		return (EXIT_SUCCESS);
	if (id == OBJ_PLANE && plane_parser(mini, parameters, objects))
		return (EXIT_SUCCESS);
	if (id == OBJ_CYLINDER && cylinder_parser(mini, parameters, objects))
		return (EXIT_SUCCESS);
	free_array(parameters);
	return (EXIT_SUCCESS);
}

int	element_dispatcher(t_rt *mini, char *line)
{
	if (!line[0] || line[0] == '#')
		return (EXIT_SUCCESS);
	if (ft_strncmp(line, "A", 1) == 0)
		return (ambient_parser(mini, line));
	if (ft_strncmp(line, "C", 1) == 0)
		return (camera_parser(mini, line, 0));
	if (ft_strncmp(line, "R", 1) == 0)
		return (resolution_parser(mini, line));
	if (ft_strncmp(line, "L", 1) == 0)
		return (light_parser(mini, line));
	if (ft_strncmp(line, "sp", 2) == 0)
		return (shape_parser(mini, line, OBJ_SPHERE, SPHERE_PARAM));
	if (ft_strncmp(line, "pl", 2) == 0)
		return (shape_parser(mini, line, OBJ_PLANE, PLANE_PARAM));
	if (ft_strncmp(line, "cy", 2) == 0)
		return (shape_parser(mini, line, OBJ_CYLINDER, CYLINDER_PARAM));
	if (ft_strncmp(line, "obj", 3) == 0)
		return (EXIT_SUCCESS);
	return (ERR_INVALID_PARAM);
}
