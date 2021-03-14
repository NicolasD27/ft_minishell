/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:41:00 by nidescre          #+#    #+#             */
/*   Updated: 2019/11/05 17:16:58 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*core_itoa(long n, int size, int neg, long pow)
{
	char	*res;
	int		i;

	i = 0;
	if ((res = malloc((size + neg + 1))) == NULL)
		return (NULL);
	if (neg)
	{
		res[0] = '-';
		i++;
	}
	while (i < size + neg)
	{
		res[i] = (char)(n / pow) + 48;
		n = n % pow;
		pow /= 10;
		i++;
	}
	res[i] = '\0';
	return (res);
}

static	char	*when_zero(void)
{
	char *res;

	if ((res = malloc((2))) == NULL)
		return (NULL);
	res[0] = '0';
	res[1] = '\0';
	return (res);
}

char			*ft_itoa(int n)
{
	long	pow;
	int		neg;
	int		size;
	long	nb;

	size = 0;
	nb = n;
	pow = 1;
	neg = 0;
	if (n == 0)
		return (when_zero());
	if (n < 0)
	{
		neg = 1;
		nb = -nb;
	}
	while (nb / pow)
	{
		pow *= 10;
		size++;
	}
	pow /= 10;
	return (core_itoa(nb, size, neg, pow));
}
