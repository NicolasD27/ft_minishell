/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:39:21 by nidescre          #+#    #+#             */
/*   Updated: 2021/01/15 22:14:18 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		to_trim(char c, char const *set)
{
	int i;

	i = 0;
	while (set[i] && set[i] != c)
		i++;
	if (set[i])
		return (1);
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int aft;
	int bef;
	int s1_len;

	aft = 0;
	bef = 0;
	s1_len = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return ((char*)s1);
	while (s1[s1_len])
		s1_len++;
	while (to_trim(s1[bef], set))
		bef++;
	if (bef + aft >= s1_len)
		return (ft_calloc(1, sizeof(char)));
	while (to_trim(s1[s1_len - aft - 1], set))
		aft++;
	return (ft_substr(s1, bef, s1_len - aft - bef));
}
