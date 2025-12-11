#include "minirt.h"

/**
 * @brief Calculates intersection with cylinder cap.
 * 
 * @param ray Ray to test.
 * @param obj Cylinder object.
 * @param cap_height Height offset for cap (0 for bottom, height for top).
 * @param axis Cap normal direction.
 * @return t_hit Hit result for cap intersection.
 */
t_hit	intersect_cap(t_ray ray, t_obj *obj,
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

/**
 * @brief Initializes quadratic equation parameters for
 * cylinder body intersection.
 * 
 * @param ray Ray to test.
 * @param obj Cylinder object.
 * @param params Array to store [a, b, c] quadratic coefficients.
 */
void	init_quadratic_params(t_ray ray, t_obj *obj, float params[3])
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

/**
 * @brief Solves quadratic equation for cylinder body intersection.
 * 
 * @param params Quadratic coefficients [a, b, c].
 * @param ray Ray to test.
 * @param obj Cylinder object.
 * @param axis Cylinder axis vector.
 * @return float Valid intersection distance or INFINITY if no hit.
 */
float	solve_quadratic(float params[3], t_ray ray,
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

/**
 * @brief Calculates intersection with cylinder body.
 * 
 * @param ray Ray to test.
 * @param obj Cylinder object.
 * @return t_hit Hit result for body intersection.
 */
t_hit	cylinder_body_intersect(t_ray ray, t_obj *obj)
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

/**
 * @brief Calculates normal vector at cylinder intersection point.
 * 
 * @param hit Hit information.
 * @param obj Cylinder object.
 * @return t_vector Normal vector at intersection point.
 */
t_vector	calculate_cylinder_normal(t_hit *hit, t_obj *obj)
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
