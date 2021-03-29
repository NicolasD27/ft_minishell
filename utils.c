/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:12:29 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/29 11:59:37 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char				**when_empty(void)
{
	char **res;

	if ((res = malloc(sizeof(char *))) == NULL)
		return (NULL);
	res[0] = NULL;
	return (res);
}

static char			**free_res(char **res, int i)
{
	while (i > 0)
		free(res[--i]);
	free(res);
	return (NULL);
}

char				*clean_trim(char *s, char *set, int j)
{
	char *tmp;

	tmp = ft_strtrim(s + j, set);
	free(s);
	s = tmp;
	return (s);
}

char				**split_words_quoting(char *sclean, int nb, char *set)
{
	char	**res;
	int		j;
	int		i;
	int		quote[2];

	quote[0] = 0;
	quote[1] = 0;
	if ((res = malloc((nb + 1) * sizeof(char *))) == NULL)
		return (NULL);
	i = -1;
	while (++i < nb)
	{
		j = -1;
		while (sclean[++j] && ((sclean[j] != set[0] && sclean[j] != set[1])
					|| (quote[0] % 2 != 0 || quote[1] % 2 != 0)))
			is_quote(sclean[j], quote, quote + 1);
		if ((res[i] = ft_substr(sclean, 0, j)) == NULL)
			return (free_res(res, i));
		sclean = clean_trim(sclean, set, j);
	}
	res[i] = NULL;
	free(sclean);
	return (res);
}

char				**split_quoting_set(char const *s, char *set)
{
	char	*sclean;
	int		nb;
	char	**splits;

	if (!s)
		return (NULL);
	if (!s[0])
		return (when_empty());
	sclean = ft_strtrim(s, set);
	sclean = clean_trim(sclean, " ", 0);
	nb = nb_of_splits_quoting(s, set);
	splits = split_words_quoting(sclean, nb, set);
	return (splits);
}
