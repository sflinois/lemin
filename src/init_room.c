/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 19:24:42 by sflinois          #+#    #+#             */
/*   Updated: 2017/10/29 14:42:17 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/includes/libft.h"
#include <stdio.h>
#include <stdlib.h>

t_room		get_room(char *line)
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

void		switchrooms(t_room **new, t_struct *s, int i)
{
	(*new)[i].name = ft_strdup(s->rooms[i].name);
	(*new)[i].x = ft_strdup(s->rooms[i].x);
	(*new)[i].y = ft_strdup(s->rooms[i].y);
	(*new)[i].status = s->rooms[i].status;
	(*new)[i].is_used = 0;
	(*new)[i].paths = NULL;
	(*new)[i].nb_paths = 0;
	(*new)[i].ant = 0;
	(*new)[i].ants_left = 0;
	free(s->rooms[i].name);
	free(s->rooms[i].x);
	free(s->rooms[i].y);
}

int			create_new_room(t_struct *s)
{
	t_room	*new_rooms;
	int		i;

	if (!(new_rooms = (t_room*)ft_memalloc(sizeof(t_room) * (s->nb_rooms + 1))))
		return (-1);
	i = 0;
	while (i < s->nb_rooms)
	{
		switchrooms(&new_rooms, s, i);
		i++;
	}
	if (s->nb_rooms)
		free(s->rooms);
	s->rooms = new_rooms;
	s->nb_rooms++;
	return (i);
}

void		replace_room(t_room *room, t_room new_room, int status)
{
	room->name = new_room.name;
	room->x = new_room.x;
	room->y = new_room.y;
	room->status = status;
	room->is_used = 0;
	room->paths = NULL;
	room->nb_paths = 0;
	room->ant = 0;
	room->ants_left = 0;
}

int			insert_room(char *line, t_struct *s, int place)
{
	int		i_room;
	t_room	new_room;

	new_room = get_room(line);
	if (is_room_dup(s, new_room))
		return (-1);
	if ((i_room = create_new_room(s)) == -1)
		return (-1);
	replace_room(&s->rooms[i_room], new_room, place);
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
