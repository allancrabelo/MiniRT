#include "minirt.h"

/**
 * @brief Computes final normal vector for cylinder intersection.
 * 
 * Handles both body and cap normals, ensuring normal points away from surface.
 * 
 * @param hit Hit information to update.
 * @param ray Ray that caused the intersection.
 * @param obj Cylinder object.
 */
void	compute_cylinder_normal(t_hit *hit, t_ray ray, t_obj *obj)
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

/**
 * @brief Main cylinder intersection function.
 * 
 * Tests intersection with cylinder body and both caps,
 * returns closest valid intersection.
 * 
 * @param ray Ray to test.
 * @param obj Cylinder object.
 * @return t_hit Closest cylinder intersection.
 */
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

/**
 * @brief Checks if intersection point is within cap radius.
 * 
 * @param ray Ray being tested.
 * @param obj Cylinder object.
 * @param cap_center Center point of the cap.
 * @param t Intersection distance.
 * @return bool True if point is within cap radius.
 */
bool	check_cap_distance(t_ray ray, t_obj *obj,
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
