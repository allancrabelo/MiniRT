#include "minirt.h"

/**
 * @brief Checks if a buffer contains non-whitespace characters.
 * 
 * Scans a buffer to determine if it contains any character that is not
 * a space, tab, newline, or other whitespace.
 * 
 * @param buf Buffer to scan.
 * @param bytes Number of bytes in the buffer to check.
 * @return int 1 if non-whitespace found, 0 if only whitespace.
 */
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

/**
 * @brief Checks if a file is empty or contains only whitespace.
 * 
 * Reads the file in chunks and verifies if it contains any non-whitespace
 * characters. Returns an error if the file is empty or contains only spaces,
 * tabs, or newlines.
 * 
 * @param file Path to the file to check.
 * @return int SUCCESS if file has content, error code if empty or unreadable.
 */
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

/**
 * @brief Validates the file extension.
 * 
 * Checks if the provided file has the required ".rt" extension.
 * 
 * @param argv Argument vector containing the file path.
 * @return int SUCCESS if extension is ".rt", FAILURE otherwise.
 */
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

/**
 * @brief Parses and validates command line arguments.
 * 
 * Checks argument count, validates file extension, and initializes
 * the scene configuration from the provided file.
 * 
 * @param mini Pointer to the main program structure.
 * @param argc Argument count.
 * @param argv Argument vector containing the program name and file path.
 * @return int SUCCESS on valid arguments, error code otherwise.
 */
int	program_parser(t_rt *mini, int argc, char **argv)
{
	if (argc != 2)
		return (ERR_USAGE);
	if (extension_checker(argv))
		return (ERR_EXTENSION);
	ft_err_handler(mini, file_init(mini, argv[1]));
	return (EXIT_SUCCESS);
}
