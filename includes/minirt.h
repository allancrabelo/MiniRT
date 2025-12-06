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

// Window Macros:
# define WIN_W 1280
# define WIN_H 720

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
	int			line_nbr;
	int			parameter_nbr;
	float		width;
	float		height;
	t_ambient	ambient;
	t_camera	camera;
	t_light		*light;
	size_t		number_of_objects;
	t_obj		*objects;

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
int			key_hook(int keysym, t_rt *mini);
int			close_hook(t_rt *mini);

// [Utils]:
int			array_size(char	**arr);
void		free_array(char **arr);
int			float_parser(char *str, float *num);
int			ulong_parser(char *str, size_t *num);
int			ambient_parser(t_rt *mini, char *line);
int			resolution_parser(t_rt *mini, char *line);
float		ft_atof(char *str);
int			color_parser(char *str, t_color *color);
int			colors_parser(char *str, t_color *primary_color, t_color *second_color);
int			is_ulong(char *str);
int			ft_atoc(char *str);
int			is_float(char *str);
float		vector_length(t_vector vector);

// [Camera]:
t_vector	*camera_normalizer(t_vector *vector);
int			camera_parser(t_rt *mini, char *line, int i);

// [Light]:
t_light		*light_generator(t_rt *mini);

// [Objects]:
t_obj	*object_generator(t_rt *mini, t_object_type id);
int		sphere_parser(t_rt *mini, char **parameters, t_obj *objects);

// Garbage collector and error handler
void		*gc_calloc(t_rt *mini, size_t size);
void		gc_free_one(t_rt *rt, void *ptr);
void		gc_free_all(t_rt *rt);
int			ft_err_handler(t_rt *mini, int code);

#endif