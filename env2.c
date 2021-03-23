/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:42:13 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/23 15:50:50 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		interpret_option(char **args, int *i, char ***env, int **options)
{
	int	j;
	int	o;

	if (args[*i][1] == '-')
		is_long_option(args[*i], options);
	else
	{
		j = 1;
		while (args[*i][j])
		{
			o = is_short_option(args[*i][j]);
			(*options)[o] += 1;
			j++;
			if (o == 2 || o == 3)
				break ;
		}
	}
	if (exec_options(options, args, i, env) == -1)
	{
		free(*options);
		free_array(*env);
		return (-1);
	}
	return (0);
}

void	printf_env(char **env, int *options)
{
	int i;

	i = 0;
	while (env[i])
	{
		write(1, env[i], ft_strlen(env[i]));
		if (!options[1])
			write(1, "\n", 1);
		i++;
	}
}

int		chdir_env(char **env, char *target)
{
	int		n;
	char	*key;
	char	*dir;

	n = find_env(env, target);
	dehash(env[n], &key, &dir);
	chdir(dir);
	free(key);
	free(dir);
	return (0);
}

int		print_env_version(void)
{
	write(2, "env (GNU coreutils) 8.30\n\
Copyright (C) 2018 Free Software Foundation, Inc.\n\
License GPLv3+: GNU GPL version 3 or later \
<https://gnu.org/licenses/gpl.html>.\nThis is free software: \
you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\n\
Written by Richard Mlynarik, David MacKenzie, \
and Assaf Gordon.\n", 342);
	return (-1);
}

int		print_env_help(void)
{
	write(2, "Usage: env [OPTION]... [-] [NAME=VALUE]... [COMMAND [ARG]...]\n\
Set each NAME to VALUE in the environment and run COMMAND.\n\n\
Mandatory arguments to long options are mandatory for short \
options too.\n\
-i, --ignore-environment  start with an empty environment\n\
-0, --null           end each output line with NUL, not newline\n\
-u, --unset=NAME     remove variable from the environment\n\
-C, --chdir=DIR      change working directory to DIR\n\
-S, --split-string=S  process and split S into separate \
arguments;\nused to pass multiple arguments on shebang lines\n\
-v, --debug          print verbose information for each \
processing step\n--help     display this help and exit\n\
--version  output version information and exit\n\n\
A mere - implies -i.  If no COMMAND, print the resulting environment.\n\n\
GNU coreutils online help: \
<https://www.gnu.org/software/coreutils/>\nFull documentation \
at: <https://www.gnu.org/software/coreutils/env>\n\
or available locally via: info '(coreutils) env invocation'\n", 971);
	return (-1);
}
