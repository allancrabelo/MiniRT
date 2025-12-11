#include "minirt.h"

/**
 * @brief Cleans and formats a configuration line.
 * 
 * Replaces tabs and newlines with spaces, then trims leading/trailing spaces.
 * 
 * @param line Raw line from configuration file.
 * @return char* Cleaned line, or NULL if input is NULL.
 */
static char	*line_cleaner(char *line)
{
	char	*new_line;
	int		i;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\t' || line[i] == '\n')
			line[i] = ' ';
		i++;
	}
	new_line = ft_strtrim(line, " ");
	free(line);
	return (new_line);
}

/**
 * @brief Parses configuration file line by line.
 * 
 * Reads the file descriptor line by line, cleans each line,
 * and dispatches it for parsing. Tracks line numbers for error reporting.
 * 
 * @param mini Pointer to main program structure.
 * @param fd File descriptor of the configuration file.
 * @return int Error code from parsing, or SUCCESS if file parsed completely.
 */
int	file_parser(t_rt *mini, int fd)
{
	int		err;
	int		nbr;
	char	*line;

	nbr = 0;
	err = 0;
	while (!err)
	{
		nbr++;
		line = get_next_line(fd);
		if (!line)
			break ;
		line = line_cleaner(line);
		err = element_dispatcher(mini, line);
		free (line);
	}
	mini->line_nbr = nbr;
	close (fd);
	return (err);
}
