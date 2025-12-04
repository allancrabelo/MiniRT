#ifndef OBJECTS_H
# define OBJECTS_H

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

typedef struct s_color
{
	float	R;
	float	G;
	float	B;
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

typedef struct s_ambient
{
	t_object_type	id;
	float			lighting;
	t_color			color;

}	t_ambient;

#endif