#include "minirt.h"

/**
 * @brief Adds a light to the end of the light linked list.
 * 
 * Traverses the light list and appends the new light at the end.
 * 
 * @param new_light Light to add to the list.
 * @param light Pointer to the head of the light list.
 */
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

/**
 * @brief Creates and initializes a new light structure.
 * 
 * Allocates memory for a light source and adds it to the scene's light list.
 * 
 * @param mini Pointer to main program structure.
 * @return t_light* Pointer to the newly created light.
 */
t_light	*light_generator(t_rt *mini)
{
	t_light	*light;

	light = gc_calloc(mini, sizeof(t_light));
	if (!light)
		return (0);
	light->id = OBJ_LIGHT;
	light_pusher(light, &mini->light);
	return (light);
}
