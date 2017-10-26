/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 19:30:29 by sflinois          #+#    #+#             */
/*   Updated: 2017/10/26 19:35:11 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (s->nb_ants > 0 ? 1 : -1);
	}
	return (-1);
}

int	new_room(char *line, t_struct *s, int place)
{
	int	i;

	i = 0;
	if (*line == '#' && place == 1)
		return (1);
	else if (*line == 'L' || *line == '-' || *line == ' ' ||
			*line == '#' || *line == '\n')
		return (-1);
	else if (is_path_line(line))
	{
		return (insert_path(line, s));
	}
	else if (is_room_line(line))
	{
		return (insert_room(line, s, place));
	}
	return (-1);
}

int	new_path(char *line, t_struct *s)
{
	int	i;

	i = 0;
	if (*line == '#')
		return (1);
	else if (*line == 'L' || *line == '-' || *line == ' ')
		return (-1);
	else if (is_path_line(line))
		return (insert_path(line, s));
	return (-1);
}

int	is_anthill_ok(int line_type, t_struct *s)
{
	int			i;

	if (s->start == -1 || s->end == -1 || s->nb_ants < 1)
		return (0);
	if (s->rooms[s->start].nb_paths == 0 || s->rooms[s->end].nb_paths == 0)
		return (0);
	i = s->rooms[s->start].nb_paths <= s->rooms[s->end].nb_paths ?
		s->rooms[s->start].nb_paths : s->rooms[s->end].nb_paths;
	s->res.nb_f_paths = 0;
	s->res.f_paths = NULL;
	s->res.nb_turns = 0;
	s->tmp.nb_f_paths = 0;
	s->tmp.f_paths = NULL;
	s->tmp.nb_turns = 0;
	resolve(s, i);
	return (line_type < 0 || s->res.nb_f_paths == 0 ? 0 : 1);
}

int	pars_args(int argc, char **argv, t_struct *s)
{
	char	*line;
	int		line_type;
	int		fd;

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
			if (line_type == 1 && ft_strcmp(line, "##start") == 0)
				line_type = 2;
			else if (line_type == 1 && ft_strcmp(line, "##end") == 0)
				line_type = 3;
			else
				line_type = new_room(line, s, line_type);
		}
		else if (line_type == 4)
			line_type = new_path(line, s);
		free(line);
	}
	free(line);
	return (is_anthill_ok(line_type, s));
}
