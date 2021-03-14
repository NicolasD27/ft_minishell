/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:38:53 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/09 21:27:40 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_verbose(char **args, int *options, char **env)
{
	int		n;
	char	*key;
	char	*value;

	if (options[0] > 0)
		write(1, "cleaning environ\n", 17);
	print_unset(options, env);
	if ((n = find_env(env, "chdir")) != -1)
	{
		dehash(env[n], &key, &value);
		write(1, "chdir:  '", 9);
		write(1, value, ft_strlen(value));
		write(1, "'\n", 2);
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
			write(1, "unset:  ", 8);
			write(1, unsetted[n], ft_strlen(unsetted[n]));
			write(1, "\n", 1);
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
		write(1, "executing: ", 11);
		write(1, args[0], ft_strlen(args[0]));
		write(1, "\n", 1);
		n = 1;
		while (args[n])
		{
			write(1, "  arg[", 5);
			ft_putnbr_fd(n, 1);
			write(1, "]= '", 4);
			write(1, args[n], ft_strlen(args[n]));
			write(1, "'\n", 2);
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
