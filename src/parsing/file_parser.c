#include "minirt.h"

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
	return (new_line);
}

int	file_parser(t_rt *mini, int fd)
{
	int		err;
	int		nbr;
	char	*line;

	nbr = 0;
	while (1)
	{
		nbr++;
		line = get_next_line(fd);
		if (!line)
			break ;
		line = line_cleaner(line);
		mini->line_nbr = nbr;
		err = element_dispatcher(mini, line);
		if (err)
		{
			free(line);
			ft_err_handler(mini, err);
		}
		free (line);
	}
	close (fd);
	return (EXIT_SUCCESS);
}
