/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:32:16 by nidescre          #+#    #+#             */
/*   Updated: 2019/11/06 14:54:34 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*when_null(const char *s1, const char *s2)
{
	if (s1)
		return (ft_strdup(s1));
	else if (s2)
		return (ft_strdup(s2));
	else
		return (NULL);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*s3;
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (when_null(s1, s2));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if ((s3 = malloc(s1_len + s2_len + 1)) == NULL)
		return (NULL);
	while (i < s1_len)
	{
		s3[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		s3[i + s1_len] = s2[i];
		i++;
	}
	s3[i + s1_len] = '\0';
	return (s3);
}
