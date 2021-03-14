/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:28:51 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/12 18:52:21 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unsetenv(char **args, char ***env)
{
	int		i;

	if (args[1])
	{
		if ((i = find_env(*env, args[1])) != -1)
			remove_env(env, i);
	}
}

void	export_pair(char **pair, char ***env)
{
	char	*key;
	char	*value;
	int		j;

	value = ft_strtrim(pair[1], "'\"");
	free(pair[1]);
	pair[1] = value;
	j = -1;
	while ((*env)[++j])
	{
		dehash((*env)[j], &key, &value);
		if (ft_strcmp(key, pair[0]) == 0)
		{
			free(key);
			free(value);
			rehash(env, j, pair[0], pair[1]);
			break ;
		}
		free(key);
		free(value);
	}
	if (!(*env)[j])
		add_env(pair[0], pair[1], env);
}

int		export_arg(char *arg, char ***env)
{
	char	**pair;
	char	*tmp;
	int		i;

	if (arg[0] == '=')
	{
		write(1, "wrong argument\n", 15);
		return (1);
	}
	pair = ft_split(arg, '=');
	tmp = ft_strtrim(pair[0], "'\"");
	free(pair[0]);
	pair[0] = tmp;
	if (!pair[1])
	{
		if ((i = find_env(*env, pair[0])) != -1)
			rehash(env, i, pair[0], "");
		else
			add_env(pair[0], NULL, env);
	}
	else
		export_pair(pair, env);
	free_array_n(pair, 2);
	return (0);
}

int		ft_export(char **args, char ***env)
{
	int i;

	if (!args[1])
		print_env(*env);
	else
	{
		i = 0;
		while (args[++i])
			if (export_arg(args[i], env) == 1)
				return (1);
	}
	return (0);
}
