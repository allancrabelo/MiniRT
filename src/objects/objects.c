#include "minirt.h"

static void	object_pusher(t_obj *object, t_obj **objs)
{
	t_obj	*tmp;

	if (!(*objs))
		*objs = object;
	else
	{
		tmp = *objs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = object;
	}
}

t_obj	*object_generator(t_rt *mini, t_object_type id)
{
	t_obj	*object;

	object = gc_calloc(mini, sizeof(t_obj));
	object->id = id;
	object->specular_intensity = DEFAULT_SPECULAR_INTENSITY;
	object->specular_exponent = DEFAULT_SPECULAR_EXPONENT;
	object->reflectivity = DEFAULT_REFLECTIVITY;
	object->refractive_index = DEFAULT_REFRACTIVE_INDEX;
	object->pattern_scale = DEFAULT_PATTERN_SCALE;
	object->pattern_type = DEFAULT_PATTERN_TYPE;
	object->has_bump = false;
	object->texture.mlx_img = NULL;
	object->has_texture = false;
	object->bump.mlx_img = NULL;
	object_pusher(object, &mini->objects);
	mini->number_of_objects++;
	return (object);
}
