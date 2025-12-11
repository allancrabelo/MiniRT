#include "minirt.h"

/**
 * @brief Creates a default miss hit result.
 * 
 * @return t_hit Miss hit structure.
 */
static t_hit	create_miss(void)
{
	t_hit	hit;

	hit.hit = false;
	hit.t = INFINITY;
	hit.object = NULL;
	return (hit);
}

/**
 * @brief Calculates intersection between ray and plane.
 * 
 * @param ray Ray to test.
 * @param obj Plane object.
 * @return t_hit Plane intersection result.
 */
t_hit	intersect_plane(t_ray ray, t_obj *obj)
{
	float		denom;
	float		t;
	t_vector	p0l0;
	t_hit		hit;

	denom = vector_dot(obj->objects.plane.orientation, ray.direction);
	if (fabs(denom) < EPSILON)
		return (create_miss());
	p0l0 = vector_sub(obj->objects.plane.coordinates, ray.origin);
	t = vector_dot(p0l0, obj->objects.plane.orientation) / denom;
	if (t < EPSILON)
		return (create_miss());
	hit.hit = true;
	hit.t = t;
	hit.point = vector_add(ray.origin, vector_mult(ray.direction, t));
	hit.normal = obj->objects.plane.orientation;
	if (vector_dot(ray.direction, hit.normal) > 0)
		hit.normal = vector_mult(hit.normal, -1);
	hit.object = obj;
	return (hit);
}

/**
 * @brief Computes quadratic equation parameters for sphere intersection.
 * 
 * @param ray Ray to test.
 * @param obj Sphere object.
 * @return t_quadratic_params Quadratic coefficients and discriminant.
 */
static t_quadratic_params	get_sphere_params(t_ray ray, t_obj *obj)
{
	t_quadratic_params	params;
	t_vector			oc;

	oc = vector_sub(ray.origin, obj->objects.sphere.coordinates);
	params.a = vector_dot(ray.direction, ray.direction);
	params.b = 2.0 * vector_dot(oc, ray.direction);
	params.c = vector_dot(oc, oc) - (obj->objects.sphere.diameter / 2.0)
		* (obj->objects.sphere.diameter / 2.0);
	params.discriminant = params.b * params.b - 4 * params.a * params.c;
	return (params);
}

/**
 * @brief Creates hit information from sphere intersection.
 * 
 * @param ray Ray that intersected.
 * @param t Intersection distance.
 * @param obj Sphere object.
 * @return t_hit Complete hit information.
 */
static t_hit	calculate_hit_info(t_ray ray, float t, t_obj *obj)
{
	t_hit	hit;

	hit.hit = true;
	hit.t = t;
	hit.point = vector_add(ray.origin, vector_mult(ray.direction, t));
	hit.normal = vector_normalize(vector_sub(hit.point,
				obj->objects.sphere.coordinates));
	if (vector_dot(hit.normal, ray.direction) > 0)
		hit.normal = vector_mult(hit.normal, -1);
	hit.object = obj;
	return (hit);
}

/**
 * @brief Calculates intersection between ray and sphere.
 * 
 * @param ray Ray to test.
 * @param obj Sphere object.
 * @return t_hit Sphere intersection result.
 */
t_hit	intersect_sphere(t_ray ray, t_obj *obj)
{
	t_quadratic_params	params;
	float				t;

	params = get_sphere_params(ray, obj);
	if (params.discriminant < 0)
		return (create_miss());
	t = (-params.b - sqrt(params.discriminant)) / (2.0 * params.a);
	if (t < EPSILON)
		t = (-params.b + sqrt(params.discriminant)) / (2.0 * params.a);
	if (t < EPSILON)
		return (create_miss());
	return (calculate_hit_info(ray, t, obj));
}
