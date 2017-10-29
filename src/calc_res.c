/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 19:40:16 by sflinois          #+#    #+#             */
/*   Updated: 2017/10/29 16:38:53 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

int		get_time_res(int *tab, int nb_paths, int nb_ants)
{
	int		i_tab;
	int		max;
	int		time;

	if (nb_paths == 0)
		return (500);
	max = tab[0];
	i_tab = 0;
	while (i_tab < nb_paths)
	{
		if (tab[i_tab] > max)
			max = tab[i_tab];
		i_tab++;
	}
	i_tab = 0;
	while (i_tab < nb_paths)
	{
		nb_ants -= max - tab[i_tab];
		i_tab++;
	}
	time = max + nb_ants / nb_paths;
	if (nb_ants % nb_paths != 0)
		time++;
	return (time);
}

t_room	***init_res(t_struct *s)
{
	int	i_paths;

	i_paths = 0;
	while (i_paths < s->res.nb_f_paths)
	{
		free(s->res.f_paths[i_paths]);
		i_paths++;
	}
	free(s->res.f_paths);
	s->res.nb_f_paths = s->tmp.nb_f_paths;
	s->res.nb_turns = s->tmp.nb_turns;
	return (s->res.f_paths =
			(t_room***)ft_memalloc(sizeof(t_room**) * (s->res.nb_f_paths)));
}

int		replace_res(t_struct *s)
{
	int	i_paths;
	int	i_rooms;

	if (!init_res(s))
		return (-1);
	i_paths = 0;
	while (i_paths < s->res.nb_f_paths)
	{
		i_rooms = 0;
		while (s->tmp.f_paths[i_paths][i_rooms] != &s->rooms[s->start])
			i_rooms++;
		if (!(s->res.f_paths[i_paths] =
					(t_room**)ft_memalloc(sizeof(t_room*) * (i_rooms + 1))))
			return (-1);
		i_rooms = 0;
		while (s->tmp.f_paths[i_paths][i_rooms] != &s->rooms[s->start])
		{
			s->res.f_paths[i_paths][i_rooms] = s->tmp.f_paths[i_paths][i_rooms];
			i_rooms++;
		}
		s->res.f_paths[i_paths][i_rooms] = &s->rooms[s->start];
		i_paths++;
	}
	return (1);
}

int		get_best_paths(t_struct *s)
{
	int		*paths_length;
	int		i_tab;
	int		i;

	if (!(paths_length = (int*)ft_memalloc(sizeof(int) * s->tmp.nb_f_paths)))
		ft_exit("ERROR\n");
	i_tab = 0;
	while (i_tab < s->tmp.nb_f_paths)
	{
		i = 0;
		while (s->tmp.f_paths[i_tab][i] != &s->rooms[s->start])
			i++;
		paths_length[i_tab] = i;
		i_tab++;
	}
	s->tmp.nb_turns = get_time_res(paths_length, s->tmp.nb_f_paths, s->nb_ants);
	if (s->tmp.nb_turns < s->res.nb_turns || s->res.nb_turns == 0)
		replace_res(s);
	free(paths_length);
	return (1);
}
