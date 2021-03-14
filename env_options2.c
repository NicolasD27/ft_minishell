/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_options2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:53:26 by nidescre          #+#    #+#             */
/*   Updated: 2021/01/21 19:02:33 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_unrecog_option(char *s)
{
	write(2, "env: unrecognized option ", 26);
	write(2, s, ft_strlen(s));
	write(2, "\nTry 'env --help' for more information.\n", 40);
	return (-1);
}

int		print_invalid_option(char *s)
{
	write(2, "env: invalid option ", 20);
	write(2, s, ft_strlen(s));
	write(2, "\nTry 'env --help' for more information.\n", 40);
	return (-1);
}

int		special_cmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i])
	{
		if (s1[i] == '='
				&& (!ft_strcmp(s2, "--unset") || !ft_strcmp(s2, "--chdir")))
			return (1);
		return (0);
	}
	return (1);
}

void	is_long_option(char *arg, int **options)
{
	if (special_cmp(arg, "--ignore-environment"))
		(*options)[0] = 1;
	else if (special_cmp(arg, "--null"))
		(*options)[1] = 1;
	else if (special_cmp(arg, "--unset"))
		(*options)[2] = 1;
	else if (special_cmp(arg, "--chdir"))
		(*options)[3] = 1;
	else if (special_cmp(arg, "--debug"))
		(*options)[4] = 1;
	else if (special_cmp(arg, "--help"))
		(*options)[5] = 1;
	else if (special_cmp(arg, "--version"))
		(*options)[6] = 1;
	else
		(*options)[10] = 1;
}

int		is_short_option(char c)
{
	if (c == '\0' || c == 'i')
		return (0);
	if (c == '0')
		return (1);
	if (c == 'u')
		return (2);
	if (c == 'C')
		return (3);
	if (c == 'v')
		return (4);
	return (9);
}
