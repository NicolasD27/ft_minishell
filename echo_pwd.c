/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:35:06 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/22 20:01:34 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(char **args)
{
	int i;
	int nl;
	int sp;

	i = 1;
	nl = 1;
	sp = 0;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n'
			&& args[i][2] == '\0')
	{
		i++;
		nl = 0;
	}
	while (args[i])
	{
		if (sp)
			write(1, " ", 1);
		else
			sp = 1;
		write(1, args[i], ft_strlen(args[i]));
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}

int		ft_pwd(char **args)
{
	char	*pwd;

	if (!(pwd = malloc(2048)))
		return (1);
	if (args[1])
	{
		write(1, "pwd: too many arguments\n", 24);
		return (1);
	}
	else
	{
		getcwd(pwd, 2048);
		write(1, pwd, ft_strlen(pwd));
		free(pwd);
	}
	write(1, "\n", 1);
	return (0);
}
