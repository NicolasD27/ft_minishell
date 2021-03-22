/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 19:58:15 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/22 19:58:26 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_free_char(char *dest, char c, int j)
{
	char	*tmp;
	char	*s;

	if (!(s = malloc(2)))
		return (dest);
	s[0] = c;
	s[1] = '\0';
	dest[j] = '\0';
	tmp = ft_strjoin(dest, s);
	free(dest);
	free(s);
	return (tmp);
}

int		join_sub(char **dest, char *s, int j)
{
	char *tmp;

	(*dest)[j] = '\0';
	tmp = ft_strjoin(*dest, s);
	free(*dest);
	*dest = tmp;
	return (ft_strlen(*dest));
}

int		join_free(char **dest, char *s, int j)
{
	char *tmp;

	(*dest)[j] = '\0';
	tmp = ft_strjoin(*dest, s);
	free(*dest);
	free(s);
	*dest = tmp;
	return (ft_strlen(*dest));
}
