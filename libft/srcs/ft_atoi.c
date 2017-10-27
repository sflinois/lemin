/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:25:19 by sflinois          #+#    #+#             */
/*   Updated: 2017/10/27 16:38:58 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		nb;
	int		neg;

	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	neg = 1;
	if (*str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	i = 0;
	nb = 0;
	if (str[i] >= '0' && str[i] <= '9')
		nb = str[i++] - '0';
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb *= 10;
		nb += str[i] - '0';
		i++;
	}
	return (ft_strlen(str) > 10 || (ft_strlen(str) > 9 && ((neg == 1 &&
		nb < 1000000000) || (neg == -1 && nb < -1000000000))) ? 0 : nb * neg);
}
