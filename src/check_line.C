/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 19:28:02 by sflinois          #+#    #+#             */
/*   Updated: 2017/10/29 17:12:56 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/includes/libft.h"

int	is_room_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isprint(line[i]) && line[i] != '-' &&
			line[i] != ' ' && line[i] != '#')
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '-' || ft_isdigit(line[i]))
		i += line[i + 1] == '-' ? 2 : 1;
	else
		return (0);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '-' || ft_isdigit(line[i]))
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
	while (line[i] && ft_isprint(line[i]) && line[i] != '-' &&
			line[i] != ' ' && line[i] != '#')
		i++;
	if (line[i] && line[i] == '-' && line[i + 1])
		i++;
	else
		return (0);
	while (line[i] && ft_isprint(line[i]) && line[i] != '-' &&
			line[i] != ' ' && line[i] != '#')
		i++;
	return (line[i] == '\0' ? 4 : 0);
}

int	is_room_dup(t_struct *s, t_room room)
{
	int		i;

	i = 0;
	while (i < s->nb_rooms)
	{
		if (ft_strcmp(s->rooms[i].name, room.name) == 0)
			return (1);
		if (ft_strcmp(s->rooms[i].x, room.x) == 0 &&
				ft_strcmp(s->rooms[i].y, room.y) == 0)
			return (1);
		i++;
	}
	return (0);
}
