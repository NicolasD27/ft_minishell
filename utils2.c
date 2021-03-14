/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 01:31:36 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/12 20:03:28 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_env(char **env, char *target)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (env[i])
	{
		dehash(env[i], &key, &value);
		free(value);
		if (!ft_strcmp(key, target))
		{
			free(key);
			return (i);
		}
		free(key);
		i++;
	}
	return (-1);
}

void	is_quote(char c, int *squote, int *dquote)
{
	if (c == '"')
		*dquote += 1;
	else if (c == '\'')
		*squote += 1;
}

int		nb_of_splits_quoting(char const *s, char *set)
{
	int nb;
	int i;
	int diff;
	int dqu;
	int squ;

	nb = 0;
	i = -1;
	diff = 0;
	dqu = 0;
	squ = 0;
	while (s[++i])
	{
		if (s[i] == set[0] || s[i] == set[1])
		{
			if (diff == 1 && dqu % 2 == 0 && squ % 2 == 0 && (diff = 0) == 0)
				nb++;
		}
		else
			diff = 1;
		is_quote(s[i], &squ, &dqu);
	}
	if (s[i - 1] != set[0] && s[i - 1] != set[1])
		nb++;
	return (nb);
}
