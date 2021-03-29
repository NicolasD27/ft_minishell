/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 23:43:44 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/29 13:47:10 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*char_sub(char c, int *i, int squote, int dquote)
{
	*i += 1;
	if (c == '\'' && squote % 2 != 1)
		return ("\'");
	else if (c == '"')
		return ("\"");
	else if (c == '\\')
	{
		if (squote % 2 == 1)
			return ("\\\\");
		return ("\\");
	}
	else if (c == '$' && dquote % 2 == 1)
		return ("$");
	*i -= 1;
	return ("\\");
}

char	*handle_backslash(char *s, char *arg, int *i, int *j)
{
	if (arg[*i + 1])
		s = join_free_char(s, arg[++(*i)], (*j)++);
	else
		ft_putstr_fd("backslash error", 2);
	return (s);
}

char	*quote_loop(char *arg, int *squote, int *dquote, char **env)
{
	char	*s;
	int		i;
	int		j;

	if (!(s = malloc(ft_strlen(arg))))
		return (NULL);
	i = -1;
	j = 0;
	while (arg[++i])
	{
		if (arg[i] == '\'' && *dquote % 2 == 0)
			*squote += 1;
		else if (arg[i] == '\"' && *squote % 2 == 0)
			*dquote += 1;
		else if (arg[i] == '\\' && (*squote % 2 == 1 || *dquote % 2 == 1))
			j = join_sub(&s, char_sub(arg[i + 1], &i, *squote, *dquote), j);
		else if (arg[i] == '$' && *squote % 2 == 0)
			j = join_free(&s, dollar_found(arg, env, &i), j);
		else if (arg[i] == '\\')
			s = handle_backslash(s, arg, &i, &j);
		else
			s = join_free_char(s, arg[i], j++);
	}
	s[j] = '\0';
	return (s);
}

int		handle_quote(char ***args, char **env)
{
	int		i;
	int		squote;
	int		dquote;
	char	*tmp;

	squote = 0;
	dquote = 0;
	i = 0;
	while ((*args)[i])
	{
		tmp = quote_loop((*args)[i], &squote, &dquote, env);
		free((*args)[i]);
		(*args)[i] = tmp;
		i++;
	}
	if (dquote % 2 != 0 || squote % 2 != 0)
	{
		g_sig.ret = 130;
		write(2, "unclosed quote\n", 15);
		return (-1);
	}
	return (0);
}
