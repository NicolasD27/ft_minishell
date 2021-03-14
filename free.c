/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 20:03:12 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/14 17:39:53 by nidescre         ###   ########.fr       */
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

void	free_half(t_shell *shell, char **env)
{
	free(shell->cmd);
	free_array(env);
	free_array_n(shell->history, 1024);
	free(g_sig.cur_cmd);
	exit(EXIT_SUCCESS);
}
