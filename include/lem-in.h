#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"

typedef struct		s_room
{
	char		*name;
	int		x;
	int		y;
	int		status;
	char		**paths;
	struct s_room	*next;
}			t_room;

typedef struct		s_ant
{
	int		num;
	int		x;
	int		y;
}			t_ant;

typedef struct		s_struct
{
	int		nb_ants;
	int		nb_rooms;
	t_room		*rooms;
	t_ant		*ants;
}			t_struct;

void			init_struct(t_struct *s);
int			pars_args(int argc, char **argv, t_struct *s);

#endif
