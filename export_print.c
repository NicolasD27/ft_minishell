/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:09:08 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/22 21:11:29 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**concat_arrays(char **env, char **exports)
{
	char	**sorted;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	j = 0;
	while (exports && exports[j])
		j++;
	if (!(sorted = malloc((i + j + 1) * sizeof(char *))))
		return (NULL);
	i = -1;
	while (env[++i])
		sorted[i] = ft_strdup(env[i]);
	j = 0;
	while (exports && exports[j])
	{
		sorted[i + j] = ft_strdup(exports[j]);
		j++;
	}
	sorted[i + j] = NULL;
	return (sorted);
}

char	**sort_alpha(char **env, char **exports, int i)
{
	char	**sorted;
	int		min;
	int		j;
	int		n;
	char	*tmp;

	sorted = concat_arrays(env, exports);
	n = array_size(sorted);
	i = -1;
	while (++i < n - 1)
	{
		min = i;
		j = i;
		while (++j < n)
			if (ft_strcmp(sorted[min], sorted[j]) > 0)
				min = j;
		if (min != i)
		{
			tmp = sorted[i];
			sorted[i] = sorted[min];
			sorted[min] = tmp;
		}
	}
	return (sorted);
}

void	print_env_export(char **env, char **exports)
{
	int		i;
	char	**sorted;
	char	*key;
	char	*value;

	i = 0;
	sorted = sort_alpha(env, exports, i);
	while (sorted[i])
	{
		write(1, "declare -x ", 11);
		dehash(sorted[i], &key, &value);
		ft_putstr_fd(key, 1);
		ft_putstr_fd("=\"", 2);
		ft_putstr_fd(value, 1);
		write(1, "\"\n", 2);
		free(key);
		free(value);
		i++;
	}
	free_array(sorted);
}
