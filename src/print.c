#include "../include/lem-in.h"
#include "../libft/includes/libft.h"

void	print_rooms(t_struct *s)
{
	int	i;
	
	i = 0;
	ft_printf("-- PRINT STRUCT --\n");
	ft_printf("nb_ants : %i\n", s->nb_ants);
	ft_printf("nb_rooms : %i\n", s->nb_rooms);
	ft_printf("start : %i\n", s->start);
	ft_printf("end : %i\n", s->end);
	ft_printf("(NAME) - (X) - (Y) - (STATUS)\n");
	while(i < s->nb_rooms)
	{
		ft_printf("(%s) - (%s) - (%s) - (%i)\n", s->rooms[i].name, s->rooms[i].x, s->rooms[i].y, s->rooms[i].status);
		i++;
	}
}
