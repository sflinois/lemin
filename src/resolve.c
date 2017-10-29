/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 19:40:16 by sflinois          #+#    #+#             */
/*   Updated: 2017/10/29 16:40:36 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

void	mapping(t_struct *s, int map_room, int i_used, int i_room)
{
	int		i_paths;

	while (s->rooms[s->end].is_used == 0 && map_room != 0)
	{
		map_room = 0;
		i_room = -1;
		while (++i_room < s->nb_rooms)
		{
			if (s->rooms[i_room].is_used == i_used)
			{
				i_paths = 0;
				while (i_paths < s->rooms[i_room].nb_paths)
				{
					if (s->rooms[i_room].paths[i_paths]->is_used == 0
							&& s->rooms[i_room].paths[i_paths]->status != 2)
					{
						s->rooms[i_room].paths[i_paths]->is_used = i_used + 1;
						map_room++;
					}
					i_paths++;
				}
			}
		}
		i_used++;
	}
}

int		get_quick_path(t_struct *s, int i)
{
	int		map_room;
	int		i_room;
	int		i_used;
	int		i_paths;

	i_used = 2;
	map_room = 1;
	s->rooms[s->start].paths[i]->is_used = 2;
	i_room = 0;
	mapping(s, map_room, i_used, i_room);
	i_paths = create_new_path(s);
	i_room = 0;
	while (i_room < s->nb_rooms)
	{
		if (s->rooms[i_room].is_used != 1)
			s->rooms[i_room].is_used = 0;
		i_room++;
	}
	return (i_paths - 1);
}

void	remove_path(t_struct *s, t_room ****path_tab, int i_tmp)
{
	int		i_tab;

	if (!((*path_tab) = (t_room***)ft_memalloc(sizeof(t_room**)
					* (s->tmp.nb_f_paths - 1))))
		ft_exit("ERROR\n");
	i_tab = 0;
	while (s->tmp.f_paths[i_tmp][i_tab] != &s->rooms[s->start])
	{
		s->tmp.f_paths[i_tmp][i_tab]->is_used = 0;
		i_tab++;
	}
}

int		del_paths(t_struct *s, int i_tmp)
{
	int		i_new;
	t_room	***path_tab;

	if (i_tmp < 0)
		return (0);
	remove_path(s, &path_tab, i_tmp);
	if (!(path_tab = (t_room***)ft_memalloc(sizeof(t_room**)
					* (s->tmp.nb_f_paths - 1))))
		ft_exit("ERROR\n");
	i_new = 0;
	while (i_new < s->tmp.nb_f_paths)
	{
		if (i_new < i_tmp)
			path_tab[i_new] = s->tmp.f_paths[i_new];
		if (i_new == i_tmp)
			free(s->tmp.f_paths[i_new]);
		if (i_new > i_tmp)
			path_tab[i_new - 1] = s->tmp.f_paths[i_new];
		i_new++;
	}
	free(s->tmp.f_paths);
	s->tmp.f_paths = path_tab;
	s->tmp.nb_f_paths--;
	return (1);
}

int		resolve(t_struct *s, int nb_paths)
{
	int		i;
	int		i_tmp;

	if (nb_paths == 0)
		return (0);
	i = 0;
	while (i < s->rooms[s->start].nb_paths)
	{
		if (!s->rooms[s->start].paths[i]->is_used)
		{
			i_tmp = get_quick_path(s, i);
			resolve(s, nb_paths - 1);
			if (s->tmp.nb_f_paths != 0)
			{
				get_best_paths(s);
				if (!del_paths(s, i_tmp))
					return (-1);
			}
			if (s->rooms[s->start].nb_paths > 8
					&& s->rooms[s->end].nb_paths > 8)
				i = s->rooms[s->start].nb_paths;
		}
		i++;
	}
	return (1);
}
