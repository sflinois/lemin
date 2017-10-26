#include "../include/lem-in.h"
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
	while(i < s->nb_rooms)
	{
		ft_printf("(%s) - [%i] - [%i] - [%i]=> ", s->rooms[i].name, s->rooms[i].is_used, s->rooms[i].ant, s->rooms[i].ants_left);
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
		//ft_printf("path p : %p\n", res.f_paths[i]);
		while(res.f_paths[i][j] != &s->rooms[s->start])
		{
			ft_printf("[%s, %i] ", res.f_paths[i][j]->name, res.f_paths[i][j]->is_used, res.f_paths[i][j]);
			j++;
		}
		ft_printf("[%s, %i]\n", res.f_paths[i][j]->name, res.f_paths[i][j]->is_used, res.f_paths[i][j]);
		i++;
	}
	ft_printf("------------\n");

}

void	print_path(t_room** path, int length)
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
