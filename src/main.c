#include "minirt.h"

int	file_init(t_rt *mini, char *file)
{
	int	fd;

	ft_err_handler(mini, file_is_empty(file));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ERR_FILE_OPEN);
	ft_err_handler(mini, file_parser(mini, fd));
	mini->initial_camera = mini->camera;
	mini->render_quality = 1;
	return (EXIT_SUCCESS);
}

static int	start_mlx(t_rt *mini)
{
	mini->mlx_ptr = mlx_init();
	if (mini->mlx_ptr == NULL)
		return (ERR_MLX_INIT);
	mini->win_ptr = mlx_new_window(mini->mlx_ptr, WIN_W, WIN_H, "miniRT");
	if (mini->win_ptr == NULL)
		return (ERR_MLX_WIN);
	mini->img.mlx_img = mlx_new_image(mini->mlx_ptr, WIN_W, WIN_H);
	if (mini->img.mlx_img == NULL)
		return (ERR_MLX_IMG);
	mini->img.addr = mlx_get_data_addr(mini->img.mlx_img, &mini->img.bpp,
				&mini->img.line_len, &mini->img.endian);
	render_scene(mini);
	mlx_hook(mini->win_ptr, 17, 0, (int (*)())close_hook, mini);
	mlx_hook(mini->win_ptr, 2, 1L<<0, (int (*)())key_hook, mini);
	mlx_loop(mini->mlx_ptr);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_rt	*mini;

	mini = ft_calloc(sizeof(t_rt), 1);
	if (!mini)
		return (EXIT_FAILURE);
	ft_err_handler(mini, program_parser(mini, argc, argv));
	//initializer
	ft_err_handler(mini, start_mlx(mini));
	ft_err_handler(mini, -1);
	return (EXIT_SUCCESS);
}
