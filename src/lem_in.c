/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 19:35:24 by sflinois          #+#    #+#             */
/*   Updated: 2017/10/26 19:40:00 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
#include "../libft/includes/libft.h"

int		init_res_ants(t_struct *s, int *tab, int nb_paths, int nb_ants)
{
	int		i_tab;
	int		max;

	if (!(s->res.nb_ants_path = (int*)ft_memalloc(sizeof(int) * s->res.nb_f_paths)))
		return (0);
	max = tab[0];
	i_tab = 0;
	while (i_tab < nb_paths)
	{
		if (tab[i_tab] > max)
			max = tab[i_tab];
		i_tab++;
	}
	i_tab = 0;
	while (i_tab < s->res.nb_f_paths)
	{
		s->res.nb_ants_path[i_tab] = max - tab[i_tab];
		nb_ants -= s->res.nb_ants_path[i_tab];
		i_tab++;
	}
	i_tab = 0;
	while (i_tab < s->res.nb_f_paths)
	{
		s->res.nb_ants_path[i_tab] += nb_ants / nb_paths;
		if (nb_ants % nb_paths > i_tab)
			s->res.nb_ants_path[i_tab]++;
		i_tab++;
	}
	return (1);
}

int		calc_res(t_struct *s)
{
	int		*paths_length;
	int		i_tab;
	int		i;

	if (!(paths_length = (int*)ft_memalloc(sizeof(int) * s->res.nb_f_paths)))
		return (0);
	i_tab = 0;
	while (i_tab < s->tmp.nb_f_paths)
	{
		i = 0;
		while (s->res.f_paths[i_tab][i] != &s->rooms[s->start])
			i++;
		paths_length[i_tab] = i;
		i_tab++;
	}
	if (!init_res_ants(s, paths_length, s->res.nb_f_paths, s->nb_ants))
		return (0);
	return (1);
}

void	init_res_map(t_struct *s)
{
	int		i_paths;
	int		i_rooms;

	i_paths = 0;
	while (i_paths < s->res.nb_f_paths)
	{
		i_rooms = 0;
		while (s->res.f_paths[i_paths][i_rooms] != &s->rooms[s->start])
		{
			if (s->res.f_paths[i_paths][i_rooms] != &s->rooms[s->end])
				s->res.f_paths[i_paths][i_rooms]->ants_left = s->res.nb_ants_path[i_paths];
			i_rooms++;
		}
		i_paths++;
	}
	s->rooms[s->start].ant = 1;
	s->rooms[s->end].ant = 0;
	s->rooms[s->end].ants_left = s->nb_ants;
}

void	print_resolved_map(t_struct *s)
{
	int		movement;
	int		i_paths;
	int		i_rooms;

	movement = 1;
	while (movement)
	{
		movement = 0;
		i_paths = 0;
		while (i_paths < s->res.nb_f_paths)
		{
			i_rooms = 0;
			while (s->res.f_paths[i_paths][i_rooms] != &s->rooms[s->start])
			{
				if (s->res.f_paths[i_paths][i_rooms]->ants_left > 0 && s->res.f_paths[i_paths][i_rooms + 1]->ant != 0)
				{
					ft_printf("L%02i-%s ", s->res.f_paths[i_paths][i_rooms + 1]->ant, s->res.f_paths[i_paths][i_rooms]->name);
					if (s->res.f_paths[i_paths][i_rooms] != &s->rooms[s->end])
						s->res.f_paths[i_paths][i_rooms]->ant = s->res.f_paths[i_paths][i_rooms + 1]->ant;
					else
						s->res.f_paths[i_paths][i_rooms]->ants_left--;
					if (s->res.f_paths[i_paths][i_rooms + 1] != &s->rooms[s->start])
					{
						s->res.f_paths[i_paths][i_rooms + 1]->ant = 0;
						s->res.f_paths[i_paths][i_rooms + 1]->ants_left--;
					}
					else
						s->res.f_paths[i_paths][i_rooms + 1]->ant++;
					movement++;
				}
				i_rooms++;
			}
			i_paths++;
		}
		ft_printf("\n");
	}
}

int		main(int argc, char **argv)
{
	t_struct	s;

	init_struct(&s);
	if (!pars_args(argc, argv, &s))
	{
		ft_printf("ERROR\n");
		return (1);
	}
	calc_res(&s);
	init_res_map(&s);
	print_res(s.res, &s);
	print_resolved_map(&s);
	ft_printf("OK\n");
	return (0);
}
