/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:35:06 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/28 18:55:39 by nidescre         ###   ########.fr       */
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
		ft_putstr_fd(args[i], 1);
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}

int		ft_pwd(void)
{
	char	*pwd;

	if (!(pwd = malloc(2048)))
		return (1);
	getcwd(pwd, 2048);
	write(1, pwd, ft_strlen(pwd));
	free(pwd);
	write(1, "\n", 1);
	return (0);
}
