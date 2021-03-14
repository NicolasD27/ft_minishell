/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:43:51 by nidescre          #+#    #+#             */
/*   Updated: 2021/01/21 19:28:18 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_options(int **options, char **args, int *i, char ***env)
{
	if ((*options)[10])
		return (print_unrecog_option(args[*i]));
	else if ((*options)[9])
		return (print_invalid_option(args[*i]));
	else if ((*options)[6])
		return (print_env_version());
	else if ((*options)[5])
		return (print_env_help());
	else
		return (exec_options2(options, args, i, env));
	return (0);
}

int		exec_options2(int **options, char **args, int *i, char ***env)
{
	if ((*options)[0] == 1)
		empty_env(env, options);
	if ((*options)[2])
	{
		(*options)[2] = 0;
		if (unset(args, i, env) == -1)
			return (print_no_arg_unset());
	}
	if ((*options)[3])
	{
		(*options)[3] = 0;
		if (find_dir(args, i, env) == -1)
			return (print_no_arg_chdir());
	}
	return (0);
}

int		print_no_arg_chdir(void)
{
	write(2, "env: option requires an argument -- 'C'\n\
			Try 'env --help' for more information.\n", 79);
	return (-1);
}

int		print_no_arg_unset(void)
{
	write(2, "env: option requires an argument -- 'u'\n\
			Try 'env --help' for more information.\n", 79);
	return (-1);
}

void	empty_env(char ***env, int **options)
{
	int		j;
	char	*key;
	char	*pwd;

	(*options)[0] = 2;
	j = find_env(*env, "PWD");
	dehash((*env)[j], &key, &pwd);
	free_array(*env);
	if (!(*env = malloc(sizeof(char *))))
		return ;
	(*env)[0] = NULL;
	add_env("ORIGINAL_PWD", pwd, env);
	free(key);
	free(pwd);
}
