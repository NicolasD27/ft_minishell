/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:38:53 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/23 15:52:03 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_verbose(char **args, int *options, char **env)
{
	int		n;
	char	*key;
	char	*value;

	if (options[0] > 0)
		write(2, "cleaning environ\n", 17);
	print_unset(options, env);
	if ((n = find_env(env, "chdir")) != -1)
	{
		dehash(env[n], &key, &value);
		write(2, "chdir:  '", 9);
		write(2, value, ft_strlen(value));
		write(2, "'\n", 2);
		free(key);
		free(value);
	}
	print_args(args);
}

void	print_unset(int *options, char **env)
{
	char	*key;
	char	*value;
	char	**unsetted;
	int		n;

	if (!options[0] && ((n = find_env(env, "unset")) != -1))
	{
		dehash(env[n], &key, &value);
		unsetted = ft_split(value, ':');
		n = 0;
		while (unsetted[n])
		{
			write(2, "unset:  ", 8);
			write(2, unsetted[n], ft_strlen(unsetted[n]));
			write(2, "\n", 1);
			n++;
		}
		free(key);
		free(value);
		free_array(unsetted);
	}
}

void	print_args(char **args)
{
	int n;

	if (args[0])
	{
		write(2, "executing: ", 11);
		write(2, args[0], ft_strlen(args[0]));
		write(2, "\n", 1);
		n = 1;
		while (args[n])
		{
			write(2, "  arg[", 5);
			ft_putnbr_fd(n, 1);
			write(2, "]= '", 4);
			write(2, args[n], ft_strlen(args[n]));
			write(2, "'\n", 2);
			n++;
		}
	}
}

void	print_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
}
