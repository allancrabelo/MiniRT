#include "minirt.h"

static t_hit	create_miss_hit(void)
{
	t_hit	hit;

	hit.hit = false;
	hit.t = INFINITY;
	hit.normal = (t_vector){0, 0, 0};
	return (hit);
}

static float	get_radius(t_obj *obj)
{
	return (obj->objects.cylinder.diameter / 2.0);
}

static bool	is_valid_t(float t)
{
	return (t >= EPSILON);
}

static bool	check_cylinder_caps(t_ray ray, t_obj *obj,
		float t, t_vector normal)
{
	t_vector	point;
	t_vector	d;
	float		dist;

	point = vector_add(ray.origin, vector_mult(ray.direction, t));
	d = vector_sub(point, obj->objects.cylinder.coordinates);
	dist = vector_dot(d, normal);
	if (dist < 0 || dist > obj->objects.cylinder.height)
		return (false);
	return (true);
}

static t_hit	create_cap_hit(t_ray ray, t_obj *obj, float t, t_vector axis)
{
	t_hit	hit;
	float	denom;

	hit.hit = true;
	hit.t = t;
	hit.point = vector_add(ray.origin, vector_mult(ray.direction, t));
	hit.object = obj;
	hit.normal = axis;
	denom = vector_dot(axis, ray.direction);
	if (denom > 0)
		hit.normal = vector_mult(axis, -1);
	return (hit);
}

static bool	check_cap_distance(t_ray ray, t_obj *obj,
		t_vector cap_center, float t)
{
	t_vector	p;
	t_vector	v;
	float		dist_sq;
	float		radius_sq;

	p = vector_add(ray.origin, vector_mult(ray.direction, t));
	v = vector_sub(p, cap_center);
	dist_sq = vector_dot(v, v);
	radius_sq = get_radius(obj) * get_radius(obj);
	return (dist_sq <= radius_sq + EPSILON_SMALL);
}

static t_hit	intersect_cap(t_ray ray, t_obj *obj,
		float cap_height, t_vector axis)
{
	t_vector	cap_center;
	float		denom;
	float		t;

	cap_center = vector_add(obj->objects.cylinder.coordinates,
			vector_mult(axis, cap_height));
	denom = vector_dot(axis, ray.direction);
	if (fabs(denom) < EPSILON_TINY)
		return (create_miss_hit());
	t = vector_dot(vector_sub(cap_center, ray.origin), axis) / denom;
	if (!is_valid_t(t))
		return (create_miss_hit());
	if (!check_cap_distance(ray, obj, cap_center, t))
		return (create_miss_hit());
	return (create_cap_hit(ray, obj, t, axis));
}

static void	init_quadratic_params(t_ray ray, t_obj *obj, float params[3])
{
	t_vector	oc;
	t_vector	axis;
	float		radius;

	axis = obj->objects.cylinder.orientation;
	radius = get_radius(obj);
	oc = vector_sub(ray.origin, obj->objects.cylinder.coordinates);
	params[0] = vector_dot(ray.direction, ray.direction)
		- pow(vector_dot(ray.direction, axis), 2);
	params[1] = 2 * (vector_dot(ray.direction, oc)
			- vector_dot(ray.direction, axis) * vector_dot(oc, axis));
	params[2] = vector_dot(oc, oc) - pow(vector_dot(oc, axis), 2)
		- radius * radius;
}

static float	solve_quadratic(float params[3], t_ray ray,
		t_obj *obj, t_vector axis)
{
	float	discriminant;
	float	t;

	discriminant = params[1] * params[1] - 4 * params[0] * params[2];
	if (discriminant < 0)
		return (INFINITY);
	t = (-params[1] - sqrt(discriminant)) / (2.0 * params[0]);
	if (is_valid_t(t) && check_cylinder_caps(ray, obj, t, axis))
		return (t);
	t = (-params[1] + sqrt(discriminant)) / (2.0 * params[0]);
	if (is_valid_t(t) && check_cylinder_caps(ray, obj, t, axis))
		return (t);
	return (INFINITY);
}

static t_hit	cylinder_body_intersect(t_ray ray, t_obj *obj)
{
	float		params[3];
	float		t;
	t_vector	axis;
	t_hit		hit;

	axis = obj->objects.cylinder.orientation;
	init_quadratic_params(ray, obj, params);
	t = solve_quadratic(params, ray, obj, axis);
	if (t == INFINITY)
		return (create_miss_hit());
	hit.hit = true;
	hit.t = t;
	hit.point = vector_add(ray.origin, vector_mult(ray.direction, t));
	hit.object = obj;
	hit.normal = (t_vector){0, 0, 0};
	return (hit);
}

static t_vector	calculate_cylinder_normal(t_hit *hit, t_obj *obj)
{
	t_vector	d;
	t_vector	axis_proj;
	t_vector	normal;

	d = vector_sub(hit->point, obj->objects.cylinder.coordinates);
	axis_proj = vector_mult(obj->objects.cylinder.orientation,
			vector_dot(d, obj->objects.cylinder.orientation));
	normal = vector_normalize(vector_sub(d, axis_proj));
	return (normal);
}

static void	compute_cylinder_normal(t_hit *hit, t_ray ray, t_obj *obj)
{
	t_vector	axis;

	if (hit->normal.x != 0 || hit->normal.y != 0 || hit->normal.z != 0)
	{
		axis = obj->objects.cylinder.orientation;
		if (fabs(vector_dot(hit->normal, axis)) > 0.99)
			return ;
	}
	hit->normal = calculate_cylinder_normal(hit, obj);
	if (vector_dot(hit->normal, ray.direction) > 0)
		hit->normal = vector_mult(hit->normal, -1);
}

t_hit	intersect_cylinder(t_ray ray, t_obj *obj)
{
	t_hit		hit;
	t_hit		cap_hit;
	t_vector	axis;

	axis = obj->objects.cylinder.orientation;
	hit = cylinder_body_intersect(ray, obj);
	cap_hit = intersect_cap(ray, obj, 0, axis);
	if (cap_hit.hit && cap_hit.t < hit.t)
		hit = cap_hit;
	cap_hit = intersect_cap(ray, obj, obj->objects.cylinder.height, axis);
	if (cap_hit.hit && cap_hit.t < hit.t)
		hit = cap_hit;
	if (!hit.hit)
		return (hit);
	compute_cylinder_normal(&hit, ray, obj);
	return (hit);
}
