#include "minirt.h"

int	element_dispatcher(t_rt *mini, char *line)
{
	if (ft_strncmp(line, "R", 1) == 0)
		return (resolution_parser(mini, line));
	if (ft_strncmp(line, "A", 1) == 0)
		return (ambient_parser(mini, line));
	if (ft_strncmp(line, "C", 1) == 0)
		return (camera_parser(mini, line, 0));
	return (EXIT_SUCCESS);
}