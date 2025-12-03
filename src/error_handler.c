#include "minirt.h"

static void	err_message_parsing(int code)
{
	if (code == ERR_USAGE)
		ft_putstr_fd("Usage: ./miniRT <Map>", 2);
	if (code == ERR_EXTENSION)
		ft_putstr_fd("Extention Error, file type must be .rt", 2);
}

static void	err_message(int code)
{
	if (code > 0)
	{
		ft_putstr_fd(BRED "[ERROR ", 2);
		ft_putnbr_fd(code, 2);
		ft_putstr_fd("] " RESET, 2);
		// printf(BRED "[ERROR %d] " RESET, code); // change this to a better system
		if (code < 200)
			err_message_parsing(code);
		ft_putstr_fd("\n", 2);
	}
}

int	ft_err_handler(t_rt *mini, int code)
{
	if (code == 0)
		return (0);
	if (mini && mini->mlx_ptr)
		mlx_destroy_display(mini->mlx_ptr);
	if (mini && mini->win_ptr) // FIXME: Not working rn, intended
		mlx_destroy_display(mini->win_ptr);
	gc_free_all(mini);
	if (mini)
		free(mini);
	err_message(code);
	if (code > 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}