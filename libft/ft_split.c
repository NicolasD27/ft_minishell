/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:43:21 by nidescre          #+#    #+#             */
/*   Updated: 2021/01/15 22:25:45 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		nb_of_splits(char const *s, char c)
{
	int nb;
	int i;
	int diff;

	nb = 0;
	i = 0;
	diff = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (diff == 1)
			{
				nb++;
				diff = 0;
			}
		}
		else
			diff = 1;
		i++;
	}
	if (s[i - 1] != c)
		nb++;
	return (nb);
}

static char		**when_empty(void)
{
	char **res;

	if ((res = malloc(sizeof(char *))) == NULL)
		return (NULL);
	res[0] = NULL;
	return (res);
}

char			**free_res(char **res, int i)
{
	while (i > 0)
		free(res[--i]);
	free(res);
	return (NULL);
}

char			**split_words(char *sclean, char c, int nb, char *set)
{
	char	**res;
	int		len;
	int		i;
	char	*tmp;

	if ((res = malloc((nb + 1) * sizeof(char *))) == NULL)
		return (NULL);
	i = 0;
	while (i < nb)
	{
		len = 0;
		while (sclean[len] != c && sclean[len])
			len++;
		if ((res[i] = ft_substr(sclean, 0, len)) == NULL)
			return (free_res(res, i));
		tmp = ft_strtrim(sclean + len, set);
		free(sclean);
		sclean = tmp;
		i++;
	}
	res[i] = NULL;
	free(sclean);
	return (res);
}

char			**ft_split(char const *s, char c)
{
	char	*sclean;
	char	set[2];
	int		nb;
	char	**splits;

	set[0] = c;
	set[1] = '\0';
	if (!s)
		return (NULL);
	if (!s[0])
		return (when_empty());
	sclean = ft_strtrim(s, set);
	nb = nb_of_splits(s, c);
	splits = split_words(sclean, c, nb, set);
	return (splits);
}
