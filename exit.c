/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:58:16 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/29 12:26:21 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_numeric(char *arg)
{
	int i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i = 1;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int		modulo(int n)
{
	while (n < 0)
		n += 256;
	return (n % 256);
}

int		ft_exit(t_shell *shell, char **env)
{
	int i;

	i = 0;
	while (shell->args[i])
		i++;
	ft_putstr_fd("exit\n", 1);
	if (i == 1)
		free_all(shell, env, g_sig.ret);
	else if (is_numeric(shell->args[1]) && i == 2)
		free_all(shell, env, modulo(ft_atoi(shell->args[1])));
	else if (is_numeric(shell->args[1]) && i > 2)
		ft_putstr_fd("bash: erit: too many arguments\n", 1);
	else
	{
		ft_putstr_fd("bash: exit: ", 1);
		ft_putstr_fd(shell->args[1], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		free_all(shell, env, 2);
	}
	return (1);
}
