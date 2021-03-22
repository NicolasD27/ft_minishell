/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:30:28 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/22 21:36:35 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		route_cmd(char ***env, t_shell *shell)
{
	if (!ft_strcmp(shell->args[0], "exit"))
		ft_exit(shell, *env);
	else if (!ft_strcmp(shell->args[0], "echo"))
		ft_echo(shell->args);
	else if (!ft_strcmp(shell->args[0], "pwd"))
		return (ft_pwd(shell->args));
	else if (!ft_strcmp(shell->args[0], "cd"))
		return (ft_chdir(shell->args[1], env));
	else if (!ft_strcmp(shell->args[0], "export"))
		return (ft_export(shell, env));
	else if (!ft_strcmp(shell->args[0], "unset"))
		ft_unsetenv(shell->args, env, shell);
	else if (!ft_strcmp(shell->args[0], "env"))
		return (ft_env(*env, shell));
	else
		return (exec_prog(*env, shell));
	return (0);
}

void	kill_prog(void)
{
	char buff;

	g_sig.sigquit = 0;
	buff = 0;
	read(fileno(stdin), &buff, 1);
	if (buff == 4)
	{
		kill(g_sig.pid, 9);
		g_sig.ret = 0;
	}
}

int		exec_prog(char **env, t_shell *shell)
{
	int		status;
	int		r_pid;
	int		i;

	g_sig.sigquit = 1;
	r_pid = 0;
	if (0 == (g_sig.pid = fork()))
		find_prog(shell->args, env, shell->paths, shell);
	i = 0;
	while (shell->pipes[i])
		i++;
	if (i <= 1 || !ft_strcmp(g_sig.cur_cmd, shell->pipes[0]))
	{
		if (0 == (r_pid = fork()))
			kill_prog();
	}
	waitpid(g_sig.pid, &status, 0);
	if (r_pid != 0)
		kill(r_pid, 9);
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (g_sig.ret);
	return (WEXITSTATUS(status));
}

void	abs_prog(char **argv, char **env, t_shell *shell)
{
	char	**tmp;
	char	*prg;
	char	*pwd;
	int		exec_error;
	int		j;

	if (argv[0][0] == '/')
		exec_error = execve(argv[0], argv, env);
	else if ((j = find_env(env, "PWD")) != -1)
	{
		tmp = ft_split(env[j], '=');
		pwd = ft_strjoin(tmp[1], "/");
		free_array(tmp);
		prg = ft_strjoin(pwd, argv[0]);
		exec_error = execve(prg, argv, env);
		free(prg);
		free(pwd);
	}
	if (exec_error == -1)
	{
		write(2, argv[0], ft_strlen(argv[0]));
		write(2, ": Command not found\n", 20);
		free_all(shell, env, 127);
	}
}

int		find_prog(char **argv, char **env, char **paths, t_shell *shell)
{
	int		i;
	char	*prg;

	if (paths)
	{
		i = 0;
		prg = ft_strjoin(paths[0], argv[0]);
		while (-1 == execve(prg, argv, env) && paths[i])
		{
			free(prg);
			prg = ft_strjoin(paths[i++], argv[0]);
		}
		free(prg);
		if (!paths[i])
			abs_prog(argv, env, shell);
	}
	else
		abs_prog(argv, env, shell);
	return (i);
}
