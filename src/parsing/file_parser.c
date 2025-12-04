#include "minirt.h"

static char	*line_cleanner(char *line)
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
	int		ret;
	int		nbr;
	char	*line;

	ret = 0;
	nbr = 0;
	while (ret != 1)
	{
		nbr++;
		line = get_next_line(fd);
		if (!line)
			break ;
		line = line_cleanner(line);
		mini->line_nbr = nbr;
		if (element_dispatcher(mini, line))
			ret = 1;
		free (line);
	}
	close (fd);
	return (ret);
}