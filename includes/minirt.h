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
typedef struct s_rt
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_rt;

// Function Prototypes

#endif