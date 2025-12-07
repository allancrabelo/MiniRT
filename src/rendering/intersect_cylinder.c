#include "minirt.h"

static bool	check_cylinder_caps(t_ray ray, t_obj *obj, float t, t_vector normal)
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

static t_hit	intersect_cap(t_ray ray, t_obj *obj, float cap_height, t_vector axis)
{
	t_vector	cap_center;
	float		denom;
	float		t;
	t_vector	p;
	t_vector	v;
	float		dist_sq;
	float		radius;
	t_hit		hit;

	cap_center = vector_add(obj->objects.cylinder.coordinates, 
		vector_mult(axis, cap_height));
	denom = vector_dot(axis, ray.direction);
	
	if (fabs(denom) < 1e-8)
		return ((t_hit){.hit = false, .t = INFINITY});
	
	t = vector_dot(vector_sub(cap_center, ray.origin), axis) / denom;
	
	if (t < 0.001)
		return ((t_hit){.hit = false, .t = INFINITY});
	
	p = vector_add(ray.origin, vector_mult(ray.direction, t));
	v = vector_sub(p, cap_center);
	radius = obj->objects.cylinder.diameter / 2.0;
	dist_sq = vector_dot(v, v);
	
	if (dist_sq > radius * radius + 1e-6)
		return ((t_hit){.hit = false, .t = INFINITY});
	
	hit.hit = true;
	hit.t = t;
	hit.point = p;
	hit.object = obj;
	hit.normal = axis;
	if (denom > 0)
		hit.normal = vector_mult(axis, -1);
	return (hit);
}

static t_hit	cylinder_body_intersect(t_ray ray, t_obj *obj)
{
	t_vector	oc;
	t_vector	axis;
	float		radius;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	float		t;
	t_hit		hit;

	axis = obj->objects.cylinder.orientation;
	radius = obj->objects.cylinder.diameter / 2.0;
	oc = vector_sub(ray.origin, obj->objects.cylinder.coordinates);
	
	a = vector_dot(ray.direction, ray.direction) 
		- pow(vector_dot(ray.direction, axis), 2);
	b = 2 * (vector_dot(ray.direction, oc) 
		- vector_dot(ray.direction, axis) * vector_dot(oc, axis));
	c = vector_dot(oc, oc) - pow(vector_dot(oc, axis), 2) - radius * radius;
	
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		hit.hit = false;
		hit.t = INFINITY;
		return (hit);
	}
	
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t < 0.001 || !check_cylinder_caps(ray, obj, t, axis))
	{
		t = (-b + sqrt(discriminant)) / (2.0 * a);
		if (t < 0.001 || !check_cylinder_caps(ray, obj, t, axis))
		{
			hit.hit = false;
			hit.t = INFINITY;
			return (hit);
		}
	}
	
	hit.hit = true;
	hit.t = t;
	hit.point = vector_add(ray.origin, vector_mult(ray.direction, t));
	hit.object = obj;
	return (hit);
}

t_hit	intersect_cylinder(t_ray ray, t_obj *obj)
{
	t_hit		hit;
	t_hit		cap_hit;
	t_vector	d;
	t_vector	p;
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
	
	if (hit.normal.x != 0 || hit.normal.y != 0 || hit.normal.z != 0)
	{
		if (fabs(vector_dot(hit.normal, axis)) > 0.99)
			return (hit);
	}
	
	p = hit.point;
	d = vector_sub(p, obj->objects.cylinder.coordinates);
	hit.normal = vector_normalize(vector_sub(d, 
		vector_mult(obj->objects.cylinder.orientation,
		vector_dot(d, obj->objects.cylinder.orientation))));
	
	if (vector_dot(hit.normal, ray.direction) > 0)
		hit.normal = vector_mult(hit.normal, -1);
	
	return (hit);
}
