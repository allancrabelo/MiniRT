#include "minirt.h"

static void	err_message(int code)
{
	if (code > 0)
		printf("Error:%d\n", code); // change this to a better system
}

int	ft_err_handler(t_rt *mini, int code)
{
	if (code == 0)
		return (0);
	if (mini && mini->mlx_ptr)
		mlx_destroy_display(mini->mlx_ptr);
	if (mini && mini->win_ptr)
		mlx_destroy_display(mini->win_ptr);
	gc_free_all(mini);
	if (mini)
		free(mini);
	err_message(code);
	if (code > 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}