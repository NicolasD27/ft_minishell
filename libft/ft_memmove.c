/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:44:45 by nidescre          #+#    #+#             */
/*   Updated: 2019/10/22 14:04:27 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memmove(void *dst, const void *src, int len)
{
	int i;

	if (dst == src)
		return (dst);
	if (dst < src)
	{
		i = 0;
		while (i < len)
		{
			((char*)dst)[i] = ((char*)src)[i];
			i++;
		}
	}
	else
	{
		i = len - 1;
		while (i >= 0)
		{
			((char*)dst)[i] = ((char*)src)[i];
			i--;
		}
	}
	return (dst);
}
