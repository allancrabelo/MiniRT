#include "minirt.h"

static int	extension_checker(char **argv)
{
	int	i;

	i = 0;
	while (argv[1][i])
		i++;
	if (argv[1][i - 1] == 't' && argv[1][i - 2] == 'r' && argv[1][i - 3] == '.')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static int	program_parser(int argc, char **argv)
{
	if (argc != 2)
		return (ERR_USAGE);
	if (extension_checker(argv))
		return (ERR_EXTENSION);
	return (EXIT_SUCCESS);
}

static int	start_mlx(t_rt *mini)
{
	mini->mlx_ptr = mlx_init();
	if (mini->mlx_ptr == NULL)
		return(ERR_MLX_INIT); //TODO: Change Remove this from here
	mini->win_ptr = mlx_new_window(mini->mlx_ptr, WIN_W, WIN_H, "miniRT");
	if (mini->win_ptr == NULL)
		return (ERR_MLX_WIN); //TODO: Change Remove this from here
	//mini->img.mlx_img = mlx_new_image(mini->mlx_ptr, WIN_W, WIN_H);
	//mini->img.addr = mlx_get_data_addr(mini->img.mlx_img, &mini->img.bpp,
				//&mini->img.line_len, &mini->img.endian);
	//mlx_loop_hook(mini->mlx_ptr, loop_hook, mini);
	//mlx_hook(mini->win_ptr, DestroyNotify, 0, close_app, mini);
	//mlx_hook(mini->win_ptr, KeyPress, 1, key_hook1, mini);
	mlx_do_key_autorepeaton(mini->mlx_ptr);
	mlx_loop(mini->mlx_ptr);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_rt	*mini;

	mini = ft_calloc(sizeof(t_rt), 1);
	if (!mini)
		return (EXIT_FAILURE);
	ft_err_handler(mini, program_parser(argc, argv));
	
	ft_err_handler(mini, start_mlx(mini));
	ft_err_handler(mini, -1);
	return (EXIT_SUCCESS);
}