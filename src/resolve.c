#include "../include/lem-in.h"
#include "../libft/includes/libft.h"

int		resolve(t_struct *s, int nb_paths)
{
	int		i;
	int		i_tmp;

	if (nb_paths > 0)
		return (0);
	i = 0;
	while (i < s->rooms[s->start].nb_paths)
	{
		if (!s->rooms[s->start].paths[i]->is_used)
		{
			i_tmp = get_quick_path(s, i); //map the path and add it to t_res tmp in s;
			resolve(s, nb_paths - 1);
			get_best_paths(s);
			del_paths(s, i_tmp);
		}
	}
	return (1);
}
