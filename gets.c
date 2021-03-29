/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:29:52 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/29 12:53:51 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_backslash(char **paths)
{
	int		i;
	int		len;
	char	*tmp;

	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strdup(paths[i]);
		len = ft_strlen(tmp);
		free(paths[i]);
		if (!(paths[i] = malloc(len + 2)))
			return (NULL);
		ft_strlcpy(paths[i], tmp, len + 1);
		paths[i][len] = '/';
		paths[i][len + 1] = '\0';
		free(tmp);
		i++;
	}
	return (paths);
}

char	**get_paths(char **env)
{
	int		i;
	char	*path_string;
	char	**paths;
	char	**tmp;

	i = 0;
	path_string = NULL;
	paths = NULL;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T'
				&& env[i][3] == 'H' && env[i][4] == '=')
		{
			if (!(path_string = malloc(2048)))
				return (NULL);
			ft_strlcpy(path_string, env[i] + 5, 2048);
			tmp = ft_split(path_string, ':');
			free(path_string);
			paths = add_backslash(tmp);
			break ;
		}
		i++;
	}
	return (paths);
}

int		cmd_begin(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s1[i] && s1[i] != s2[i])
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

int		handle_read(char *cmd, int cmd_len, int *n, t_shell *shell)
{
	if (g_sig.sigint == 0 && cmd_len != 0)
		cmd[0] = '\0';
	if (cmd[cmd_len] == 127)
		handle_del(shell, cmd, &cmd_len, n);
	else if (cmd[cmd_len] == '\t')
		get_termcap("bl");
	else if (cmd[cmd_len] == 27)
		handle_arrows(shell, cmd, &cmd_len, n);
	else if (cmd[cmd_len] != 4)
	{
		handle_char(shell, cmd, &cmd_len, n);
		if (g_sig.sigint == 0)
		{
			g_sig.sigint = 1;
			if (!(cmd[cmd_len - 1] == 127 || cmd[cmd_len - 1] == 27
						|| cmd[cmd_len - 1] == '\t'))
				cmd[0] = cmd[cmd_len - 1];
			cmd_len = 1;
		}
	}
	return (cmd_len);
}

char	*get_cmd(char **env, t_shell *shell)
{
	char	*cmd;
	int		cmd_len;
	int		n;

	if (!(cmd = malloc(2048)))
		return (NULL);
	cmd_len = 0;
	n = 0;
	while (read(STDIN_FILENO, cmd + cmd_len, 1) > 0 && cmd[cmd_len] != '\n')
	{
		if (cmd[cmd_len] == 4
				&& ((cmd_len == 0 && n == 0) || g_sig.sigint == 0))
			free_half(shell, env, cmd);
		else
			cmd_len = handle_read(cmd, cmd_len, &n, shell);
	}
	if (g_sig.sigint == 0)
		cmd[0] = '\0';
	if (n != 0)
		ft_strcpy(cmd, shell->history[shell->his_n - n]);
	else
		cmd[cmd_len] = '\0';
	ft_putchar('\n');
	return (cmd);
}
