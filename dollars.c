/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:25:09 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/22 20:00:00 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_dollar(char **arg, int j, char *rep, int offset)
{
	int		len;
	char	*tmp;

	len = ft_strlen(rep);
	if (!(tmp = malloc(ft_strlen(*arg) + len - offset + 1)))
		return ;
	ft_strlcpy(tmp, *arg, j + 1);
	ft_strlcpy(tmp + j, rep, len + 1);
	ft_strlcpy(tmp + j + len, *arg + j + offset,
			ft_strlen(*arg) - j - offset + 1);
	free(*arg);
	*arg = tmp;
}

char	*not_in_env(char *tmp)
{
	int		i;
	char	*value;

	i = 0;
	while (ft_isdigit(tmp[i]))
		i++;
	if (i > 0)
		value = ft_strdup(tmp + i);
	else
		value = ft_strdup("");
	free(tmp);
	return (value);
}

char	*replace_dollar_env(char *arg, char **env, int *j)
{
	int		i;
	char	*key;
	char	*value;
	char	*tmp;

	if (!(tmp = malloc((1 + ft_strlen(arg + 1)) * sizeof(char))))
		return (ft_strdup(""));
	i = 0;
	while (arg[++i] && ft_isalnum(arg[i]))
		tmp[i - 1] = arg[i];
	*j += i - 1;
	tmp[i - 1] = '\0';
	if ((i = find_env(env, tmp)) == -1)
		return (not_in_env(tmp));
	else
	{
		free(tmp);
		dehash(env[i], &key, &value);
		free(key);
		return (value);
	}
}

char	*dollar_found(char *arg, char **env, int *i)
{
	char *rep;

	if (arg[*i + 1] == '?')
	{
		rep = ft_itoa(g_sig.ret);
		*i += 1;
		return (rep);
	}
	else if (arg[*i + 1]
			&& arg[*i + 1] != '"'
			&& arg[*i + 1] != '\'')
		return (replace_dollar_env(arg + *i, env, i));
	return ("$");
}
