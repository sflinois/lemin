#include "../include/lem-in.h"
#include "../libft/includes/libft.h"
#include <stdio.h>
#include <stdlib.h>

void	init_struct(t_struct *s)
{
	s->nb_ants = 0;
	s->nb_rooms = 0;
	s->rooms = NULL;
	s->ants = NULL;
	s->start = -1;
	s->end = -1;
}

int	create_new_room(t_struct *s)
{
	t_room	*new_rooms;
	int	i;
	
	if (!(new_rooms = (t_room*)ft_memalloc(sizeof(t_room) * (s->nb_rooms + 1))))
		return (-1);
	i = 0;
	while (i < s->nb_rooms)
	{
		new_rooms[i].name  = ft_strdup(s->rooms[i].name);
		new_rooms[i].x  = ft_strdup(s->rooms[i].x);
		new_rooms[i].y  = ft_strdup(s->rooms[i].y);
		new_rooms[i].status  = s->rooms[i].status;
		free(s->rooms[i].name);
		free(s->rooms[i].x);
		free(s->rooms[i].y);
		i++;
	}
	if (s->nb_rooms)
		free(s->rooms);
	s->rooms = new_rooms;
	s->nb_rooms++;
	return (i);
}

int	insert_room(char *line, t_struct *s, int place)
{
	int	i_room;
	int	i;
	int	j;

	if((i_room = create_new_room(s)) == -1)
		return (-1);
	i = 0;
	while (line[i] != ' ')
		i++;	
	s->rooms[i_room].name = ft_strndup(line, i);
	i++;
	j = i;
	while (line[i] != ' ')
		i++;
	s->rooms[i_room].x = ft_strndup(line + j, i - j);
	i++;
	j = i;
	while (ft_isdigit(line[i]) || line[i] == '-')
		i++;
	s->rooms[i_room].y = ft_strndup(line + j, i - j);
	s->rooms[i_room].status = place;
	if (place == 2)
	{
		if (s->start != -1)
			s->rooms[s->start].status = 1;
		s->start = i_room;
	}
	if (place == 3)
	{
		if (s->end != -1)
			s->rooms[s->end].status = 1;
		s->end = i_room;
	}
	return (1);
}

int	insert_path(char *line, t_struct *s)
{
	int	i_room;
	char	*name1;
	char	*name2;
	int	i;
	
	i = 0;
	while(line[i] != '-')
		i++;
	name1 = ft_strndup(line, i);
	name2 = ft_strdup(line + i + 1);
	i_room = 0;
	i = 0;
	while(ft_strcmp(s->rooms[i_room].name, name1) != 0 && ft_strcmp(s->rooms[i_room].name, name2) != 0 && i_room < s->nb_rooms)
		i_room++;
	
	return (4);
}
