#include "minirt.h"

static t_hit	check_object_intersection(t_ray ray, t_obj *obj)
{
	if (obj->id == OBJ_SPHERE)
		return (intersect_sphere(ray, obj));
	else if (obj->id == OBJ_PLANE)
		return (intersect_plane(ray, obj));
	else if (obj->id == OBJ_CYLINDER)
		return (intersect_cylinder(ray, obj));
	return ((t_hit){.hit = false, .t = INFINITY});
}

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

static t_color	calculate_ambient(t_rt *mini, t_hit hit)
{
	t_color	ambient;

	ambient = color_mult_color(mini->ambient.color,
			hit.object->primary_color);
	ambient = color_mult(ambient, mini->ambient.lighting);
	return (ambient);
}

static t_vector	adjust_shadow_origin(t_vector point, t_vector normal,
		t_vector light_dir)
{
	float	bias;

	bias = EPSILON;
	if (vector_dot(normal, light_dir) < 0)
		bias = -EPSILON;
	return (vector_add(point, vector_mult(normal, bias)));
}

static bool	is_in_shadow(t_rt *mini, t_vector point, t_light *light,
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

static t_color	calculate_diffuse(t_light *light, t_hit hit,
		t_vector normal, t_vector light_dir)
{
	t_color	diffuse;
	float	light_intensity;

	light_intensity = fabs(vector_dot(normal, light_dir));
	diffuse = color_mult_color(light->color, hit.object->primary_color);
	diffuse = color_mult(diffuse, light_intensity * light->brightness);
	return (diffuse);
}

static t_color	process_light(t_rt *mini, t_hit hit, t_light *light,
		t_vector normal)
{
	t_vector	light_dir;

	light_dir = vector_normalize(vector_sub(light->coordinates, hit.point));
	if (is_in_shadow(mini, hit.point, light, normal))
		return ((t_color){0, 0, 0});
	return (calculate_diffuse(light, hit, normal, light_dir));
}

static t_vector	get_facing_normal(t_vector normal, t_vector view_dir)
{
	if (vector_dot(normal, view_dir) < 0)
		return (vector_mult(normal, -1));
	return (normal);
}

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

t_color	ray_color(t_rt *mini, t_ray ray)
{
	t_hit	hit;

	hit = intersect_scene(mini, ray);
	if (hit.hit)
		return (calculate_lighting(mini, hit, ray));
	return ((t_color){0.0, 0.0, 0.0});
}
