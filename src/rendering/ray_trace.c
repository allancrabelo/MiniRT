#include "minirt.h"

t_hit	intersect_scene(t_rt *mini, t_ray ray)
{
	t_obj	*current;
	t_hit	closest_hit;
	t_hit	hit;

	closest_hit.hit = false;
	closest_hit.t = INFINITY;
	closest_hit.object = NULL;
	
	current = mini->objects;
	while (current)
	{
		if (current->id == OBJ_SPHERE)
			hit = intersect_sphere(ray, current);
		else if (current->id == OBJ_PLANE)
			hit = intersect_plane(ray, current);
		else if (current->id == OBJ_CYLINDER)
			hit = intersect_cylinder(ray, current);
		else
		{
			current = current->next;
			continue;
		}
		
		if (hit.hit && hit.t < closest_hit.t)
			closest_hit = hit;
		
		current = current->next;
	}
	
	return (closest_hit);
}

static t_color	color_add(t_color a, t_color b)
{
	t_color	result;

	result.r = fmin(a.r + b.r, 1.0);
	result.g = fmin(a.g + b.g, 1.0);
	result.b = fmin(a.b + b.b, 1.0);
	return (result);
}

static t_color	color_mult(t_color c, float scalar)
{
	t_color	result;

	result.r = fmin(c.r * scalar, 1.0);
	result.g = fmin(c.g * scalar, 1.0);
	result.b = fmin(c.b * scalar, 1.0);
	return (result);
}

static t_color	color_mult_color(t_color a, t_color b)
{
	t_color	result;

	result.r = a.r * b.r;
	result.g = a.g * b.g;
	result.b = a.b * b.b;
	return (result);
}

t_color	calculate_lighting(t_rt *mini, t_hit hit, t_ray ray)
{
	t_color		ambient;
	t_color		diffuse;
	t_color		result;
	t_light		*light;
	t_vector	light_dir;
	float		light_intensity;
	t_ray		shadow_ray;
	t_hit		shadow_hit;

	ambient = color_mult_color(mini->ambient.color, hit.object->primary_color);
	ambient = color_mult(ambient, mini->ambient.lighting);
	
	result = ambient;
	light = mini->light;
	while (light)
	{
		light_dir = vector_normalize(vector_sub(light->coordinates, hit.point));
		
		shadow_ray.origin = vector_add(hit.point, vector_mult(hit.normal, 0.001));
		shadow_ray.direction = light_dir;
		shadow_hit = intersect_scene(mini, shadow_ray);
		
		if (!shadow_hit.hit || shadow_hit.t > vector_length(vector_sub(light->coordinates, hit.point)))
		{
			light_intensity = fmax(vector_dot(hit.normal, light_dir), 0.0);
			diffuse = color_mult_color(light->color, hit.object->primary_color);
			diffuse = color_mult(diffuse, light_intensity * light->brightness);
			result = color_add(result, diffuse);
		}
		
		light = light->next;
	}
	
	(void)ray;
	return (result);
}

t_color	ray_color(t_rt *mini, t_ray ray)
{
	t_hit	hit;
	t_color	bg_color;

	hit = intersect_scene(mini, ray);
	
	if (hit.hit)
		return (calculate_lighting(mini, hit, ray));
	
	bg_color.r = 0.0;
	bg_color.g = 0.0;
	bg_color.b = 0.0;
	return (bg_color);
}
