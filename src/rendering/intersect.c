#include "minirt.h"

static t_hit	create_miss(void)
{
	t_hit	hit;

	hit.hit = false;
	hit.t = INFINITY;
	hit.object = NULL;
	return (hit);
}

t_hit	intersect_sphere(t_ray ray, t_obj *obj)
{
	t_vector	oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	float		t;
	t_hit		hit;

	oc = vector_sub(ray.origin, obj->objects.sphere.coordinates);
	a = vector_dot(ray.direction, ray.direction);
	b = 2.0 * vector_dot(oc, ray.direction);
	c = vector_dot(oc, oc) - (obj->objects.sphere.diameter / 2.0) 
		* (obj->objects.sphere.diameter / 2.0);
	discriminant = b * b - 4 * a * c;
	
	if (discriminant < 0)
		return (create_miss());
	
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t < 0.001)
		t = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t < 0.001)
		return (create_miss());
	
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

t_hit	intersect_plane(t_ray ray, t_obj *obj)
{
	float		denom;
	float		t;
	t_vector	p0l0;
	t_hit		hit;

	denom = vector_dot(obj->objects.plane.orientation, ray.direction);
	if (fabs(denom) < 0.0001)
		return (create_miss());
	
	p0l0 = vector_sub(obj->objects.plane.coordinates, ray.origin);
	t = vector_dot(p0l0, obj->objects.plane.orientation) / denom;
	
	if (t < 0.001)
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
