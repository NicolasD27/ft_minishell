/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 19:43:09 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/23 22:37:36 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shift_args(char ***args, int i, int offset)
{
	int		len;
	char	**tmp;

	len = 0;
	while ((*args)[len])
		len++;
	if (!(tmp = (char **)malloc((len + 1 - offset) * sizeof(char *))))
		return ;
	len = -1;
	while (++len < i)
		tmp[len] = ft_strdup((*args)[len]);
	while ((*args)[i + offset])
	{
		tmp[i] = ft_strdup((*args)[i + offset]);
		i++;
	}
	tmp[i] = NULL;
	free_array(*args);
	*args = tmp;
}

char	*redir_right(char ***args, int *redir, int *i)
{
	char *filename;

	if ((*args)[*i][1] == '>')
		*redir = 2;
	else
		*redir = 1;
	if ((*args)[*i][*redir])
	{
		filename = ft_strdup((*args)[*i] + *redir);
		shift_args(args, *i, 1);
		*i -= 1;
	}
	else if ((*args)[*i + 1])
	{
		filename = ft_strdup((*args)[*i + 1]);
		shift_args(args, *i, 2);
		*i -= 2;
	}
	else
		*redir = 666;
	return (filename);
}

char	*redir_left(char ***args, int *redir, int *i)
{
	char *filename;

	*redir = -1;
	if ((*args)[*i][1])
	{
		filename = ft_strdup((*args)[*i] + 1);
		shift_args(args, *i, 1);
		*i -= 1;
	}
	else if ((*args)[*i + 1])
	{
		filename = ft_strdup((*args)[*i + 1]);
		shift_args(args, *i, 2);
		*i -= 2;
	}
	else
		*redir = 666;
	return (filename);
}

int		check_filename(char *filename, int *redir)
{
	int		fd;

	if (filename && *redir)
	{
		if (*redir == -1)
			fd = open(filename, O_RDONLY, 0600);
		else
			fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0600);
		if (fd == -1)
		{
			*redir = 999;
			return (1);
		}
		close(fd);
	}
	return (0);
}

char	*find_redirections(char ***args, int *redir)
{
	int		i;
	char	*filename;

	filename = NULL;
	i = 0;
	while ((*args)[i])
	{
		if ((*args)[i][0] == '<')
		{
			if (filename)
				free(filename);
			filename = redir_left(args, redir, &i);
		}
		else if ((*args)[i][0] == '>')
		{
			if (filename)
				free(filename);
			filename = redir_right(args, redir, &i);
		}
		if (check_filename(filename, redir))
			return (filename);
		i++;
	}
	return (filename);
}
