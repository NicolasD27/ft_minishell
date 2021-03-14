/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:41:34 by nidescre          #+#    #+#             */
/*   Updated: 2019/11/04 12:59:56 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlcpy(char *dst, const char *src, int dstsize)
{
	int i;
	int srclen;

	i = 0;
	srclen = 0;
	if (!src)
		return (0);
	while (src[srclen])
		srclen++;
	if (!dst)
		return (srclen);
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (srclen);
}
