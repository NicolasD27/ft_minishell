/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_options3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:20:50 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/09 21:27:17 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_dir(char **args, int *i, char ***env)
{
	int		j;
	char	*dir;
	char	*key;
	char	*pwd;

	if ((j = find_env(*env, "ORIGINAL_PWD")) == -1)
	{
		j = find_env(*env, "PWD");
		dehash((*env)[j], &key, &pwd);
		add_env("ORIGINAL_PWD", pwd, env);
	}
	else
	{
		dehash((*env)[j], &key, &pwd);
		ft_chdir(pwd, env);
	}
	free(pwd);
	free(key);
	dir = find_arg(args, i, 'C');
	if (dir)
		found_dir(env, dir);
	else
		return (-1);
	return (0);
}

void	found_dir(char ***env, char *dir)
{
	int j;

	if ((j = find_env(*env, "chdir")) != -1)
		rehash(env, j, "chdir", dir);
	else
		add_env("chdir", dir, env);
	ft_chdir(dir, env);
	free(dir);
}

char	*find_arg(char **args, int *i, char c)
{
	char	*arg;
	int		j;

	if (args[*i][1] == '-')
	{
		if ((j = index_of(args[*i], '=')) != -1)
			arg = ft_strdup(args[*i] + j + 1);
		else if (args[*i + 1])
			arg = ft_strdup(args[++*i]);
		else
			arg = NULL;
	}
	else
	{
		j = index_of(args[*i], c);
		if (args[*i][j + 1])
			arg = ft_strdup(args[*i] + j + 1);
		else if (args[*i + 1])
			arg = ft_strdup(args[++*i]);
		else
			arg = NULL;
	}
	return (arg);
}

int		unset(char **args, int *i, char ***env)
{
	int		j;
	char	*key;

	key = find_arg(args, i, 'u');
	if (key)
	{
		if ((j = find_env(*env, key)) != -1)
			remove_env(env, j);
		add_unset(env, key);
	}
	else
		return (-1);
	return (0);
}

void	add_unset(char ***env, char *key)
{
	char	*unsetted;
	char	*tmp;
	int		j;

	if ((j = find_env(*env, "unset")) != -1)
	{
		dehash((*env)[j], &tmp, &unsetted);
		free(tmp);
		tmp = ft_strjoin(unsetted, ":");
		free(unsetted);
		unsetted = ft_strjoin(tmp, key);
		rehash(env, j, "unset", unsetted);
		free(unsetted);
	}
	else
		add_env("unset", key, env);
	free(key);
}
