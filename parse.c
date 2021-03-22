/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 17:29:23 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/22 20:01:04 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_up(t_shell *shell, char *cmd, int *cmd_len, int *n)
{
	int i;

	cmd[*cmd_len - 2] = '\0';
	ft_strcpy(shell->history[shell->his_n], cmd);
	*n += 1;
	while (shell->his_n >= *n
			&& cmd_begin(cmd, shell->history[shell->his_n - *n]) != 0)
		*n += 1;
	if (*n > shell->his_n)
	{
		get_termcap("bl");
		*n = shell->his_n;
		while (shell->his_n >= *n
				&& cmd_begin(cmd, shell->history[shell->his_n - *n]) != 0)
			*n -= 1;
	}
	i = 0;
	get_termcap("dl");
	write(1, "$> ", 3);
	while (shell->history[shell->his_n - *n][i])
	{
		ft_putchar(shell->history[shell->his_n - *n][i]);
		i++;
	}
}

void	handle_down(t_shell *shell, char *cmd, int *cmd_len, int *n)
{
	int i;

	cmd[*cmd_len - 2] = '\0';
	ft_strcpy(shell->history[shell->his_n], cmd);
	*n -= 1;
	while (*n >= 0 && cmd_begin(cmd, shell->history[shell->his_n - *n]) != 0)
		*n -= 1;
	if (*n < 0)
	{
		*n = 0;
		get_termcap("bl");
	}
	i = 0;
	get_termcap("dl");
	write(1, "$> ", 3);
	while (shell->history[shell->his_n - *n][i])
	{
		ft_putchar(shell->history[shell->his_n - *n][i]);
		i++;
	}
}

void	handle_arrows(t_shell *shell, char *cmd, int *cmd_len, int *n)
{
	read(STDIN_FILENO, cmd + ++(*cmd_len), 1);
	read(STDIN_FILENO, cmd + ++(*cmd_len), 1);
	if (cmd[*cmd_len] == 'A')
		handle_up(shell, cmd, cmd_len, n);
	else if (cmd[*cmd_len] == 'B')
		handle_down(shell, cmd, cmd_len, n);
	*cmd_len -= 2;
}

void	handle_del(t_shell *shell, char *cmd, int *cmd_len, int *n)
{
	if (*n != 0)
	{
		ft_strcpy(cmd, shell->history[shell->his_n - *n]);
		*cmd_len = ft_strlen(cmd);
		*n = 0;
	}
	if (!(*cmd_len == 0 || cmd[*cmd_len - 1] == 127))
	{
		*cmd_len -= 1;
		write(1, "\b \b", 3);
	}
}

void	handle_char(t_shell *shell, char *cmd, int *cmd_len, int *n)
{
	char c;

	c = cmd[*cmd_len];
	ft_putchar(c);
	if (*n != 0)
	{
		ft_strcpy(cmd, shell->history[shell->his_n - *n]);
		*cmd_len = ft_strlen(cmd);
		cmd[*cmd_len] = c;
		*n = 0;
	}
	*cmd_len += 1;
}
