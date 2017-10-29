/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 19:31:02 by sflinois          #+#    #+#             */
/*   Updated: 2017/10/29 16:52:14 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/includes/libft.h"

void	print_rooms(t_struct *s)
{
	int	i;
	int	j;

	i = 0;
	ft_printf("-- PRINT STRUCT --\n");
	ft_printf("nb_ants : %i\n", s->nb_ants);
	ft_printf("nb_rooms : %i\n", s->nb_rooms);
	ft_printf("start : %i\n", s->start);
	ft_printf("end : %i\n", s->end);
	ft_printf("ROOMS :\n");
	while (i < s->nb_rooms)
	{
		ft_printf("(%s) - [%i] - [%i] - [%i]=> ", s->rooms[i].name,
				s->rooms[i].is_used, s->rooms[i].ant, s->rooms[i].ants_left);
		j = 0;
		while (j < s->rooms[i].nb_paths)
		{
			ft_printf("{%s}", s->rooms[i].paths[j]->name);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("------------\n");
}

void	print_res(t_res res, t_struct *s)
{
	int		i;
	int		j;

	ft_printf("-- PRINT RET --\n");
	ft_printf("nb_f_paths : %i\n", res.nb_f_paths);
	ft_printf("nb_turns : %i\n", res.nb_turns);
	i = 0;
	while (i < res.nb_f_paths)
	{
		j = 0;
		while (res.f_paths[i][j] != &s->rooms[s->start])
		{
			ft_printf("[%s, %i] ", res.f_paths[i][j]->name,
					res.f_paths[i][j]->is_used, res.f_paths[i][j]);
			j++;
		}
		ft_printf("[%s, %i]\n", res.f_paths[i][j]->name,
				res.f_paths[i][j]->is_used, res.f_paths[i][j]);
		i++;
	}
	ft_printf("------------\n");
}

void	print_path(t_room **path, int length)
{
	int		i;

	i = 0;
	while (i < length)
	{
		if (path[i])
			ft_printf("[%s   %i]", path[i]->name, path[i]->is_used);
		i++;
	}
	ft_printf("\n");
}

void	print_ant(t_struct *s, int i_paths, int i_rooms, int *movement)
{
	if (s->res.f_paths[i_paths][i_rooms]->ants_left > 0 &&
			s->res.f_paths[i_paths][i_rooms + 1]->ant != 0)
	{
		ft_printf("L%02i-%s ", s->res.f_paths[i_paths][i_rooms + 1]->ant,
				s->res.f_paths[i_paths][i_rooms]->name);
		if (s->res.f_paths[i_paths][i_rooms] != &s->rooms[s->end])
			s->res.f_paths[i_paths][i_rooms]->ant = \
				s->res.f_paths[i_paths][i_rooms + 1]->ant;
		else
			s->res.f_paths[i_paths][i_rooms]->ants_left--;
		if (s->res.f_paths[i_paths][i_rooms + 1] != &s->rooms[s->start])
		{
			s->res.f_paths[i_paths][i_rooms + 1]->ant = 0;
			s->res.f_paths[i_paths][i_rooms + 1]->ants_left--;
		}
		else
			s->res.f_paths[i_paths][i_rooms + 1]->ant++;
		(*movement)++;
	}
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
				print_ant(s, i_paths, i_rooms, &movement);
				i_rooms++;
			}
			i_paths++;
		}
		if (movement)
			ft_printf("\n");
	}
}
