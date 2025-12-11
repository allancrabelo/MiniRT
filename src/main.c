#include "minirt.h"

/**
 * @brief Initializes the scene from a configuration file.
 * 
 * Validates the file, opens it, parses its contents, and sets initial
 * program states including camera position and rendering quality.
 * 
 * @param mini Pointer to the main program structure.
 * @param file Path to the .rt configuration file.
 * @return int SUCCESS on completion, error code if file operations fail.
 */
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
	mini->show_help = 0;
	return (EXIT_SUCCESS);
}

/**
 * @brief Initializes the MLX graphics system and creates a window.
 * 
 * Sets up the MLX context, creates a window and image buffer,
 * renders the scene, and registers event hooks for window management.
 * 
 * @param mini Pointer to the main program structure.
 * @return int SUCCESS on completion, error code if MLX initialization fails.
 */
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
	mlx_hook(mini->win_ptr, 17, 0, close_hook, mini);
	mlx_hook(mini->win_ptr, 2, 1L << 0, key_hook, mini);
	mlx_loop(mini->mlx_ptr);
	return (EXIT_SUCCESS);
}

/**
 * @brief Main entry point for the MiniRT ray tracing program.
 * 
 * Initializes the program structure, parses command line arguments,
 * starts the graphics system, and manages execution flow.
 * 
 * @param argc Argument count. Expected: 2 (program + .rt file).
 * @param argv Argument vector. argv[1] should be a valid .rt scene file.
 * @return int EXIT_SUCCESS on completion, EXIT_FAILURE on initialization error.
 */
int	main(int argc, char **argv)
{
	t_rt	*mini;

	mini = ft_calloc(sizeof(t_rt), 1);
	if (!mini)
		return (EXIT_FAILURE);
	ft_err_handler(mini, program_parser(mini, argc, argv));
	ft_err_handler(mini, start_mlx(mini));
	ft_err_handler(mini, SUCCESS);
	return (EXIT_SUCCESS);
}
