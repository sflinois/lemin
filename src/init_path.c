/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 19:24:42 by sflinois          #+#    #+#             */
/*   Updated: 2017/10/29 14:35:46 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/includes/libft.h"
#include <stdio.h>
#include <stdlib.h>

void		init_struct(t_struct *s)
{
	s->nb_ants = 0;
	s->nb_rooms = 0;
	s->rooms = NULL;
	s->start = -1;
	s->end = -1;
	s->res.nb_f_paths = 0;
	s->res.nb_turns = 0;
	s->res.f_paths = NULL;
}

void		replace_path(t_room *s_room, t_room *s_room_path,
		t_room **path_tab, int i_path)
{
	if (s_room->nb_paths > 0)
		free(s_room->paths);
	path_tab[i_path] = s_room_path;
	s_room->paths = path_tab;
	s_room->nb_paths++;
}

int			add_path(t_struct *s, int i_room, char *name)
{
	int		i_rp;
	int		i_path;
	t_room	**path_tab;

	i_rp = 0;
	while (i_rp < s->nb_rooms && ft_strcmp(s->rooms[i_rp].name, name) != 0)
		i_rp++;
	if (i_rp == s->nb_rooms || i_rp == i_room)
		return (-2);
	if (!(path_tab = (t_room**)ft_memalloc(sizeof(t_room*)
					* (s->rooms[i_room].nb_paths + 1))))
		return (-2);
	i_path = 0;
	while (i_path < s->rooms[i_room].nb_paths)
	{
		if (name == s->rooms[i_room].paths[i_path]->name)
		{
			free(path_tab);
			return (i_room);
		}
		path_tab[i_path] = s->rooms[i_room].paths[i_path];
		i_path++;
	}
	replace_path(&(s->rooms[i_room]), &(s->rooms[i_rp]), path_tab, i_path);
	return (i_room);
}

int			insert_path(char *line, t_struct *s)
{
	int		i_room;
	int		i;
	char	*name1;
	char	*name2;

	i = 0;
	while (line[i] != '-')
		i++;
	name1 = ft_strndup(line, i);
	name2 = ft_strdup(line + i + 1);
	i_room = 0;
	while (i_room < s->nb_rooms && i_room != -1)
	{
		if (ft_strcmp(s->rooms[i_room].name, name1) == 0)
			i_room = add_path(s, i_room, name2);
		if (ft_strcmp(s->rooms[i_room].name, name2) == 0)
			i_room = add_path(s, i_room, name1);
		i_room++;
	}
	free(name1);
	free(name2);
	return (i_room == -1 ? -1 : 4);
}
