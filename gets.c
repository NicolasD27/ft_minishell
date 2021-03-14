/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:29:52 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/14 18:08:20 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		index_of(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] || s[i] == c)
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	**add_backslash(char **paths)
{
	int		i;
	int		len;
	char	*tmp;

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

	if (!(path_string = malloc(2048)))
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T'
				&& env[i][3] == 'H' && env[i][4] == '=')
		{
			ft_strlcpy(path_string, env[i] + 5, 2048);
			break ;
		}
		i++;
	}
	paths = ft_split(path_string, ':');
	free(path_string);
	return (add_backslash(paths));
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

void	get_cmd(char *cmd, char **env, t_shell *shell)
{
	int	cmd_len;
	int	n;

	cmd_len = 0;
	n = 0;
	while (read(STDIN_FILENO, cmd + cmd_len, 1) > 0 && cmd[cmd_len] != '\n')
	{
		if (cmd[cmd_len] == 127)
			handle_del(shell, cmd, &cmd_len, &n);
		else if (cmd[cmd_len] == '\t')
			get_termcap("bl");
		else if (cmd[cmd_len] == 27)
			handle_arrows(shell, cmd, &cmd_len, &n);
		else if (cmd[cmd_len] == 4)
			free_half(shell, env);
		else
			handle_char(shell, cmd, &cmd_len, &n);
	}
	if (n != 0)
		ft_strcpy(cmd, shell->history[shell->his_n - n]);
	else
		cmd[cmd_len] = '\0';
	ft_putchar('\n');
}
