#include "minirt.h"

static void	light_pusher(t_light *new_light, t_light **light)
{
	t_light	*tmp;

	if (!(*light))
		*light = new_light;
	else
	{
		tmp = *light;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_light;
	}
}

t_light	*light_generator(t_rt *mini)
{
	t_light	*light;

	light = ft_calloc(sizeof(t_light), 1);
	if (!light)
		return (0);
	light->id = OBJ_LIGHT;
	light_pusher(light, &mini->light);
	return (light);
}
