/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:20:22 by mokhames          #+#    #+#             */
/*   Updated: 2019/10/21 17:32:30 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*e;

	i = 0;
	e = (char *)s;
	while (*e != c)
	{
		if (*e == '\0')
			return (NULL);
		e++;
	}
	return (e);
}
