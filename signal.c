/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:25:31 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/29 13:59:57 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_handler(int signum)
{
	char *pid_str;
	char *cmd;

	(void)signum;
	pid_str = ft_itoa(g_sig.pid);
	if (g_sig.sigquit == 1)
	{
		if (g_sig.pid != 0)
		{
			cmd = ft_strtrim(g_sig.cur_cmd, " ");
			g_sig.sigquit = 2;
			ft_putstr_fd("Quit (core dumped)\n", 2);
			kill(g_sig.pid, 3);
			g_sig.ret = 131;
			free(cmd);
		}
	}
	free(pid_str);
}

void	int_handler(int signum)
{
	(void)signum;
	g_sig.ret = 130;
	if (g_sig.pid == 0)
	{
		write(2, "\n", 1);
		write_prompt();
	}
	g_sig.sigint = 0;
}
