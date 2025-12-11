#include "minirt.h"

/**
 * @brief Calculates diffuse lighting contribution.
 * 
 * @param light Light source.
 * @param hit Intersection information.
 * @param normal Surface normal.
 * @param light_dir Direction from surface to light.
 * @return t_color Diffuse color contribution.
 */
t_color	calculate_diffuse(t_light *light, t_hit hit,
		t_vector normal, t_vector light_dir)
{
	t_color	diffuse;
	float	light_intensity;

	light_intensity = fabs(vector_dot(normal, light_dir));
	diffuse = color_mult_color(light->color, hit.object->primary_color);
	diffuse = color_mult(diffuse, light_intensity * light->brightness);
	return (diffuse);
}

/**
 * @brief Processes a single light source.
 * 
 * @param mini Main program structure.
 * @param hit Intersection information.
 * @param light Light source to process.
 * @param normal Surface normal.
 * @return t_color Light contribution from this source.
 */
t_color	process_light(t_rt *mini, t_hit hit, t_light *light,
		t_vector normal)
{
	t_vector	light_dir;

	light_dir = vector_normalize(vector_sub(light->coordinates, hit.point));
	if (is_in_shadow(mini, hit.point, light, normal))
		return ((t_color){0, 0, 0});
	return (calculate_diffuse(light, hit, normal, light_dir));
}

/**
 * @brief Ensures normal faces towards viewer.
 * 
 * @param normal Original normal.
 * @param view_dir Direction from surface to viewer.
 * @return t_vector Facing normal.
 */
t_vector	get_facing_normal(t_vector normal, t_vector view_dir)
{
	if (vector_dot(normal, view_dir) < 0)
		return (vector_mult(normal, -1));
	return (normal);
}

/**
 * @brief Calculates total lighting at intersection point.
 * 
 * @param mini Main program structure.
 * @param hit Intersection information.
 * @param ray Original ray.
 * @return t_color Total lighting color.
 */
t_color	calculate_lighting(t_rt *mini, t_hit hit, t_ray ray)
{
	t_color		result;
	t_light		*light;
	t_vector	normal;
	t_vector	view_dir;

	result = calculate_ambient(mini, hit);
	view_dir = vector_mult(ray.direction, -1);
	normal = get_facing_normal(hit.normal, view_dir);
	light = mini->light;
	while (light)
	{
		result = color_add(result, process_light(mini, hit, light, normal));
		light = light->next;
	}
	return (result);
}

/**
 * @brief Calculates color for a ray.
 * 
 * @param mini Main program structure.
 * @param ray Ray to trace.
 * @return t_color Final color for this ray.
 */
t_color	ray_color(t_rt *mini, t_ray ray)
{
	t_hit	hit;

	hit = intersect_scene(mini, ray);
	if (hit.hit)
		return (calculate_lighting(mini, hit, ray));
	return ((t_color){0.0, 0.0, 0.0});
}
