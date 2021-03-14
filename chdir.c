/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:36:37 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/09 01:33:02 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(char ***env, char *new_pwd)
{
	int		n;
	char	*key;
	char	*old_pwd;

	if ((n = find_env(*env, "PWD")) == -1)
		return ;
	dehash((*env)[n], &key, &old_pwd);
	rehash(env, n, "PWD", new_pwd);
	if ((n = find_env(*env, "OLDPWD")) == -1)
		return ;
	rehash(env, n, "OLDPWD", old_pwd);
	free(key);
	free(old_pwd);
}

void	print_cd_error(char *dir)
{
	if (errno == 2)
		write(2, "cd: no such file or directory: ", 31);
	else if (errno == 5)
		write(2, "cd: An I/O error occurred: ", 27);
	else if (errno == 12)
		write(2, "cd: Insufficient kernel memory was available: ", 46);
	else if (errno == 13)
		write(2, "cd: permission denied: ", 23);
	else if (errno == 14)
		write(2, "cd: path points outside your accessible address space: ", 55);
	else if (errno == 20)
		write(2, "cd: not a directory: ", 21);
	else if (errno == 36)
		write(2, "cd: path is too long: ", 22);
	else if (errno == 40)
		write(2, "cd: Too many symbolic links: ", 29);
	write(2, dir, ft_strlen(dir));
	write(2, "\n", 1);
}

int		chdir_end(char *target, char ***env)
{
	char	*path;
	int		ret;

	if (!(path = malloc(2048)))
		return (-1);
	if ((ret = chdir(target)) == -1)
		print_cd_error(target);
	else
	{
		getcwd(path, 2048);
		update_pwd(env, path);
	}
	free(path);
	return (ret);
}

int		ft_chdir(char *target, char ***env)
{
	if (!target || !ft_strcmp(target, "~"))
	{
		if (special_chdir(env, "HOME") == -1)
			return (1);
	}
	else if (!ft_strcmp(target, "-"))
	{
		if (special_chdir(env, "OLDPWD") == -1)
			return (1);
	}
	else
		return (chdir_end(target, env));
	return (0);
}

int		special_chdir(char ***env, char *target)
{
	int		n;
	char	*key;
	char	*value;

	if ((n = find_env(*env, target)) == -1)
		return (-1);
	dehash((*env)[n], &key, &value);
	chdir(value);
	update_pwd(env, value);
	free(key);
	free(value);
	return (0);
}
