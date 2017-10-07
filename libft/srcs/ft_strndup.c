/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 10:44:36 by sflinois          #+#    #+#             */
/*   Updated: 2017/03/18 16:44:13 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "../includes/libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*ret;

	ret = ft_strnew(n);
	if (!ret)
		return (NULL);
	ret = ft_strncpy(ret, s1, n);
	return (ret);
}
