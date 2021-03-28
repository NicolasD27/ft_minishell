/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 20:03:12 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/28 19:48:04 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array_n(char **arr, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_array_int(int **arr, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_half(t_shell *shell, char **env, char *cmd)
{
	free(cmd);
	free_array(env);
	free_array_n(shell->history, 1024);
	free(g_sig.cur_cmd);
	if (shell->exports)
		free_array(shell->exports);
	ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
}

void	free_all(t_shell *shell, char **env, int code)
{
	free(shell->cmd);
	free_array(env);
	free(g_sig.cur_cmd);
	free_array(shell->cmds);
	if (shell->paths)
		free_array(shell->paths);
	free_array(shell->args);
	free_array(shell->pipes);
	free(shell->filename);
	if (shell->exports)
		free_array(shell->exports);
	free_array_n(shell->history, 1024);
	exit(code);
}
