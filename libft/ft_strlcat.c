/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 19:19:22 by nidescre          #+#    #+#             */
/*   Updated: 2019/11/04 13:02:34 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlcat(char *dst, const char *src, int dstsize)
{
	int srclen;
	int dstlen;
	int j;

	srclen = 0;
	dstlen = 0;
	j = 0;
	while (dst[dstlen] && dstlen <= dstsize)
		dstlen++;
	while (src[srclen])
		srclen++;
	if (dstsize == 0 || dstlen > dstsize)
		return (dstsize + srclen);
	while (dstlen + j < dstsize - 1 && src[j])
	{
		dst[dstlen + j] = src[j];
		j++;
	}
	dst[dstlen + j] = '\0';
	return (dstlen + srclen);
}
