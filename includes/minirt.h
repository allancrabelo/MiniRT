#ifndef MINIRT_H
# define MINIRT_H

// Library Includes
# include <fcntl.h>		// Open, Close, Read
# include <unistd.h>	// Write
# include <stdio.h>		// Printf
# include <stdlib.h>	// Malloc, Free, Exit
# include <string.h>	// Perror, Strerror
# include <math.h>		// Math functions
# include <sys/time.h>	// Gettimeofday
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdbool.h>

# include "objects.h"
# include "colors.h"
# include "error.h"
# include "../libft/libft.h"
# include "../minilibx/mlx.h"

// Program status
# define SUCCESS -1

// Window Macros:
# define WIN_W 1280
# define WIN_H 720

// Rendering Constants:
# define EPSILON 0.001
# define EPSILON_SMALL 1e-6
# define EPSILON_TINY 1e-8

// Hooks defines:
#define CAMERA_SPEED 2.0
#define ROTATE_ANGLE 0.1
#define QUALITY_FAST 4
#define QUALITY_HIGH 1

// Structures
typedef enum e_token_type
{
	ERROR,
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*content;
}	t_token;

typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;
}	t_gc;

typedef struct s_rt
{
	t_gc		*gc;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	int			line_nbr;
	int			parameter_nbr;
	float		width;
	float		height;
	t_ambient	ambient;
	t_camera	camera;
	t_camera	initial_camera;
	t_light		*light;
	size_t		number_of_objects;
	t_obj		*objects;
	int			render_quality;
	int			show_help;

}	t_rt;

// Function Prototypes

// [Parsing]:
int			program_parser(t_rt *mini, int argc, char **argv);
int			extension_checker(char **argv);
int			file_is_empty(char *file);
int			file_parser(t_rt *mini, int fd);
int			element_dispatcher(t_rt *mini, char *line);
int			vector_parser(char *str, t_vector *vector);
int			light_parser(t_rt *mini, char *line);

// [Initializer]:
int			file_init(t_rt *mini, char *file);

// [Hooks];
int			key_hook(int keysym, void *param);
int			close_hook(void *param);

// [Controls Help]:
void		toggle_controls_help(t_rt *mini);
void		draw_help_overlay(t_rt *mini);

// [Camera Presets]:
void		handle_numpad_camera(t_rt *mini, int keysym);

// [Utils]:
int			array_size(char	**arr);
void		free_array(char **arr);
int			float_parser(char *str, float *num);
int			ulong_parser(char *str, size_t *num);
int			ambient_parser(t_rt *mini, char *line);
int			resolution_parser(t_rt *mini, char *line);
float		ft_atof(char *str);
int			colors_parser(char *str, t_color *primary_color,
				t_color *second_color);
int			is_ulong(char *str);
int			ft_atoc(char *str);
int			is_float(char *str);
float		vector_length(t_vector vector);
t_camera_basis	calculate_camera_basis(t_vector camera_orientation);
t_vector	calculate_pixel_pos(float x, float y, t_viewport vp);
t_viewport	calculate_viewport(t_rt *mini);

// [Vector Math]:
t_vector	vector_add(t_vector a, t_vector b);
t_vector	vector_sub(t_vector a, t_vector b);
t_vector	vector_mult(t_vector v, float scalar);
t_vector	vector_div(t_vector v, float scalar);
float		vector_dot(t_vector a, t_vector b);
t_vector	vector_cross(t_vector a, t_vector b);
t_vector	vector_normalize(t_vector v);

// [Rendering]:
void		render_scene(t_rt *mini);
void		render_scene_quality(t_rt *mini, int quality);
t_color		ray_color(t_rt *mini, t_ray ray);
t_hit		intersect_scene(t_rt *mini, t_ray ray);
t_hit		intersect_sphere(t_ray ray, t_obj *obj);
t_hit		intersect_plane(t_ray ray, t_obj *obj);
t_hit		intersect_cylinder(t_ray ray, t_obj *obj);
t_color		calculate_lighting(t_rt *mini, t_hit hit, t_ray ray);
int			create_trgb(int t, int r, int g, int b);
void		img_pix_put(t_img *img, int x, int y, int color);
t_hit		create_miss_hit(void);
float		get_radius(t_obj *obj);
bool		is_valid_t(float t);
bool		check_cylinder_caps(t_ray ray, t_obj *obj,
			float t, t_vector normal);
