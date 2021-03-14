/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:39:20 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/11 16:22:09 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(char **env, t_shell *shell)
{
	int		*options;
	int		i;
	int		o;
	char	**copy;
	char	****en_cp;

	copy = copy_array(env);
	if (!(en_cp = malloc(2 * sizeof(char ***))))
		return (12);
	en_cp[0] = &env;
	en_cp[1] = &copy;
	if (!(options = ft_calloc(11, sizeof(int))))
		return (12);
	i = 0;
	while (shell->args[++i])
	{
		if ((o = env_loop(en_cp, shell, &options, &i)) == -1)
			break ;
		else if (o == 0)
			return (125);
	}
	free(en_cp);
	env_end(&options, env, copy, shell->args + i);
	free(options);
	return (g_sig.ret);
}

int		env_loop(char ****en_cp, t_shell *shell, int **options, int *i)
{
	char **args_copy;

	if (shell->args[*i][0] == '-' && (*options)[7] == 0)
	{
		if (interpret_option(shell->args, i, en_cp[1], options) == -1)
			return (chdir_env(*en_cp[0], "PWD"));
	}
	else if (index_of(shell->args[*i], '=') != -1)
	{
		(*options)[7] = 1;
		add_env_hashed(shell->args[*i], en_cp[1]);
	}
	else
	{
		(*options)[8] = 1;
		if ((*options)[4])
			print_verbose(shell->args + *i, *options, *en_cp[1]);
		restore_env(en_cp[0]);
		args_copy = copy_array(shell->args + *i);
		free_array(shell->args);
		shell->args = args_copy;
		g_sig.ret = route_cmd(en_cp[1], shell);
		return (-1);
	}
	return (1);
}

void	env_end(int **options, char **env, char **copy, char **args)
{
	int o;

	if (!(*options)[8])
	{
		if ((o = find_env(copy, "chdir")) != -1)
		{
			(*options)[11] = 125;
			write(2, "env: must specify command with --chdir (-C)\n\
Try 'env --help' for more information.\n", 83);
		}
		else
		{
			if ((*options)[4])
				print_verbose(args, *options, copy);
			restore_env(&copy);
			printf_env(copy, *options);
		}
	}
	free_array(copy);
	chdir_env(env, "PWD");
}

void	restore_env(char ***env)
{
	int n;

	if ((n = find_env(*env, "ORIGINAL_PWD")) != -1)
		remove_env(env, n);
	if ((n = find_env(*env, "unset")) != -1)
		remove_env(env, n);
	if ((n = find_env(*env, "chdir")) != -1)
		remove_env(env, n);
}

char	**copy_array(char **array)
{
	int		i;
	char	**copy_array;

	i = 0;
	while (array[i])
		i++;
	if (!(copy_array = malloc((i + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	while (array[i])
	{
		copy_array[i] = ft_strdup(array[i]);
		i++;
	}
	copy_array[i] = NULL;
	return (copy_array);
}
