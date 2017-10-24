#include "../include/lem-in.h"
#include "../libft/includes/libft.h"

/*
**
** fonction a verif avec des prints
**
**
**
**
*/

int		insert_path(t_struct *s)
{
	t_room	**new_path;
	t_room	***new_f_paths;
	int		i_paths;
	int		i_f_rooms;

	if (s->rooms[s->end].is_used == 0)
		return (-1);
	if (!(new_path = (t_room**)ft_memalloc(sizeof(t_room*) * s->rooms[s->end].is_used)))
		return (-1);
	if (!(new_f_paths = (t_room***)ft_memalloc(sizeof(t_room**) * s->tmp.nb_f_paths + 1)))
		return (-1);
	new_path[0] = &(s->rooms[s->end]);
	i_f_rooms = 1;
	while (i_f_rooms < s->rooms[s->end].is_used - 1)
	{
		i_paths = 0;
		while(i_paths < new_path[i_f_rooms - 1]->nb_paths)
		{
			if (new_path[i_f_rooms - 1]->paths[i_paths]->is_used == new_path[i_f_rooms - 1]->is_used - 1)
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
	new_path[i_f_rooms] = s->rooms[s->start];
	i_paths = 0;
	while (i_paths < s->tmp.nb_f_paths)
	{
		new_f_paths[i_paths] = s->tmp.f_paths[i_paths];
		i_paths++;
	}
	new_f_paths[i_paths] = new_path;
	free(s->tmp.f_paths);
	s->tmp.f_paths = new_f_paths;
	s->rooms[s->end].is_used = 0;
	return (s->tmp.nb_f_paths);
}

int		get_quick_path(t_struct *s, int i)
{
	int		map_room;
	int		i_room;
	int		i_used;
	int		i_paths

	i_used = 2;
	s->rooms[s->start].paths[i]->is_used = 2;
	while (s->rooms[s->end].is_used == 0 || map_room != 0)
	{
		i_room = 0;
		map_room = 0;
		while (i_room < s->nb_rooms)
		{
			if (s->rooms[i_room].is_used == i_used)
			{
				i_paths = 0;
				while (i_paths < s->rooms[i_room].nb_paths)
				{
					if (s->rooms[i_room].paths[i_paths]->is_used == 0 &&
							s->rooms[i_room].paths[i_paths]->status != 2)
					{
						s->rooms[i_room].paths[i_paths]->is_used = i_used + 1;
						map_room++;
					}
					i_paths++;
				}
			}
			i_room++;
		}
		i_used++;
	}
	i_paths = insert_path(s);
	return (i_paths);
}

int		get_time_res(int *tab, int nb_paths, int nb_ants)
{
	int		i_tab;
	int		max;
	int		time;
	int		nb_min;

	max = tab[0];
	i_tab = 0;
	while(i_tab < nb_paths)
	{
		if (tab[i_tab] > max)
			max = tab[i_tab];
		i_tab++;
	}
	i_tab = 0;
	while(i_tab < nb_paths)
	{
		nb_ants -= max - tab[i_tab];
		i_tab++;
	}
	time = max + nb_ants / nb_paths;
	if (nb_ants % nb_paths != 0)
		time++;
	return (time);
}

int		replace_res(t_struct *s)
{
	int		i_f_paths;
	int		i_path;

	i_f_paths = 0;
	while (i_f_paths < s->res.nb_f_paths)
	{
		free(s->res.f_paths[i_f_paths])
		i_f_paths++;
	}
	free(s->res.f_paths);
	s->res = s->tmp;
	return (1);
}

int		get_best_paths(t_struct *s)
{
	int		*paths_length;
	int		i_tab;
	int		i;

	if (!(paths_length = (int*)ft_memalloc(sizeof(int) * s->tmp.nb_f_paths)))
		return (0);
	i_tab = 0;
	while (i_tab < nb_f_paths)
	{
		i = 0;
		while (s->tmp.f_paths[i_tab][i] != s->rooms[s->start])
			i++;
		paths_length[i_tab] = i;
		i_tab++;
	}
	if (get_time_res(paths_length, s->tmp.nb_f_paths, s->nb_ants) < s->res.nb_turns)
		replace_res(s);
	free(paths_length);
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
			i_tmp = get_quick_path(s, i); //map the path and add it to t_res tmp in s;
			resolve(s, nb_paths - 1);
			if (!get_best_paths(s))
				return (-1);
			del_paths(s, i_tmp);
		}
		i++;
	}
	return (1);
}
