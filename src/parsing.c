
#include "../include/lem-in.h"
#include "../libft/includes/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int	get_ants(char *line, t_struct *s)
{
	if (line && *line && ft_strisdigit(line))
	{
		s->nb_ants = ft_atoi(line);
		ft_printf("%d\n", s->nb_ants);
		return (1);
	}
	return (-1);
}

int	get_room(char *line, t_struct *s, int place)
{
	int	i;

	i = 0;
	if (*line == '#')
		return (1);
	else if (*line == 'L' || *line == '-' || *line == ' ')
		return (-1);
	else if (is_path_line(line))
		return (insert_path(line, s));
	else if (is_room_line(line))
		return(insert_room(line, s, place));
	line = NULL;
	s = NULL;
	place = 0;
	return (1);
}

int	get_path(char *line, t_struct *s)
{
	line = NULL;
	s = NULL;

	return (4);
}

int	is_anthill_ok(t_struct *s)
{
	s = NULL;
	return (1);
}

int	pars_args(int argc, char **argv, t_struct *s)
{
	char	*line;
	int	line_type;
	int	fd;

	if (argc != 2)
		return (0);
	line = NULL;
	line_type = 0;
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0 && line_type >= 0)
	{
		if (line_type == 0)
			line_type = get_ants(line, s);
		else if (line_type >= 1 && line_type <= 3)
		{
			ft_printf("line_type : %d\n", line_type);
			if (ft_strcmp(line, "##start") == 0)
				line_type = 2;
			else if (ft_strcmp(line, "##end") == 0)
				line_type = 3;
			else
				line_type = get_room(line, s, line_type);
		}
		else if (line_type == 4)
			get_path(line, s);
		free(line);
	}
	return (is_anthill_ok(s));
}
