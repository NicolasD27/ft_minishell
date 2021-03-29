/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:05:19 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/29 14:03:03 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell)
{
	int i;

	shell->exports = NULL;
	shell->paths = NULL;
	if (!(shell->history = malloc(1024 * sizeof(char *))))
		return ;
	i = -1;
	while (++i < 1024)
		if (!(shell->history[i] = malloc(2048)))
			return ;
	shell->his_n = 0;
}

int		main(int argc, char **argv, char **env)
{
	t_shell	shell;
	char	**env_copy;

	(void)argc;
	(void)argv;
	env_copy = copy_array(env);
	signal(SIGINT, &int_handler);
	signal(SIGQUIT, &quit_handler);
	g_sig.ret = 0;
	g_sig.sigint = 1;
	if (!(g_sig.cur_cmd = malloc(2048)))
		return (1);
	init_shell(&shell);
	init_termcap();
	while (1)
		if (shell_loop(&env_copy, &shell) == 1)
			return (1);
	return (0);
}

int		semi_colon_error(char *cmd)
{
	int i;
	int c;

	c = 0;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == ';')
		{
			if (c == 0)
			{
				if (cmd[i + 1] == ';' || (i > 0 && cmd[i - 1] == ';'))
					ft_putstr_fd("bash: syntax error near unexpected token\
							`;;'\n", 1);
				else
					ft_putstr_fd("bash: syntax error near unexpected token\
							`;'\n", 1);
				return (0);
			}
			c = 0;
		}
		else if (cmd[i] != ' ')
			c = 1;
	}
	return (1);
}

void	write_prompt(void)
{
	char	*pwd;
	char	**dirs;
	int		i;

	if (g_sig.ret == 0)
		ft_putstr_fd("\033[1;32m➜  ", 2);
	else
		ft_putstr_fd("\033[1;31m➜  ", 2);
	if (!(pwd = malloc(2048)))
		return ;
	getcwd(pwd, 2048);
	dirs = ft_split(pwd, '/');
	i = 0;
	while (dirs[i])
		i++;
	ft_putstr_fd("\033[1;34m", 2);
	if (i == 0)
		ft_putstr_fd("/", 2);
	else
		ft_putstr_fd(dirs[i - 1], 2);
	ft_putstr_fd("\033[0m ", 2);
	free_array(dirs);
	free(pwd);
}

int		shell_loop(char ***env, t_shell *shell)
{
	int		i;

	g_sig.pid = 0;
	g_sig.sigquit = 0;
	write_prompt();
	shell->cmd = get_cmd(*env, shell);
	if (shell->cmd[0])
		ft_strcpy(shell->history[shell->his_n++], shell->cmd);
	shell->cmds = split_quoting_set(shell->cmd, ";");
	if (semi_colon_error(shell->cmd))
	{
		free(shell->cmd);
		i = -1;
		while (shell->cmds[++i])
			g_sig.ret = handle_pipes(env, shell->cmds[i], shell);
	}
	else
		free(shell->cmd);
	free_array(shell->cmds);
	return (0);
}
