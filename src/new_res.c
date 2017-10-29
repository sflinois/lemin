/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 19:40:16 by sflinois          #+#    #+#             */
/*   Updated: 2017/10/29 15:38:15 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

void	replace_tmp(t_struct *s, t_room **new_p, t_room ***new_fp, int i_fr)
{
	int		i_paths;

	if (i_fr == -1)
		return ;
	if (new_p[i_fr - 1] != &s->rooms[s->end])
		new_p[i_fr - 1]->is_used = 1;
	new_p[i_fr] = &s->rooms[s->start];
	i_paths = 0;
	while (i_paths < s->tmp.nb_f_paths)
	{
		new_fp[i_paths] = s->tmp.f_paths[i_paths];
		i_paths++;
	}
	new_fp[i_paths] = new_p;
	free(s->tmp.f_paths);
	s->tmp.f_paths = new_fp;
	s->tmp.nb_f_paths++;
	s->rooms[s->end].is_used = 0;
}

int		init_new_tmp(t_struct *s, t_room ***new_path, t_room ****new_f_paths)
{
	if (s->rooms[s->end].is_used == 0)
		return (-1);
	if (!((*new_path) = (t_room**)ft_memalloc(sizeof(t_room*)
					* s->rooms[s->end].is_used)))
		ft_exit("ERROR\n");
	if (!((*new_f_paths) = (t_room***)ft_memalloc(sizeof(t_room**)
					* (s->tmp.nb_f_paths + 1))))
		ft_exit("ERROR\n");
	(*new_path)[0] = &(s->rooms[s->end]);
	return (1);
}

int		create_new_path(t_struct *s)
{
	t_room	**new_path;
	t_room	***new_f_paths;
	int		i_paths;
	int		i_f_rooms;

	i_f_rooms = init_new_tmp(s, &new_path, &new_f_paths);
	while (i_f_rooms < s->rooms[s->end].is_used - 1 && i_f_rooms != -1)
	{
		i_paths = 0;
		while (i_paths < new_path[i_f_rooms - 1]->nb_paths)
		{
			if (new_path[i_f_rooms - 1]->paths[i_paths]->is_used
					== new_path[i_f_rooms - 1]->is_used - 1)
			{
				new_path[i_f_rooms] = new_path[i_f_rooms - 1]->paths[i_paths];
				if (new_path[i_f_rooms - 1] != &(s->rooms[s->end]))
					new_path[i_f_rooms - 1]->is_used = 1;
				i_paths = new_path[i_f_rooms - 1]->nb_paths - 1;
			}
			i_paths++;
		}
		i_f_rooms++;
	}
	replace_tmp(s, new_path, new_f_paths, i_f_rooms);
	return (i_f_rooms != -1 ? s->tmp.nb_f_paths : -1);
}
