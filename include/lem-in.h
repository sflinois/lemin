#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"

/*
**		The 'status' attribute is used to know wich type of room
**		we are in (1 : normal room) (2 : start room) (3 : end room)
**
**		The 'dist' attribute is used to know the distance from the
**		current room to the end room
**
**		algo : avec n possibles chemins, recherche des plus court chemins en partant des n possibilite de depart
**		si intersections, recherche de chemins plus court en evitant l'intersection
*/

typedef struct		s_room
{
	char			*name;
	char			*x;
	char			*y;
	int				status;
	int				is_used;
	struct s_room	**paths;
	int				nb_paths;
	int				ant;
	int				ants_left;
}					t_room;

typedef struct		s_res
{
	int				nb_f_paths;
	int				nb_turns;
	t_room			***f_paths;
	int				*nb_ants_path;
}					t_res;

typedef struct		s_struct
{
	int				nb_ants;
	int				nb_rooms;
	int				start;
	int				end;
	t_room			*rooms;
	t_res			tmp;
	t_res			res;
}					t_struct;

void		print_rooms(t_struct *s);
void		print_res(t_res res, t_struct *s);
void		print_path(t_room** path, int length);
void		init_struct(t_struct *s);
int			pars_args(int argc, char **argv, t_struct *s);
int			is_room_line(char *line);
int			is_path_line(char *line);
int			is_room_dup(t_struct *s, t_room room);
int			insert_path(char *line, t_struct *s);
int			insert_room(char *line, t_struct *s, int place);
int			resolve(t_struct *s, int nb_paths);
#endif
