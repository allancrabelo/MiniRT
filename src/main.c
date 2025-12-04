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

/* static int	file_parser(t_rt *mini, int fd)
{
	(void)mini;
	(void)fd;
	return (EXIT_SUCCESS);
} */

static int	file_is_empty(t_rt *mini, char *file)
{
	int		fd;
	char	c;
	ssize_t	byte;

	(void)mini;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ERR_FILE_OPEN);
	byte = read(fd, &c, 1);
	close(fd);
	if (byte < 0)
		return (ERR_FILE_READ);
	if (byte == 0)
		return (ERR_FILE_EMPTY);
	return (EXIT_SUCCESS);
}

static int	file_init(t_rt *mini, char *file)
{
	int	fd;
	//int	status;

	ft_err_handler(mini, file_is_empty(mini, file));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ERR_FILE_OPEN);
	//ft_err_handler(mini, file_parser(mini, fd));
	return (EXIT_SUCCESS);
}

static int	program_parser(t_rt *mini, int argc, char **argv)
{
	if (argc != 2)
		return (ERR_USAGE);
	if (extension_checker(argv))
		return (ERR_EXTENSION);
	ft_err_handler(mini, file_init(mini, argv[1]));
	return (EXIT_SUCCESS);
}

int	key_hook1(int keysym, t_rt *mini)
{
	if (keysym == XK_Escape)
		ft_err_handler(mini, -1);
	return (0);
}


static int	ft_close_x(t_rt *mini)
{
	return (ft_err_handler(mini, -1));
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
	mlx_hook(mini->win_ptr, DestroyNotify, 0, ft_close_x, mini);
	mlx_hook(mini->win_ptr, KeyPress, 1, key_hook1, mini);
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
	ft_err_handler(mini, start_mlx(mini));
	ft_err_handler(mini, -1);
	return (EXIT_SUCCESS);
}