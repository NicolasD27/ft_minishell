/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:26:50 by nidescre          #+#    #+#             */
/*   Updated: 2019/11/04 12:49:27 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strnstr(const char *haystack, const char *needle, int len)
{
	int i;
	int j;
	int nlen;

	i = 0;
	j = 0;
	if (!(needle[0]))
		return ((char*)(haystack));
	nlen = 0;
	while (needle[nlen])
		nlen++;
	while (i < len - nlen + 1)
	{
		j = 0;
		while (needle[j] && haystack[i + j] == needle[j])
			j++;
		if (!(needle[j]))
			return ((char*)(haystack + i));
		i++;
	}
	return (0);
}
