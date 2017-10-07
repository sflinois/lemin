#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"

typedef struct		s_room
{
	char		*name;
	char		*x;
	char		*y;
	int		status;
	char		**paths;
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
	int		start;
	int		end;
	t_room		*rooms;
	t_ant		*ants;
}			t_struct;

void			print_rooms(t_struct *s);
void			init_struct(t_struct *s);
int			pars_args(int argc, char **argv, t_struct *s);
int			is_room_line(char *line);
int			is_path_line(char *line);
int			insert_path(char *line, t_struct *s);
int			insert_room(char *line, t_struct *s, int place);
#endif
