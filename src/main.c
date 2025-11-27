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
	{
		ft_putstr_fd(BRED "[USAGE ERROR]: ./miniRT <Map>\n" RESET, 2);
		return (EXIT_FAILURE);
	}
	if (extension_checker(argv))
	{
		ft_putstr_fd(BRED "[EXTENSION ERROR]: Must be .rt\n" RESET, 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	start_mlx(t_rt *mini)
{
	mini->mlx_ptr = mlx_init();
	if (mini->mlx_ptr == NULL)
		return(ft_printf(BRED "Failed connection with server\n" RESET, 2), 1);
	mini->win_ptr = mlx_new_window(mini->mlx_ptr, WIN_W, WIN_H, "miniRT");
	if (mini->win_ptr == NULL)
		return (ft_printf(BRED "Failed to create a new window\n" RESET, 2), 1);
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
	if (program_parser(argc, argv))
		return (EXIT_FAILURE);
	if (start_mlx(mini))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}