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

t_room	get_room(char *line)
{
	t_room	ret;
	int		i;
	int		j;

	i = 0;
	while (line[i] != ' ')
		i++;	
	ret.name = ft_strndup(line, i);
	i++;
	j = i;
	while (line[i] != ' ')
		i++;
	ret.x = ft_strndup(line + j, i - j);
	i++;
	j = i;
	while (ft_isdigit(line[i]) || line[i] == '-')
		i++;
	ret.y = ft_strndup(line + j, i - j);
	return (ret);
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
		new_rooms[i].name = ft_strdup(s->rooms[i].name);
		new_rooms[i].x = ft_strdup(s->rooms[i].x);
		new_rooms[i].y = ft_strdup(s->rooms[i].y);
		new_rooms[i].status = s->rooms[i].status;
		new_rooms[i].is_used = 0;
		new_rooms[i].paths = NULL;
		new_rooms[i].nb_paths  = 0;
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
	int		i_room;
	t_room	new_room;

	new_room = get_room(line);
	if (is_room_dup(s, new_room))
		return (-1);
	if((i_room = create_new_room(s)) == -1)
		return (-1);
	s->rooms[i_room].name = new_room.name;
	s->rooms[i_room].x = new_room.x;
	s->rooms[i_room].y = new_room.y;
	s->rooms[i_room].status = place;
	s->rooms[i_room].is_used = 0;
	s->rooms[i_room].paths = NULL;
	s->rooms[i_room].nb_paths  = 0;
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

int	add_path(t_struct *s, int i_room, char *name)
{
	int		i_room_path;
	int		i_path;
	t_room	**path_tab;

	i_room_path = 0;
	while (i_room_path < s->nb_rooms && ft_strcmp(s->rooms[i_room_path].name, name) != 0)
		i_room_path++;
	if (i_room_path == s->nb_rooms || i_room_path == i_room)
		return (-2);
	if (!(path_tab = (t_room**)ft_memalloc(sizeof(t_room*) * (s->rooms[i_room].nb_paths + 1))))
		return (-2);
	i_path = 0;
	while(i_path < s->rooms[i_room].nb_paths)
	{
		if (name == s->rooms[i_room].paths[i_path]->name)
		{
			free(path_tab);
			return (i_room);
		}
		path_tab[i_path] = s->rooms[i_room].paths[i_path];
		i_path++;
	}
	if (s->rooms[i_room].nb_paths > 0)
		free(s->rooms[i_room].paths);
	path_tab[i_path] = &(s->rooms[i_room_path]);
	s->rooms[i_room].paths = path_tab;
	s->rooms[i_room].nb_paths++;
	return (i_room);
}

int	insert_path(char *line, t_struct *s)
{
	int		i_room;
	int		i;
	char	*name1;
	char	*name2;
	
	i = 0;
	while(line[i] != '-')
		i++;
	name1 = ft_strndup(line, i);
	name2 = ft_strdup(line + i + 1);
	i_room = 0;
	while(i_room < s->nb_rooms && i_room != -1)
	{
		if (ft_strcmp(s->rooms[i_room].name, name1) == 0)
			i_room = add_path(s, i_room, name2);
		if (ft_strcmp(s->rooms[i_room].name, name2) == 0)
			i_room = add_path(s, i_room, name1);
		i_room++;
	}
	return (i_room == -1 ? -1 : 4);
}
