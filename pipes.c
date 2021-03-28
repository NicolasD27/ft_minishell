/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:26:31 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/28 20:34:19 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		array_size(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int		**create_pipefd(t_shell *shell)
{
	int i;
	int **pipefd;

	if (!(pipefd = malloc((array_size(shell->pipes)) * sizeof(int *))))
	{
		free_array(shell->pipes);
		return (NULL);
	}
	i = 0;
	while (shell->pipes[i])
		if (!(pipefd[i++] = malloc(2 * sizeof(int))))
		{
			free(pipefd);
			free_array(shell->pipes);
			return (NULL);
		}
	i = 0;
	while (shell->pipes[i] && shell->pipes[i + 1])
		pipe(pipefd[i++]);
	pipefd[i++][1] = fileno(stdout);
	while (--i > 0)
		pipefd[i][0] = pipefd[i - 1][0];
	pipefd[0][0] = fileno(stdin);
	return (pipefd);
}

void	handle_pipe(t_shell *shell, int i, char ***env, int **pipefd)
{
	int savefd[2];

	savefd[0] = dup(fileno(stdin));
	savefd[1] = dup(fileno(stdout));
	dup2(pipefd[i][0], fileno(stdin));
	dup2(pipefd[i][1], fileno(stdout));
	g_sig.ret = handle_cmds(env, shell->pipes[i], shell);
	close(pipefd[i][0]);
	close(pipefd[i][1]);
	dup2(savefd[0], fileno(stdin));
	dup2(savefd[1], fileno(stdout));
}

int		handle_pipes(char ***env, char *cmd, t_shell *shell)
{
	int i;
	int	**pipefd;

	shell->pipes = split_quoting_set(cmd, "|");
	if (array_size(shell->pipes) > 1)
	{
		if (!(pipefd = create_pipefd(shell)))
			return (1);
		i = 0;
		while (shell->pipes[i])
		{
			handle_pipe(shell, i, env, pipefd);
			i++;
		}
		free_array_int(pipefd, i);
	}
	else
		handle_cmds(env, cmd, shell);
	free_array(shell->pipes);
	return (g_sig.ret);
}
