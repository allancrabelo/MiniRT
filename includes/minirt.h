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
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "colors.h"
# include <X11/X.h>
# include <X11/keysym.h>
// Macros
# define WIN_W 1280
# define WIN_H 720

// Structures
typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;


typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;
}	t_gc;

typedef struct s_rt
{
	t_gc	*gc;
	void	*mlx_ptr;
	void	*win_ptr;
}	t_rt;

// Function Prototypes

// Garbage collector and error handler
void	*gc_calloc(t_rt *mini, size_t size);
void	gc_free_one(t_rt *rt, void *ptr);
void	gc_free_all(t_rt *rt);
int		ft_err_handler(t_rt *mini, int code);


#endif