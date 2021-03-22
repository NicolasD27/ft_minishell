/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:28:51 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/22 21:10:47 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unsetenv(char **args, char ***env, t_shell *shell)
{
	int		i;
	int		j;

	j = 1;
	while (args[j])
	{
		if ((i = find_env(*env, args[j])) != -1)
			remove_env(env, i);
		else if ((i = find_env(shell->exports, args[j])) != -1)
			remove_env(&(shell->exports), i);
		j++;
	}
}

void	export_pair(char **pair, char ***env, t_shell *shell)
{
	int		j;
	char	*value;

	value = ft_strtrim(pair[1], "'\"");
	free(pair[1]);
	pair[1] = value;
	if ((j = find_env(*env, pair[0])) != -1)
		rehash(env, j, pair[0], pair[1]);
	else
	{
		if ((j = find_env(shell->exports, pair[0])) != -1)
		{
			remove_env(&(shell->exports), j);
			add_env(pair[0], pair[1], env);
		}
		else
			add_env(pair[0], pair[1], env);
	}
}

void	export_null(char *arg, char **pair, t_shell *shell, char ***env)
{
	int i;

	if ((i = find_env(*env, pair[0])) != -1)
	{
		if (arg[ft_strlen(arg) - 1] == '=')
			rehash(env, i, pair[0], "");
	}
	else if ((i = find_env(shell->exports, pair[0])) != -1)
	{
		if (arg[ft_strlen(arg) - 1] == '=')
		{
			remove_env(&(shell->exports), i);
			add_env(pair[0], NULL, env);
		}
	}
	else
	{
		if (arg[ft_strlen(arg) - 1] == '=')
			add_env(pair[0], NULL, env);
		else
			add_env(pair[0], NULL, &(shell->exports));
	}
}

int		export_arg(char *arg, char ***env, t_shell *shell)
{
	char	**pair;
	char	*tmp;

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
		export_null(arg, pair, shell, env);
	else
		export_pair(pair, env, shell);
	free_array_n(pair, 2);
	return (0);
}

int		ft_export(t_shell *shell, char ***env)
{
	int i;

	if (!shell->args[1])
		print_env_export(*env, shell->exports);
	else
	{
		i = 0;
		while (shell->args[++i])
			if (export_arg(shell->args[i], env, shell) == 1)
				return (1);
	}
	return (0);
}