t_hit		create_cap_hit(t_ray ray, t_obj *obj, float t, t_vector axis);
bool		check_cap_distance(t_ray ray, t_obj *obj,
		t_vector cap_center, float t);
void		compute_cylinder_normal(t_hit *hit, t_ray ray, t_obj *obj);
t_hit		intersect_cylinder(t_ray ray, t_obj *obj);
t_hit		intersect_cap(t_ray ray, t_obj *obj,
		float cap_height, t_vector axis);
void		init_quadratic_params(t_ray ray, t_obj *obj, float params[3]);
float		solve_quadratic(float params[3], t_ray ray,
		t_obj *obj, t_vector axis);
t_hit		cylinder_body_intersect(t_ray ray, t_obj *obj);
t_vector	calculate_cylinder_normal(t_hit *hit, t_obj *obj);
t_hit		check_object_intersection(t_ray ray, t_obj *obj);
t_hit		intersect_scene(t_rt *mini, t_ray ray);
t_color		calculate_ambient(t_rt *mini, t_hit hit);
t_vector	adjust_shadow_origin(t_vector point, t_vector normal,
		t_vector light_dir);
bool		is_in_shadow(t_rt *mini, t_vector point, t_light *light,
		t_vector normal);
t_color		ray_color(t_rt *mini, t_ray ray);
t_color		calculate_lighting(t_rt *mini, t_hit hit, t_ray ray);
t_vector	get_facing_normal(t_vector normal, t_vector view_dir);
t_color		process_light(t_rt *mini, t_hit hit, t_light *light,
		t_vector normal);
t_color		calculate_diffuse(t_light *light, t_hit hit,
		t_vector normal, t_vector light_dir);

// [Color operations]:
t_color		color_add(t_color c1, t_color c2);
t_color		color_mult(t_color c, float scalar);
t_color		color_mult_color(t_color c1, t_color c2);
int			color_parser(char *str, t_color *color);

// [Camera]:
t_vector	*camera_normalizer(t_vector *vector);
int			camera_parser(t_rt *mini, char *line, int i);

// [Light]:
t_light		*light_generator(t_rt *mini);

// [Objects]:
t_obj		*object_generator(t_rt *mini, t_object_type id);
int			sphere_parser(t_rt *mini, char **parameters, t_obj *objects);
int			plane_parser(t_rt *mini, char **parameters, t_obj *objects);
int			cylinder_parser(t_rt *mini, char **parameters, t_obj *objects);

// [Hooks]:
int			key_hook(int keysym, void *param);
void		handle_numpad_keys(t_rt *mini, int keysym);
void		handle_special_keys(t_rt *mini, int keysym);
void		update_and_render(t_rt *mini, int quality);
int			close_hook(void *param);
t_vector	rotate_vector_y(t_vector v, float angle);
void		rotate_camera(t_rt *mini, int direction);
void		move_camera_forward_back(t_rt *mini, int direction);
void		move_camera_strafe(t_rt *mini, int direction);
void		move_camera_vertical(t_rt *mini, int direction);

// [Errors]:
int			ft_err_handler(t_rt *mini, int code);
void		err_message_parsing(int code);
void		err_message_mlx(int code);
void		err_message_elements(int code);
void		err_message_type(int code);
void		err_message(int code);

// [Extras]:
void		handle_numpad_camera(t_rt *mini, int keysym);
void		set_camera_another_view(t_rt *mini);
t_camera	create_preset_camera(t_vector pos, t_vector orientation);
void		set_camera_front(t_rt *mini);
void		set_camera_front_bottom(t_rt *mini);
void		set_camera_right(t_rt *mini);
void		set_camera_left(t_rt *mini);
void		set_camera_top(t_rt *mini);
void		set_camera_back(t_rt *mini);
void		set_camera_isometric(t_rt *mini);
void		set_camera_alt_isometric(t_rt *mini);

// [Garbage collector and error handler]:
void		*gc_calloc(t_rt *mini, size_t size);
void		gc_free_one(t_rt *rt, void *ptr);
void		gc_free_all(t_rt *rt);
int			ft_err_handler(t_rt *mini, int code);

#endif