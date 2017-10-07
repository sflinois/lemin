#include "../include/lem-in.h"
#include "../libft/includes/libft.h"

int	is_room_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isprint(line[i]) && line[i] != '-' && line[i] != ' ' && line[i] != '#')
		i++;
	if (line[i] && line[i] == ' ' && (line[i + 1] == '-' || ft_isdigit(line[i + 1])))
		i += line[i + 1] == '-' ? 2 : 1;
	else
		return (0);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (line[i] && line[i] == ' ' && (line[i + 1] == '-' || ft_isdigit(line[i + 1])))
		i += line[i + 1] == '-' ? 2 : 1;
	else
		return (0);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	return (line[i] == '\0' ? 1 : 0);
}

int	is_path_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isprint(line[i]) && line[i] != '-' && line[i] != ' ' && line[i] != '#')
		i++;
	if (line[i] && line[i] == '-' && line[i + 1])
		i++;
	else
		return (0);
	while (line[i] && ft_isprint(line[i]) && line[i] != '-' && line[i] != ' ' && line[i] != '#')
		i++;
	return (line[i] == '\0' ? 4 : 0);
}
