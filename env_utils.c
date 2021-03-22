/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:28:00 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/21 18:44:45 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env(char *key, char *value, char ***env)
{
	char	*tmp;
	int		i;
	char	**new_env;

	i = 0;
	while (*env && (*env)[i])
		i++;
	if (!(new_env = malloc((i + 2) * sizeof(char *))))
		return ;
	tmp = ft_strjoin(key, "=");
	new_env[i + 1] = NULL;
	new_env[i] = ft_strjoin(tmp, value);
	free(tmp);
	while (--i >= 0)
		new_env[i] = (*env)[i];
	if (*env)
		free(*env);
	*env = new_env;
}

void	add_env_hashed(char *line, char ***env)
{
	int		i;
	char	**new_env;

	i = 0;
	while ((*env)[i])
		i++;
	if (!(new_env = malloc((i + 2) * sizeof(char *))))
		return ;
	new_env[i + 1] = NULL;
	new_env[i] = ft_strdup(line);
	while (--i >= 0)
		new_env[i] = (*env)[i];
	free(*env);
	*env = new_env;
}

void	remove_env(char ***env, int n)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 1;
	while ((*env)[i])
		i++;
	if (!(new_env = malloc(i * sizeof(char *))))
		return ;
	while (i >= 0)
	{
		if (i == n)
		{
			free((*env)[i]);
			j = 0;
		}
		else
			new_env[i - j] = (*env)[i];
		i--;
	}
	free(*env);
	*env = new_env;
}

void	rehash(char ***env, int i, char *key, char *value)
{
	char *tmp;

	tmp = ft_strjoin(key, "=");
	free((*env)[i]);
	(*env)[i] = ft_strjoin(tmp, value);
	free(tmp);
}

void	dehash(char *line, char **key, char **value)
{
	int n;

	n = index_of(line, '=');
	line[n] = '\0';
	*key = ft_strdup(line);
	*value = ft_strdup(line + n + 1);
	line[n] = '=';
}
