#ifndef OBJECTS_H
# define OBJECTS_H

// [Objects Macros]:
# define SPHERE_PARAM 4
# define PLANE_PARAM 4
# define CYLINDER_PARAM 6

// Shapes Default:
# define DEFAULT_SPECULAR_INTENSITY 0.5
# define DEFAULT_SPECULAR_EXPONENT 20
# define DEFAULT_REFLECTIVITY 0.0
# define DEFAULT_REFRACTIVE_INDEX 0.0
# define DEFAULT_PATTERN_SCALE 0.0
# define DEFAULT_PATTERN_TYPE 0

typedef enum e_object_type
{
	OBJ_SPHERE,
	OBJ_TRIANGLE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_UNSET,
	OBJ_LIGHT,
	OBJ_CAMERA,
	OBJ_CONE,
	OBJ_AMBIENT,
	OBJ_TORUS
}	t_object_type;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_camera
{
	t_object_type	id;
	t_vector		coordinates;
	t_vector		orientation;
	size_t			fov;
	float			scale;
}	t_camera;

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}	t_color;

typedef struct s_colors
{
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
	t_color	reflective;
	t_color	refractive;
	int		shadows;
}	t_colors;

typedef struct s_light
{
	t_object_type	id;
	t_color			color;
	t_vector		coordinates;
	float			brightness;
	struct s_light	*next;
}	t_light;

typedef struct s_ambient
{
	t_object_type	id;
	float			lighting;
	t_color			color;

}	t_ambient;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;

typedef struct s_sphere
{
	t_object_type	id;
	t_vector		coordinates;
	float			diameter;
	t_color			color;

}	t_sphere;

typedef struct s_plane
{
	t_object_type	id;
	t_vector		coordinates;
	t_vector		orientation;
	t_color			color;

}	t_plane;

typedef struct s_cylinder
{
	t_object_type	id;
	t_vector		coordinates;
	t_vector		orientation;
	float			diameter;
	float			height;
	t_color			color;

}	t_cylinder;

typedef union u_object_hub
{
	t_sphere		sphere;
	t_plane			plane;
	t_cylinder		cylinder;

}	t_object_hub;

typedef struct s_obj
{
	t_object_type	id;
	t_object_hub	objects;
	float			specular_intensity;
	float			specular_exponent;
	float			reflectivity;
	float			refractive_index;
	float			pattern_scale;
	int				pattern_type;
	//t_bool????
	bool			has_bump;
	t_img			bump;
	bool			has_texture;
	t_img			texture;
	t_vector		coordinates;
	t_color			primary_color;
	t_color			second_color;
	struct s_obj	*next;
}	t_obj;

typedef struct s_hit
{
	float		t;
	t_vector	point;
	t_vector	normal;
	t_obj		*object;
	bool		hit;
}	t_hit;

#endif