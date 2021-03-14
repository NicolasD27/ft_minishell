/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:28:24 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/13 17:44:09 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_redir(t_shell *shell, int redir, int *fa, int *fb)
{
	if (redir > 0)
	{
		if (redir == 2)
			*fa = open(shell->filename, O_RDWR | O_CREAT | O_APPEND, 0600);
		else
			*fa = open(shell->filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
		if (*fa == -1)
			return (fd_error(shell->filename));
		*fb = dup(fileno(stdout));
		dup2(*fa, fileno(stdout));
	}
	else if (redir == -1)
	{
		*fa = open(shell->filename, O_RDONLY, 0600);
		if (*fa == -1)
		{
			free_array(shell->args);
			free_array(shell->paths);
			return (fd_error(shell->filename));
		}
		*fb = dup(fileno(stdin));
		dup2(*fa, fileno(stdin));
	}
	return (0);
}

void	clear_cmd(t_shell *shell, int *fd, int redir)
{
	if (shell->filename)
	{
		close(fd[0]);
		if (redir > 0)
			dup2(fd[1], fileno(stdout));
		else if (redir == -1)
			dup2(fd[1], fileno(stdin));
		close(fd[1]);
	}
	free(shell->filename);
	free_array(shell->args);
	free_array(shell->paths);
}

int		parse_error(t_shell *shell)
{
	free_array(shell->args);
	free_array(shell->paths);
	write(1, "parse error near `\n'\n", 21);
	return (1);
}

int		handle_cmds(char ***env, char *cmd, t_shell *shell)
{
	int		fd[2];
	int		redir;

	redir = 0;
	ft_strcpy(g_sig.cur_cmd, cmd);
	shell->args = split_quoting_set(cmd, " \t");
	if (handle_quote(&(shell->args), *env) != -1)
	{
		shell->paths = get_paths(*env);
		shell->filename = find_redirections(&(shell->args), &redir);
		if (redir == 666)
			return (parse_error(shell));
		if (shell->filename)
			if (handle_redir(shell, redir, fd, fd + 1) == 1)
				return (1);
		if (shell->args[0])
			g_sig.ret = route_cmd(env, shell);
	}
	clear_cmd(shell, fd, redir);
	return (g_sig.ret);
}
