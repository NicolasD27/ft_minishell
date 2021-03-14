/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:30:28 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/13 23:32:18 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_shell *shell, char **env)
{
	free_array(env);
	free(g_sig.cur_cmd);
	free_array(shell->cmds);
	free_array(shell->paths);
	free_array(shell->args);
	free_array(shell->pipes);
	free(shell->filename);
	free(shell->cmd);
	free_array_n(shell->history, 1024);
	exit(EXIT_SUCCESS);
}

int		route_cmd(char ***env, t_shell *shell)
{
	if (!ft_strcmp(shell->args[0], "exit"))
		free_all(shell, *env);
	else if (!ft_strcmp(shell->args[0], "echo"))
		ft_echo(shell->args);
	else if (!ft_strcmp(shell->args[0], "pwd"))
		return (ft_pwd(*env, shell->args));
	else if (!ft_strcmp(shell->args[0], "cd"))
		return (ft_chdir(shell->args[1], env));
	else if (!ft_strcmp(shell->args[0], "export"))
		return (ft_export(shell->args, env));
	else if (!ft_strcmp(shell->args[0], "unset"))
		ft_unsetenv(shell->args, env);
	else if (!ft_strcmp(shell->args[0], "env"))
		return (ft_env(*env, shell));
	else
		return (exec_prog(*env, shell));
	return (0);
}

int		exec_prog(char **env, t_shell *shell)
{
	int		status;

	g_sig.sigquit = 1;
	if (0 == (g_sig.pid = fork()))
	{
		find_prog(shell->args, env, shell->paths, shell);
	}
	while (0 == waitpid(g_sig.pid, &status, WNOHANG))
		sleep(1);
	if (g_sig.sigint == 1 && g_sig.sigquit == 1
			&& (1 != WIFEXITED(status) || 0 != WEXITSTATUS(status)))
	{
		write(2, shell->args[0], ft_strlen(shell->args[0]));
		write(2, ": Command failed\n", 17);
	}
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
		free_all(shell, env);
	}
}

int		find_prog(char **argv, char **env, char **paths, t_shell *shell)
{
	int		i;
	char	*prg;

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
	return (i);
}
