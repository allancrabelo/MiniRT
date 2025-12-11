#include "minirt.h"

/**
 * @brief Handles errors and program cleanup.
 * 
 * Cleans up MLX resources, frees memory, and exits with appropriate code.
 * 
 * @param mini Pointer to main program structure.
 * @param code Error code (0=success, negative=normal exit, positive=error).
 * @return int Always returns 0 for success codes, exits for error/normal exit.
 */
int	ft_err_handler(t_rt *mini, int code)
{
	if (code == 0)
		return (0);
	if (mini && mini->img.mlx_img)
		mlx_destroy_image(mini->mlx_ptr, mini->img.mlx_img);
	if (mini && mini->win_ptr)
		mlx_destroy_window(mini->mlx_ptr, mini->win_ptr);
	if (mini && mini->mlx_ptr)
	{
		mlx_destroy_display(mini->mlx_ptr);
		free(mini->mlx_ptr);
	}
	gc_free_all(mini);
	if (mini)
		free(mini);
	err_message(code);
	if (code > 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
