/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:05:19 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/13 23:28:19 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_shell	shell;
	char	**env_copy;
	int		i;

	(void)argc;
	(void)argv;
	env_copy = copy_array(env);
	signal(SIGINT, &int_handler);
	signal(SIGQUIT, &quit_handler);
	g_sig.ret = 0;
	g_sig.sigint = 1;
	if (!(g_sig.cur_cmd = malloc(2048)))
		return (1);
	if (!(shell.history = malloc(1024 * sizeof(char *))))
		return (1);
	i = -1;
	while (++i < 1024)
		if (!(shell.history[i] = malloc(2048)))
			return (1);
	shell.his_n = 0;
	init_termcap();
	while (1)
		if (shell_loop(&env_copy, &shell) == 1)
			return (1);
	return (0);
}

int		shell_loop(char ***env, t_shell *shell)
{
	int		i;

	g_sig.pid = 0;
	g_sig.sigquit = 0;
	write(2, "$> ", 3);
	if (!(shell->cmd = malloc(2048)))
		return (1);
	get_cmd(shell->cmd, *env, shell);
	if (shell->cmd[0])
		ft_strcpy(shell->history[shell->his_n++], shell->cmd);
	shell->cmds = split_quoting_set(shell->cmd, ";");
	i = -1;
	while (shell->cmds[++i])
		g_sig.ret = handle_pipes(env, shell->cmds[i], shell);
	free_array(shell->cmds);
	free(shell->cmd);
	return (0);
}
