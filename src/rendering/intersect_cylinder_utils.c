#include "minirt.h"

/**
 * @brief Creates a default "miss" hit result.
 * 
 * @return t_hit Hit structure with hit=false and t=INFINITY.
 */
t_hit	create_miss_hit(void)
{
	t_hit	hit;

	hit.hit = false;
	hit.t = INFINITY;
	hit.normal = (t_vector){0, 0, 0};
	return (hit);
}

/**
 * @brief Gets cylinder radius from diameter.
 * 
 * @param obj Cylinder object.
 * @return float Radius of the cylinder.
 */
float	get_radius(t_obj *obj)
{
	return (obj->objects.cylinder.diameter / 2.0);
}

/**
 * @brief Checks if intersection distance is valid.
 * 
 * @param t Intersection distance.
 * @return bool True if t is positive and above epsilon.
 */
bool	is_valid_t(float t)
{
	return (t >= EPSILON);
}

/**
 * @brief Checks if cylinder intersection is within height bounds.
 * 
 * @param ray Ray being tested.
 * @param obj Cylinder object.
 * @param t Intersection distance.
 * @param normal Cylinder axis vector.
 * @return bool True if intersection is within cylinder height.
 */
bool	check_cylinder_caps(t_ray ray, t_obj *obj,
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

/**
 * @brief Creates a hit result for cylinder cap intersection.
 * 
 * @param ray Ray that hit the cap.
 * @param obj Cylinder object.
 * @param t Intersection distance.
 * @param axis Cap normal axis.
 * @return t_hit Hit structure for cap intersection.
 */
t_hit	create_cap_hit(t_ray ray, t_obj *obj, float t, t_vector axis)
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
