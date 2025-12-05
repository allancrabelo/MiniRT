#include "minirt.h"

static int	contains_non_whitespace(char *buf, ssize_t bytes)
{
	size_t	i;

	i = 0;
	while (i < (size_t)bytes)
	{
		if (!ft_isspace((int)buf[i]))
			return (1);
		i++;
	}
	return (0);
}

int	file_is_empty(char *file)
{
	int		fd;
	char	buf[1024];
	ssize_t	bytes;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ERR_FILE_OPEN);
	bytes = read(fd, buf, sizeof(buf));
	while (bytes > 0)
	{
		if (contains_non_whitespace(buf, bytes))
		{
			close(fd);
			return (EXIT_SUCCESS);
		}
		bytes = read(fd, buf, sizeof(buf));
	}
	close(fd);
	if (bytes < 0)
		return (ERR_FILE_READ);
	return (ERR_FILE_EMPTY);
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
