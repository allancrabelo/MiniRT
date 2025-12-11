#include "minirt.h"

/**
 * @brief Routes intersection test to appropriate object type.
 * 
 * @param ray Ray to test.
 * @param obj Object to test against.
 * @return t_hit Intersection result for that object.
 */
t_hit	check_object_intersection(t_ray ray, t_obj *obj)
{
	if (obj->id == OBJ_SPHERE)
		return (intersect_sphere(ray, obj));
	else if (obj->id == OBJ_PLANE)
		return (intersect_plane(ray, obj));
	else if (obj->id == OBJ_CYLINDER)
		return (intersect_cylinder(ray, obj));
	return ((t_hit){.hit = false, .t = INFINITY});
}

/**
 * @brief Tests ray against all objects in scene.
 * 
 * @param mini Main program structure.
 * @param ray Ray to test.
 * @return t_hit Closest intersection in scene.
 */
t_hit	intersect_scene(t_rt *mini, t_ray ray)
{
	t_obj	*current;
	t_hit	closest_hit;
	t_hit	hit;

	closest_hit.hit = false;
	closest_hit.t = INFINITY;
	current = mini->objects;
	while (current)
	{
		hit = check_object_intersection(ray, current);
		if (hit.hit && hit.t < closest_hit.t)
			closest_hit = hit;
		current = current->next;
	}
	return (closest_hit);
}

/**
 * @brief Calculates ambient lighting contribution.
 * 
 * @param mini Main program structure.
 * @param hit Intersection information.
 * @return t_color Ambient color at intersection point.
 */
t_color	calculate_ambient(t_rt *mini, t_hit hit)
{
	t_color	ambient;

	ambient = color_mult_color(mini->ambient.color,
			hit.object->primary_color);
	ambient = color_mult(ambient, mini->ambient.lighting);
	return (ambient);
}

/**
 * @brief Adjusts shadow ray origin to prevent self-intersection.
 * 
 * @param point Original intersection point.
 * @param normal Surface normal.
 * @param light_dir Direction to light.
 * @return t_vector Adjusted origin point.
 */
t_vector	adjust_shadow_origin(t_vector point, t_vector normal,
		t_vector light_dir)
{
	float	bias;

	bias = EPSILON;
	if (vector_dot(normal, light_dir) < 0)
		bias = -EPSILON;
	return (vector_add(point, vector_mult(normal, bias)));
}

/**
 * @brief Checks if point is in shadow relative to a light.
 * 
 * @param mini Main program structure.
 * @param point Point to check.
 * @param light Light source.
 * @param normal Surface normal at point.
 * @return bool True if point is in shadow.
 */
bool	is_in_shadow(t_rt *mini, t_vector point, t_light *light,
		t_vector normal)
{
	t_ray		shadow_ray;
	t_hit		shadow_hit;
	t_vector	light_dir;
	float		light_dist;

	light_dir = vector_normalize(vector_sub(light->coordinates, point));
	shadow_ray.origin = adjust_shadow_origin(point, normal, light_dir);
	shadow_ray.direction = light_dir;
	shadow_hit = intersect_scene(mini, shadow_ray);
	light_dist = vector_length(vector_sub(light->coordinates, point));
	return (shadow_hit.hit && shadow_hit.t < light_dist);
}
