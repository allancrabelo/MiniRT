#include "minirt.h"

int	file_is_empty(t_rt *mini, char *file)
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

int	extension_checker(char **argv)
{
	int	i;

	i = 0;
	while (argv[1][i])
		i++;
	if (argv[1][i - 1] == 't' && argv[1][i - 2] == 'r' && argv[1][i - 3] == '.')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	program_parser(t_rt *mini, int argc, char **argv)
{
	if (argc != 2)
		return (ERR_USAGE);
	if (extension_checker(argv))
		return (ERR_EXTENSION);
	ft_err_handler(mini, file_init(mini, argv[1]));
	return (EXIT_SUCCESS);
}