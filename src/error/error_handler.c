#include "minirt.h"

static void	err_message_parsing(int code)
{
	if (code == ERR_USAGE)
		ft_putstr_fd("Usage: ./miniRT scenes/<Map>.rt\n", 2);
	else if (code == ERR_EXTENSION)
		ft_putstr_fd("Extension error: scene file must have a .rt extension\n", 2);
	else if (code == ERR_FILE_OPEN)
		ft_putstr_fd("File open error: cannot open scene file\n", 2);
	else if (code == ERR_FILE_READ)
		ft_putstr_fd("File read error: failed while reading scene file\n", 2);
	else if (code == ERR_FILE_EMPTY)
		ft_putstr_fd("File error: scene file is empty or contains no valid elements\n", 2);
	else if (code == ERR_INVALID_ELEMENT)
		ft_putstr_fd("Parsing error: invalid element identifier in scene file\n", 2);
	else if (code == ERR_INVALID_FORMAT)
		ft_putstr_fd("Parsing error: invalid format in scene file\n", 2);
	else if (code == ERR_INVALID_RANGE)
		ft_putstr_fd("Parsing error: numeric value out of allowed range\n", 2);
	else if (code == ERR_DUPLICATE_PARAM)
		ft_putstr_fd("Parsing error: duplicate parameter found in scene file\n", 2);
	else if (code == ERR_MALLOC)
		ft_putstr_fd("Memory error: failed to allocate memory\n", 2);
}

static void	err_message_mlx(int code)
{
	if (code == ERR_MLX_INIT)
		ft_putstr_fd("MLX error: failed to initialize MiniLibX\n", 2);
	else if (code == ERR_MLX_WIN)
		ft_putstr_fd("MLX error: failed to create window\n", 2);
	else if (code == ERR_MLX_IMG)
		ft_putstr_fd("MLX error: failed to create image\n", 2);
}

static void	err_message_elements(int code)
{
	if (code == ERR_RESOLUTION_PARAM)
		ft_putstr_fd("Element error: invalid resolution parameter\n", 2);
	else if (code == ERR_OVER_AMBIENTS)
		ft_putstr_fd("Element error: more than one ambient light specified\n", 2);
	else if (code == ERR_AMBIENT_PARAM)
		ft_putstr_fd("Element error: invalid ambient light parameter(s)\n", 2);
	else if (code == ERR_INVALID_COLOR)
		ft_putstr_fd("Element error: invalid color value\n", 2);
	else if (code == ERR_OVER_CAMERAS)
		ft_putstr_fd("Element error: more than one camera specified\n", 2);
	else if (code == ERR_CAMERA_PARAM)
		ft_putstr_fd("Element error: invalid camera parameter(s)\n", 2);
	else if (code == ERR_INVALID_COORD)
		ft_putstr_fd("Element error: invalid coordinate value\n", 2);
	else if (code == ERR_INVALID_ORIENT)
		ft_putstr_fd("Element error: invalid orientation vector\n", 2);
	else if (code == ERR_LIGHT_PARAM)
		ft_putstr_fd("Element error: invalid light parameter(s)\n", 2);
}

static void	err_message_type(int code)
{
	if (code == ERR_NOT_FLOAT)
		ft_putstr_fd("Type error: expected floating point number\n", 2);
	else if (code == ERR_NOT_ULONG)
		ft_putstr_fd("Type error: expected unsigned integer value\n", 2);
}

static void
err_message(int code)
{
	if (code > 0)
	{
		ft_putstr_fd(BRED "[ERROR ", 2);
		ft_putnbr_fd(code, 2);
		ft_putstr_fd("] " RESET, 2);
		/* dispatch by hundreds: parsing, mlx, elements, type */
		if (code < 200)
			err_message_parsing(code);
		else if (code < 300)
			err_message_mlx(code);
		else if (code < 400)
			err_message_elements(code);
		else if (code < 500)
			err_message_type(code);
		else
			ft_putstr_fd("Unknown error code\n", 2);
		ft_putstr_fd("\n", 2);
	}
}

int	ft_err_handler(t_rt *mini, int code)
{
	if (code == 0)
		return (0);
	if (mini && mini->mlx_ptr)
		mlx_destroy_display(mini->mlx_ptr);
	if (mini && mini->win_ptr) /* FIXME: Not working rn, intended */
		mlx_destroy_display(mini->win_ptr);
	gc_free_all(mini);
	if (mini)
		free(mini);
	err_message(code);
	if (code > 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}