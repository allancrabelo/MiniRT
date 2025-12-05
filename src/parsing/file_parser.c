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
